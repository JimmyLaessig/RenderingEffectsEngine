#ifndef ENGINE_RENDERING_GAMECANVAS_HPP
#define ENGINE_RENDERING_GAMECANVAS_HPP

#include <Engine/System.hpp>

#include <Engine/Rendering/Renderer.hpp>

#include <Engine/Platform/Window.hpp>

#include <memory>


namespace Reef::Rendering
{

class ENGINE_API GameCanvas : public Canvas
{
public:

	static std::unique_ptr<Canvas> create(Reef::IWindow& window);

	GameCanvas(Reef::IWindow& window);

	void prepareRender() override;

	FrameData currentFrameData() override;

	void finishRender() override;

	Coral::Context& context() override;

	Coral::Swapchain* swapchain() override;

private:

	GameCanvas() = default;

	Coral::ContextPtr mContext;

	Coral::SwapchainPtr mSwapchain;

	std::vector<Coral::SemaphorePtr> mRenderFinishedSemaphores;

	FrameData mCurrentFrameData{};

};

} // namespace Reef

#endif // !ENGINE_RENDERING_GAMECANVAS_HPP
