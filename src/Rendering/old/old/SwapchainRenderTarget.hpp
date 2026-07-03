#ifndef ENGINE_RENDERING_SWAPCHAINRENDERTARGET_HPP
#define ENGINE_RENDERING_SWAPCHAINRENDERTARGET_HPP

#include <Engine/Rendering/RenderTarget.hpp>


namespace Reef::Rendering
{

class ENGINE_API SwapchainRenderTarget : public RenderTarget
{
public:

	void acquireNextSwapchainImage();

	Coral::Framebuffer* framebuffer() override;

	Coral::Semaphore* renderTargetReadySemaphore() override;

	Coral::Semaphore* renderFinishedSemaphore() override;

private:

	Coral::SwapchainPtr mSwapchain;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_DEFAULTRENDERER_HPP
