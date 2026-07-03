#ifndef ENGINE_CORE_ENGINEIMPL_HPP
#define ENGINE_CORE_ENGINEIMPL_HPP

#include <Engine/Core/Engine.hpp>
#include <Engine/SceneGraph/SceneImpl.hpp>
#include <Engine/Platform/Window.hpp>

#include <Engine/Rendering/Renderer.hpp>
#include <Engine/Core/Viewport.hpp>
#include <Engine/Core/FrameTime.hpp>

#include <Log20/AsyncTaskQueue.hpp>

namespace Reef
{

class EngineImpl : public Engine
{
public:

	EngineImpl(IWindow& window);

	virtual ~EngineImpl();

	Scene* activeScene() override;

	const Scene* activeScene() const override;

	void updateFrame() override;

	Viewport viewport() const override;

	const IInput& input() const override;

	IInput& input() override;

	void render();

	std::future<void> executeOnRenderThread(std::function<void()> fun);

private:

	void updateFrameTime();

	void updateViewport();

	void updateUI();

	IWindow& mWindow;

	FrameTime mCurrentFrameTime{};

	Viewport mViewport{};

	std::shared_ptr<Reef::Rendering::Canvas> mCanvas;

	std::unique_ptr<Reef::Rendering::IRenderer> mRenderer;

	Log::AsyncTaskQueue mRenderThread;

	std::unique_ptr<SceneImpl> mActiveScene;

	Reef::Event<FrameTime> mOnFrameUpdateEvent;

	Reef::Event<Viewport> mOnViewportChangedEvent;

	std::atomic<bool> mRenderInProgress{ false };

	std::atomic<float> mLastFrameTime{ 0.f };
};

} // namespace Reef

#endif // !#define ENGINE_CORE_ENGINEIMPL_HPP