#include "DefaultRendererImpl.hpp"

////#include <Engine/Application/Application.hpp>
////
////#include <Engine/Rendering/RenderPass.hpp>
////#include <Engine/Rendering/GeometryPass.hpp>
////
////#include <glm/gtc/matrix_transform.hpp>
////
////#include <Coral/ImGui_Impl_Coral.hpp>

#include <array>
#include <memory>
#include <ranges>
#include <vector>
#include <unordered_set>

#include "RenderObjectImpl.hpp"

using namespace Reef::Rendering;

namespace
{

/*!
 *
 */
class RenderObjectFactory : public Reef::Util::Hive<RenderObjectImpl>::Factory
{
public:

    size_t objectSize() const override
    {
        return sizeof(RenderObjectImpl);
    }

    void constructAt(void* address) override
    {
        std::construct_at(static_cast<RenderObjectImpl*>(address));
    }
}; // class RenderObjectFactory

} // namespace

//void
//createRenderPassListRecursive(RenderPass& renderPass,
//                                    std::vector<RenderPass*>& renderPasses)
//{
//    renderPasses.push_back(&renderPass);
//    
//    for (auto input : renderPass.dependencies())
//    {
//        createRenderPassListRecursive(*input, renderPasses);
//    }
//}


//std::vector<RenderPass*>
//createSortedRenderPassList(RenderPass& renderPass)
//{
//    // Contains the render passes in reversed order
//    std::vector<RenderPass*> renderPasses;
//    createRenderPassListRecursive(renderPass, renderPasses);
//
//    std::unordered_set<RenderPass*> visited;
//
//    std::vector<RenderPass*> renderPassesSorted;
//    
//    for (auto renderPass : std::views::reverse(renderPasses))
//    {
//        if (visited.insert(renderPass).second)
//        {
//            renderPassesSorted.push_back(renderPass);
//        }
//    }
//
//    return renderPassesSorted;
//}

//} // namespace

//class PresentPass : public RenderPass
//{
//public:
//
//    PresentPass(DefaultRenderer& renderer, std::shared_ptr<RenderPass> dependency)
//        : RenderPass("PresentPass", renderer, dependency)
//    {
//    }
//
//    void recordCommandBuffer(const SceneView& view, 
//                             Coral::CommandBuffer& commandBuffer)
//    {
//        auto sourceImage = mDependencies.front()->framebuffer()->colorAttachment(0);
//        auto targetImage = renderer().canvas()->currentFrameData().framebuffer->colorAttachment(0);
//        commandBuffer.cmdBlitImage(sourceImage, targetImage);
//    }
//
//    Coral::Semaphore* renderPassFinishedSemaphore() override
//    {
//        return renderer().canvas()->currentFrameData().renderFinishedSemaphore;
//    }
//
//    std::vector<Coral::Semaphore*> renderPassReadySemaphores() override
//    {
//        auto semaphores = RenderPass::renderPassReadySemaphores();
//        semaphores.push_back(renderer().canvas()->currentFrameData().framebufferReadySemaphore);
//        return semaphores;
//    }
//
//    Coral::Framebuffer* framebuffer() override { return mDependencies.back()->framebuffer(); }
//};


/*class ImGuiPass : public RenderPass
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
*/


std::unique_ptr<Renderer>
Renderer::create(void* nativeWindowHandle)
{
    return std::make_unique<DefaultRendererImpl>(nativeWindowHandle);
}


DefaultRendererImpl::DefaultRendererImpl(void* nativeWindowHandle)
    : mResourceManager(*this)
    , mShaderManager(*this)
    , mRenderObjects(std::make_unique<RenderObjectFactory>())
{
    
    CoContextCreateConfig config{};
    config.graphicsAPI      = CO_GRAPHICS_API_VULKAN;
    config.pApplicationName = "Reef";
    if (coCreateContext(&config, std::out_ptr(mContext)) != CO_SUCCESS)
    {
        return;
    }

    CoSwapchainCreateConfig swapchainConfig{};
    auto depthFormat                   = CO_PIXEL_FORMAT_DEPTH24_STENCIL8;
    swapchainConfig.depthFormat        = &depthFormat;
    swapchainConfig.format             = CO_PIXEL_FORMAT_RGBA8_SRGB;
    swapchainConfig.lockToVSync        = false;
    swapchainConfig.minImageCount      = 2;
    swapchainConfig.nativeWindowHandle = nativeWindowHandle;

    if (coContextCreateSwapchain(mContext.get(), &swapchainConfig, std::out_ptr(mSwapchain)) != CO_SUCCESS)
    {
        return;
    }


    //mCanvas          = canvas;
    //mResourceManager = std::make_unique<ResourceManager>(*this);

    //auto geometryPass   = std::make_shared<GeometryPass>(*this);
    //auto imguiPass      = std::make_shared<ImGuiPass>(*this, geometryPass);

    //mRenderGraphRoot    = std::make_unique<PresentPass>(*this, imguiPass);
    //mRenderPassesSorted = createSortedRenderPassList(*mRenderGraphRoot);
}


CoContext
DefaultRendererImpl::context()
{
    return mContext.get();
}


const CoContext
DefaultRendererImpl::context() const
{
    return mContext.get();
}


ResourceManager&
DefaultRendererImpl::resourceManager()
{
    return mResourceManager;
}


const ResourceManager& 
DefaultRendererImpl::resourceManager() const
{
    return mResourceManager;
}


RenderObject*
DefaultRendererImpl::createRenderObject()
{
    return mRenderObjects.emplace();
}


void
DefaultRendererImpl::destroyRenderObject(RenderObject* renderObject)
{
    mRenderObjects.erase(static_cast<RenderObjectImpl*>(renderObject));
}


void
DefaultRendererImpl::render(const CameraInfo& camera)
{
    CoSwapchainImageInfo info{};
    if (coSwapchainAcquireNextImage(mSwapchain.get(), nullptr, &info) != CO_SUCCESS)
    {
        return;
    }

    CoCommandQueue queue;
    if (coContextGetGraphicsQueue(mContext.get(), &queue) != CO_SUCCESS)
    {
        return;
    }

    CoCommandBufferCreateConfig commandBufferConfig{};
    Coral::CommandBufferPtr commandBuffer;
    if (coCommandQueueCreateCommandBuffer(queue, &commandBufferConfig, std::out_ptr(commandBuffer)) != CO_SUCCESS)
    {
        return;
    }

    coCommandBufferBegin(commandBuffer.get());

    CoClearColor clearColor{ 0, CO_CLEAR_OP_CLEAR, { 1.f, 1.f, 1.f, 1.f } };
    CoClearDepthStencil clearDepth{ CO_CLEAR_OP_CLEAR, 1.f, 0 };

    CoBeginRenderPassInfo beginRenderPassInfo{};
    beginRenderPassInfo.framebuffer       = info.framebuffer;
    beginRenderPassInfo.pClearColors      = &clearColor;
    beginRenderPassInfo.clearColorsCount  = 1;
    beginRenderPassInfo.clearDepthStencil = &clearDepth;

    coCommandBufferBeginRenderPass(commandBuffer.get(), &beginRenderPassInfo);

    CoViewportInfo viewport
    {
        CoRectangle{ 0, 0, camera.camera.resolution().x, camera.camera.resolution().y },
        0.f,  1.f
    };

    coCommandBufferSetViewport(commandBuffer.get(), &viewport);
    coCommandBufferEndRenderPass(commandBuffer.get());
    coCommandBufferEnd(commandBuffer.get());

    std::vector<CoCommandBuffer> commandBuffers{ commandBuffer.get() };
    std::vector<CoSemaphore> waitSemaphores{ info.imageAcquiredSemaphore };

    CoCommandBufferSubmitInfo submitInfo{};
    submitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
    submitInfo.pCommandBuffers    = commandBuffers.data();
    submitInfo.pWaitSemaphores    = waitSemaphores.data();
    submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());

    Coral::FencePtr fence;
    CoFenceCreateConfig fenceConfig{};
    if (coContextCreateFence(mContext.get(), &fenceConfig, std::out_ptr(fence)) != CO_SUCCESS)
    {
        return;
    }

    coCommandQueueSubmit(queue, &submitInfo, fence.get());

    coFenceWait(fence.get());
}
