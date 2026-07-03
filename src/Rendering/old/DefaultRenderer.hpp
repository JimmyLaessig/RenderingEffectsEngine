#ifndef ENGINE_RENDERING_DEFAULTRENDERER_HPP
#define ENGINE_RENDERING_DEFAULTRENDERER_HPP

#include <Engine/Rendering/Renderer.hpp>

#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <Engine/Rendering/RenderPass.hpp>

#include <Engine/Platform/Window.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace Reef::Rendering
{

class ENGINE_API DefaultRenderer : public IRenderer
{
public:

	static std::unique_ptr<DefaultRenderer> create(std::shared_ptr<Canvas> canvas);

	void render(const SceneView& sceneView) override;

	Coral::Context& context() override;

	std::shared_ptr<Canvas> canvas();

	ResourceManager& resourceManager();


private:

	DefaultRenderer(std::shared_ptr<Canvas> canvas);

	std::shared_ptr<Canvas> mCanvas;

	std::unique_ptr<ResourceManager> mResourceManager;

	std::unique_ptr<RenderPass> mRenderGraphRoot;
	std::vector<RenderPass*> mRenderPassesSorted;

	std::unique_ptr<Reef::Rendering::UniformBuffer> mPerFrameDataUniformBuffer;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_DEFAULTRENDERER_HPP
