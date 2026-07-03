#include <Engine/Rendering/DefaultRenderer.hpp>

#include <Engine/Application/Application.hpp>

#include <Engine/Rendering/RenderPass.hpp>
#include <Engine/Rendering/GeometryPass.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <Coral/ImGui_Impl_Coral.hpp>

#include <array>
#include <memory>
#include <ranges>
#include <vector>
#include <unordered_set>

using namespace Reef::Rendering;

namespace
{
void
createRenderPassListRecursive(RenderPass& renderPass,
                                    std::vector<RenderPass*>& renderPasses)
{
    renderPasses.push_back(&renderPass);
    
    for (auto input : renderPass.dependencies())
    {
        createRenderPassListRecursive(*input, renderPasses);
    }
}


std::vector<RenderPass*>
createSortedRenderPassList(RenderPass& renderPass)
{
    // Contains the render passes in reversed order
    std::vector<RenderPass*> renderPasses;
    createRenderPassListRecursive(renderPass, renderPasses);

    std::unordered_set<RenderPass*> visited;

    std::vector<RenderPass*> renderPassesSorted;
    
    for (auto renderPass : std::views::reverse(renderPasses))
    {
        if (visited.insert(renderPass).second)
        {
            renderPassesSorted.push_back(renderPass);
        }
    }

    return renderPassesSorted;
}

} // namespace

class PresentPass : public RenderPass
{
public:

    PresentPass(DefaultRenderer& renderer, std::shared_ptr<RenderPass> dependency)
        : RenderPass("PresentPass", renderer, dependency)
    {
    }

    void recordCommandBuffer(const SceneView& view, 
                             Coral::CommandBuffer& commandBuffer)
    {
        auto sourceImage = mDependencies.front()->framebuffer()->colorAttachment(0);
        auto targetImage = renderer().canvas()->currentFrameData().framebuffer->colorAttachment(0);
        commandBuffer.cmdBlitImage(sourceImage, targetImage);
    }

    Coral::Semaphore* renderPassFinishedSemaphore() override
    {
        return renderer().canvas()->currentFrameData().renderFinishedSemaphore;
    }

    std::vector<Coral::Semaphore*> renderPassReadySemaphores() override
    {
        auto semaphores = RenderPass::renderPassReadySemaphores();
        semaphores.push_back(renderer().canvas()->currentFrameData().framebufferReadySemaphore);
        return semaphores;
    }

    Coral::Framebuffer* framebuffer() override { return mDependencies.back()->framebuffer(); }
};


class ImGuiPass : public RenderPass
{
public:

    ImGuiPass(DefaultRenderer& renderer, std::shared_ptr<RenderPass> dependency)
        : RenderPass("ImGuiPass", renderer, dependency)
    {
        ImGui_ImplCoral_InitInfo initInfo{};
        initInfo.context              = &renderer.context();
        initInfo.swapchainImageCount  = renderer.canvas()->swapchain()->swapchainImageCount();
        initInfo.framebufferSignature = renderer.canvas()->swapchain()->framebufferSignature();

        ImGui_ImplCoral_Init(&initInfo);
        ImGui_ImplCoral_CreateFontsTexture();
    }


    ~ImGuiPass()
    {
        ImGui_ImplCoral_DestroyFontsTexture();
        ImGui_ImplCoral_Shutdown();
    }

    void recordCommandBuffer(const SceneView& view, 
                             Coral::CommandBuffer& commandBuffer) override
    {
        if (!view.drawData)
        {
            return;
        }

        auto colorImage = framebuffer()->colorAttachment(0);

        auto iter = mFramebuffers.find(colorImage);
        if (iter == mFramebuffers.end())
        {
            Coral::ColorAttachment colorAttachment{ 0, colorImage };

            Coral::FramebufferCreateConfig config{};
            config.colorAttachments = std::span{ &colorAttachment, 1 };

            auto framebuffer = context().createFramebuffer(config).value();

            iter = mFramebuffers.emplace(colorImage, framebuffer).first;
        }

        ImGui_ImplCoral_NewFrame();

        Coral::ClearColor clearColor{ 0, Coral::ClearOp::LOAD, { 0.f, 0.f, 0.f, 1.f } };

        Coral::BeginRenderPassInfo info{};
        info.framebuffer = iter->second.get();
        info.clearColor  = { &clearColor, 1 };

        commandBuffer.cmdBeginRenderPass(info);
        commandBuffer.cmdSetViewport({ 0, 0, info.framebuffer->width(), info.framebuffer->height(), 0.f, 1.f, Coral::ViewportMode::Y_UP });

        ImGui_ImplCoral_RenderDrawData(&view.drawData->DrawData, &commandBuffer);

        commandBuffer.cmdEndRenderPass();
    }

    Coral::Framebuffer* framebuffer() override { return mDependencies.front()->framebuffer(); }

private:

    std::unordered_map<Coral::Image*, Coral::FramebufferPtr> mFramebuffers;
};


std::unique_ptr<DefaultRenderer>
DefaultRenderer::create(std::shared_ptr<Canvas> canvas)
{
    return std::unique_ptr<DefaultRenderer>(new DefaultRenderer(canvas));
}


DefaultRenderer::DefaultRenderer(std::shared_ptr<Canvas> canvas)
{
    mCanvas          = canvas;
    mResourceManager = std::make_unique<ResourceManager>(*this);

    auto geometryPass   = std::make_shared<GeometryPass>(*this);
    auto imguiPass      = std::make_shared<ImGuiPass>(*this, geometryPass);

    mRenderGraphRoot    = std::make_unique<PresentPass>(*this, imguiPass);
    mRenderPassesSorted = createSortedRenderPassList(*mRenderGraphRoot);
}


Coral::Context&
DefaultRenderer::context()
{
    return mCanvas->context();
}


std::shared_ptr<Canvas>
DefaultRenderer::canvas()
{
    return mCanvas;
}


ResourceManager&
DefaultRenderer::resourceManager()
{
    return *mResourceManager;
}


void
DefaultRenderer::render(const SceneView& view)
{
    mCanvas->prepareRender();

    for (auto renderPass : mRenderPassesSorted)
    {
        renderPass->render(view);
    }

    mCanvas->finishRender();
}
