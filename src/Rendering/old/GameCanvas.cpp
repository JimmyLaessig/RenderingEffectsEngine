#include <Engine/Rendering/GameCanvas.hpp>

#include <Coral/Coral.hpp>

using namespace Reef::Rendering;

std::unique_ptr<Canvas>
GameCanvas::create(Reef::IWindow& window)
{
    return std::make_unique<GameCanvas>(window);
}


GameCanvas::GameCanvas(Reef::IWindow& window)
{
    Coral::ContextCreateConfig contextConfig{};
    contextConfig.graphicsAPI = Coral::GraphicsAPI::VULKAN;

    mContext = Coral::createContext(contextConfig).value();

    Coral::SwapchainCreateConfig swapchainConfig{};
    swapchainConfig.nativeWindowHandle  = window.nativeWindowHandle();
    swapchainConfig.depthFormat         = Coral::PixelFormat::DEPTH24_STENCIL8;
    swapchainConfig.format              = Coral::PixelFormat::RGBA8_SRGB;
    swapchainConfig.swapchainImageCount = 2;
    swapchainConfig.lockToVSync         = false;

    mSwapchain = mContext->createSwapchain(swapchainConfig).value();

    for (size_t i = 0; i < mSwapchain->swapchainImageCount(); ++i)
    {
        mRenderFinishedSemaphores.push_back(mContext->createSemaphore().value());
    }
}


void
GameCanvas::prepareRender()
{
    auto info = mSwapchain->acquireNextSwapchainImage(nullptr);
    auto index = mSwapchain->currentSwapchainImageIndex();
    mCurrentFrameData = {
        info.framebuffer, 
        info.imageAvailableSemaphore, 
        mRenderFinishedSemaphores[index].get()
    };
}


Canvas::FrameData
GameCanvas::currentFrameData()
{
    return mCurrentFrameData;
}


void
GameCanvas::finishRender()
{
    Coral::PresentInfo presentInfo{};
    presentInfo.swapchain      = mSwapchain.get();
    presentInfo.waitSemaphores = std::span{ &mCurrentFrameData.renderFinishedSemaphore, 1 };
    mContext->getGraphicsQueue()->submit(presentInfo);

    mCurrentFrameData = {};

    mContext->getGraphicsQueue()->waitIdle();
}


Coral::Context&
GameCanvas::context()
{
    return *mContext;
}


Coral::Swapchain*
GameCanvas::swapchain()
{
    return mSwapchain.get();
}
