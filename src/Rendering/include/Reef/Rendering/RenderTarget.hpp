#ifndef ENGINE_RENDERING_RENDERTARGET_HPP
#define ENGINE_RENDERING_RENDERTARGET_HPP

#include <Engine/System.hpp>

#include <Coral/CoralFwd.hpp>

namespace Reef::Rendering
{

class ENGINE_API RenderTarget
{
public:

	virtual ~RenderTarget() = default;

	virtual Coral::Framebuffer* framebuffer() = 0;

	virtual Coral::Semaphore* renderTargetReadySemaphore() = 0;

	virtual Coral::Semaphore* renderFinishedSemaphore() = 0;

};

} // namespace Reef::Rendering

#endif // !ENGINE_RENDERING_RENDERTARGET_HPP
