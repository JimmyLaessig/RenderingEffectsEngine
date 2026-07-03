#ifndef ENGINE_RENDERING_GEOMETRYPASS_HPP
#define ENGINE_RENDERING_GEOMETRYPASS_HPP

#include <Engine/Rendering/RenderPass.hpp>

#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>


namespace Reef::Rendering
{

class ENGINE_API GeometryPass : public RenderPass
{
public:

	GeometryPass(DefaultRenderer& renderer);

	void recordCommandBuffer(const SceneView& sceneView, 
		                     Coral::CommandBuffer& commandBuffer) override;

	Coral::ImagePtr colorImage()
	{
		return mColorImage;
	}

	Coral::ImagePtr depthImage()
	{
		return mDepthImage;
	}

	Coral::Framebuffer* framebuffer()
	{
		return mFramebuffer.get();
	}

private:

	struct RenderObjectResolved
	{
		PrimitiveResource* primitive{ nullptr };

		MaterialFunctionResource* materialFunctionResource{ nullptr };

		MaterialResource* materialResource{ nullptr };

		TransformResource* transformResouce{ nullptr };
	};

	struct SceneViewResolved
	{
		std::vector<RenderObjectResolved> renderObjects;
	};

	SceneViewResolved updateResources(const Reef::Rendering::SceneView& sceneView);

	std::unique_ptr<Reef::Rendering::UniformBuffer> mPerFrameDataUniformBuffer;

	Coral::ImagePtr mColorImage;
	Coral::ImagePtr mDepthImage;

	Coral::FramebufferPtr mFramebuffer;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_GEOMETRYPASS_HPP
