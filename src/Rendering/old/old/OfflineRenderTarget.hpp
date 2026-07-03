#ifndef ENGINE_RENDERING_DEFAULTRENDERER_HPP
#define ENGINE_RENDERING_DEFAULTRENDERER_HPP

#include <Engine/Rendering/IRenderer.hpp>

#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <Engine/Rendering/RenderPass.hpp>

#include <Engine/Platform/Window.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>
#include <unordered_set>


namespace Reef::Rendering
{

class ENGINE_API DefaultRenderer : public IRenderer
{
public:

	static std::unique_ptr<DefaultRenderer> create(Reef::IWindow& window);

	void render(SceneView&& sceneView) override;

	Coral::Context& context() override;

	ResourceManager& resourceManager();

	Coral::Framebuffer& framebuffer();

	Coral::Swapchain* swapchain();

private:

	DefaultRenderer() = default;

	Coral::ContextPtr mContext;

	Coral::SwapchainPtr mSurface;

	std::unique_ptr<ResourceManager> mResourceManager;

	std::vector<std::unique_ptr<RenderPass>> mRenderPasses;

	std::unique_ptr<Reef::Rendering::UniformBuffer> mPerFrameDataUniformBuffer;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_DEFAULTRENDERER_HPP
