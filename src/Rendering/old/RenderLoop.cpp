//#include <Engine/Rendering/DefaultRenderer.hpp>
//
//#include <Engine/Application/Application.hpp>
//
//#include <Engine/Rendering/RenderPass.hpp>
//#include <Engine/Rendering/GeometryPass.hpp>
//
//#include <glm/gtc/matrix_transform.hpp>
//
//#include <Coral/ImGui_Impl_Coral.hpp>
//
//#include <array>
//#include <memory>
//#include <ranges>
//#include <vector>
//
//using namespace Reef::Rendering;
//
//
//class PresentPass : public RenderPass
//{
//public:
//
//	template<typename ...T>
//	PresentPass(DefaultRenderer& renderer, T&... dependencies)
//		: RenderPass("PresentPass", renderer, std::forward<T&...>(dependencies...))
//		, mSurface(renderer.swapchain())
//	{
//	}
//
//	void render(const SceneView& sceneView) override
//	{
//		auto waitSems = waitSemaphores();
//
//		Coral::PresentInfo presentInfo{};
//		presentInfo.swapchain      = mSurface;
//		presentInfo.waitSemaphores = waitSems;
//
//		renderer().context().getGraphicsQueue()->submit(presentInfo);
//	}
//
//private:
//
//	Coral::Swapchain* mSurface{ nullptr };
//};
//
//
//void
//DefaultRenderer::render(SceneView&& view)
//{
//	SceneView sceneView = view;
//
//	for (auto& renderPass : mRenderPasses)
//	{
//		renderPass->beginFrame();
//	}
//
//	for (auto& renderPass : mRenderPasses)
//	{
//		renderPass->render(sceneView);
//	}
//
//	mContext->getGraphicsQueue()->waitIdle();
//}
