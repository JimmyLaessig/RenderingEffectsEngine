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

using namespace Reef::Rendering;


class AcquireSwapchainImage : public RenderPass
{
public:

	AcquireSwapchainImage(DefaultRenderer& renderer)
		: RenderPass("AcquireSwapchainImage", renderer)
		, mSwapchain(renderer.swapchain())
	{
	}

	void render(const SceneView& sceneView) override
	{
		mCurrentSwapchainImageInfo = mSwapchain->acquireNextSwapchainImage(nullptr);
	}

	Coral::Semaphore& renderFinishedSemaphore() override
	{
		return *mCurrentSwapchainImageInfo.imageAvailableSemaphore;
	}

private:

	Coral::SwapchainImageInfo mCurrentSwapchainImageInfo{};

	Coral::Swapchain* mSwapchain{ nullptr };
};


class PresentPass : public RenderPass
{
public:

	template<typename ...T>
	PresentPass(DefaultRenderer& renderer, T&... dependencies)
		: RenderPass("PresentPass", renderer, std::forward<T&...>(dependencies...))
		, mSurface(renderer.swapchain())
	{
	}

	void render(const SceneView& sceneView) override
	{
		auto waitSems = waitSemaphores();

		Coral::PresentInfo presentInfo{};
		presentInfo.swapchain      = mSurface;
		presentInfo.waitSemaphores = waitSems;

		renderer().context().getGraphicsQueue()->submit(presentInfo);
	}

private:

	Coral::Swapchain* mSurface{ nullptr };
};


class ImGuiPass : public RenderPass
{
public:

	template<typename ...T>
	ImGuiPass(DefaultRenderer& renderer, T&... dependencies)
		: RenderPass("ImGuiPass", renderer, std::forward<T&...>(dependencies...))
		, mSurface(renderer.swapchain())
	{
		ImGui_ImplCoral_InitInfo initInfo{};
		initInfo.context   = &renderer.context();
		initInfo.swapchain = renderer.swapchain();
		ImGui_ImplCoral_Init(&initInfo);
		ImGui_ImplCoral_CreateFontsTexture();
	}


	~ImGuiPass()
	{
		ImGui_ImplCoral_DestroyFontsTexture();
		ImGui_ImplCoral_Shutdown();
	}


	void render(const SceneView&) override
	{
		ImGui_ImplCoral_NewFrame();

		auto& commandBuffer = beginCommandBuffer();

		Coral::ClearColor clearColor{ Coral::ClearOp::LOAD };
		Coral::ClearDepth clearDepth{ Coral::ClearOp::LOAD };

		Coral::BeginRenderPassInfo info{};
		info.framebuffer = &renderer().framebuffer();
		info.clearColor  = { &clearColor, 1 };
		info.clearDepth  = clearDepth;
		commandBuffer.cmdBeginRenderPass(info);

		ImGui_ImplCoral_RenderDrawData(ImGui::GetDrawData(), &commandBuffer);

		commandBuffer.cmdEndRenderPass();

		submitCommandBuffer();
	}

private:

	Coral::Swapchain* mSurface{ nullptr };
};


std::unique_ptr<DefaultRenderer>
DefaultRenderer::create(Reef::IWindow& window)
{
	Coral::ContextCreateConfig contextConfig{};
	contextConfig.graphicsAPI = Coral::GraphicsAPI::VULKAN;

	auto context = Coral::createContext(contextConfig);
	if (!context)
	{
		return nullptr;
	}

	Coral::SwapchainCreateConfig swapchainConfig{};
	swapchainConfig.nativeWindowHandle  = window.nativeWindowHandle();
	swapchainConfig.depthFormat         = Coral::PixelFormat::DEPTH24_STENCIL8;
	swapchainConfig.format              = Coral::PixelFormat::RGBA8_SRGB;
	swapchainConfig.swapchainImageCount = 2;
	swapchainConfig.lockToVSync         = false;

	auto surface = context.value()->createSwapchain(swapchainConfig);
	if (!surface)
	{
		return nullptr;
	}

	std::unique_ptr<DefaultRenderer> renderer(new DefaultRenderer);
	renderer->mContext         = std::move(context.value());
	renderer->mSurface         = std::move(surface.value());
	renderer->mResourceManager = std::make_unique<ResourceManager>(*renderer);

	auto accquireSwapchainImage = std::make_unique<AcquireSwapchainImage>(*renderer);
	auto geometryPass           = std::make_unique<GeometryPass>(*renderer, *accquireSwapchainImage);
	auto imguiPass              = std::make_unique<ImGuiPass>(*renderer, *geometryPass);
	auto presentPass            = std::make_unique<PresentPass>(*renderer, *imguiPass);

	renderer->mRenderPasses.push_back(std::move(accquireSwapchainImage));
	renderer->mRenderPasses.push_back(std::move(geometryPass));
	renderer->mRenderPasses.push_back(std::move(imguiPass));
	renderer->mRenderPasses.push_back(std::move(presentPass));

	return renderer;
}


Coral::Context&
DefaultRenderer::context()
{
	return *mContext;
}


ResourceManager&
DefaultRenderer::resourceManager()
{
	return *mResourceManager;
}


Coral::Framebuffer& 
DefaultRenderer::framebuffer()
{
	return *mSurface->getCurrentSwapchainImage().framebuffer;
}


Coral::Swapchain*
DefaultRenderer::swapchain()
{
	return mSurface.get();
}


void
DefaultRenderer::render(SceneView&& view)
{
	SceneView sceneView = view;

	for (auto& renderPass : mRenderPasses)
	{
		renderPass->beginFrame();
	}

	for (auto& renderPass : mRenderPasses)
	{
		renderPass->render(sceneView);
	}

	mContext->getGraphicsQueue()->waitIdle();
}
