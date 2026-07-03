#include <Engine/Core/EngineImpl.hpp>

#include <Engine/SceneGraph/Scene.hpp>

#include <Engine/Core/Constants.hpp>

#include <Engine/Rendering/DefaultRenderer.hpp>

#include <Engine/Rendering/GameCanvas.hpp>

#include <imgui.h>
#include <imgui_threaded_rendering/imgui_threaded_rendering.h>
#include <backends/imgui_impl_win32.h>

using namespace Reef;


std::unique_ptr<Engine>
Engine::createEngine(IWindow& window)
{
	return std::make_unique<EngineImpl>(window);
}


EngineImpl::EngineImpl(IWindow& window)
	: mWindow(window)
{
	mCanvas      = Rendering::GameCanvas::create(window);
	mRenderer    = Rendering::DefaultRenderer::create(mCanvas);
	mActiveScene = std::make_unique<SceneImpl>();
	mActiveScene->initialize(*this);

	updateViewport();
}


EngineImpl::~EngineImpl()
{
	// Make sure the render thread has stopped before destroying the renderer
	mRenderThread.flush();
	mRenderer.reset();
}


Scene*
EngineImpl::activeScene()
{
	return mActiveScene.get();
}


const Scene*
EngineImpl::activeScene() const
{
	return mActiveScene.get();
}


void
EngineImpl::updateFrameTime()
{
	mCurrentFrameTime.previousFrameTimestamp = mCurrentFrameTime.currentFrameTimestamp;
	mCurrentFrameTime.currentFrameTimestamp  = std::chrono::high_resolution_clock::now();
	auto delta                               = mCurrentFrameTime.currentFrameTimestamp - mCurrentFrameTime.previousFrameTimestamp;
	mCurrentFrameTime.deltaTime              = delta.count() * Reef::Constants<double>::NANOSECONDS_TO_SECONDS;

	if (mCurrentFrameTime.deltaTime == 0)
	{
		return;
	}

	if (mActiveScene)
	{
		mActiveScene->onUpdateFrame(mCurrentFrameTime);
	}
}


void
EngineImpl::updateViewport()
{
	glm::uvec2 windowSize = mWindow.clientRect().resolution;

	if (windowSize == mViewport.resolution)
	{
		return;
	}

	mViewport.resolution = windowSize;

	if (mActiveScene)
	{
		mActiveScene->onViewportChanged(mViewport);
	}
}


void
EngineImpl::updateUI()
{
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	mActiveScene->onUpdateUI();
	ImGui::Render();
}


void
EngineImpl::updateFrame()
{
	mWindow.processEvents();

	updateViewport();

	updateFrameTime();

	updateUI();

	render();
}


Viewport
EngineImpl::viewport() const
{
	return mViewport;
}


const IInput&
EngineImpl::input() const
{
	return mWindow;
}


IInput&
EngineImpl::input()
{
	return mWindow;
}


void
EngineImpl::render()
{
	bool expected = false;
	if (!mRenderInProgress.compare_exchange_strong(expected, true))
	{
		// Skipping rendering
		return;
	}
	mRenderInProgress = true;
	auto view     = mActiveScene->createSceneView();
	view.drawData = std::make_shared<ImDrawDataSnapshot>();
	view.drawData->SnapUsingSwap(ImGui::GetDrawData(), ImGui::GetTime());

	executeOnRenderThread([view = std::move(view), this] mutable
	{
		mRenderer->render(std::move(view));
		mRenderInProgress = false;
	});
}


std::future<void>
EngineImpl::executeOnRenderThread(std::function<void()> fun)
{
	return mRenderThread.push(std::move(fun));
}
