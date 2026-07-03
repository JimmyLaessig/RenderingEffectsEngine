#include <Engine/Rendering/SwapchainRenderTarget.hpp>

#include <Coral/Swapchain.hpp>
#include <Coral/Framebuffer.hpp>
#include <Coral/Semaphore.hpp>

using namespace Reef::Rendering;


void
SwapchainRenderTarget::acquireNextSwapchainImage()
{
	mSwapchain->acquireNextSwapchainImage(nullptr);
}


Coral::Framebuffer*
SwapchainRenderTarget::framebuffer()
{
	return mSwapchain->currentSwapchainImage().framebuffer;
}


Coral::Semaphore*
SwapchainRenderTarget::renderTargetReadySemaphore()
{
	return mSwapchain->currentSwapchainImage().imageAvailableSemaphore;
}


Coral::Semaphore*
SwapchainRenderTarget::renderFinishedSemaphore()
{
	return nullptr;
}
