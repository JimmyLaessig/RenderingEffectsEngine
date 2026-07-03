#ifndef ENGINE_RENDERING_RENDERPASS_HPP
#define ENGINE_RENDERING_RENDERPASS_HPP

#include <memory>
#include <unordered_map>

#include <Engine/Core/NonCopyable.hpp>

#include <Coral/Coral.hpp>

#include <glm/glm.hpp>

#include <Engine/Rendering/Renderer.hpp>

namespace Reef::Rendering
{

class SceneView;

enum class CommandQueueType
{
	GRAPHICS,
	TRANSFER,
	COMPUTE,
};

class DefaultRenderer;

class ENGINE_API RenderPass : public NonCopyable
{
public:

	template<typename ...T>
	RenderPass(std::string_view name, DefaultRenderer& renderer, T&&... dependencies)
		: RenderPass(name, renderer)
	{
		mDependencies = { std::forward<T>(dependencies)... };
	}

	RenderPass(std::string_view name, DefaultRenderer& renderer);

	virtual ~RenderPass() = default;

	/// Render the scene view
	void render(const SceneView& sceneView);

	// Invoked if the render resolution has changed
	virtual void onResolutionChanged(const glm::uvec2& resolution);

	/// Get the name of the render pass
	const std::string& name();

	/// Get the renderer
	DefaultRenderer& renderer();

	Coral::Context& context();

	/// This semaphore is signaled once this render pass has finished.
	/*
	 * Render passes that depend on outputs of other render passes must ensure to wait for the render-finished
	 * semaphores of it's dependencies.
	 */
	virtual Coral::Semaphore* renderPassFinishedSemaphore();

	/// 
	virtual std::vector<Coral::Semaphore*> renderPassReadySemaphores();

	virtual Coral::Framebuffer* framebuffer() = 0;

	std::vector<RenderPass*> dependencies();

protected:

	virtual void recordCommandBuffer(const SceneView& sceneView,
		                             Coral::CommandBuffer& commandBuffer) = 0;

	std::vector<std::shared_ptr<RenderPass>> mDependencies;

private:

	std::string mName;

	DefaultRenderer& mRenderer;

	Coral::SemaphorePtr mRenderPassFinishedSemaphore;

	std::vector<Coral::CommandBufferPtr> mCommandBuffers;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_RENDERPASS_HPP
