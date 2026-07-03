module;

#include <memory>

export module Engine.Rendering.DirectionalLightRenderer;

import Engine.Rendering.ShadowMapRenderingTechnique;
import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

import RenderLib;

namespace Reef
{
namespace Rendering
{

/// Implementation of a directional light with Cascaded shadow mapping[1] and Soft-edged shadows using pixel shader branching[2]
/**
 * [1] TODO
 * [2] https://developer.nvidia.com/gpugems/gpugems2/part-ii-shading-lighting-and-shadows/chapter-17-efficient-soft-edged-shadows-using
 */
class DirectionalLightRenderer
{
public:

	bool initialize(RenderLib::Context& context,
					std::shared_ptr<RenderLib::Framebuffer> framebuffer, 
					GBuffer& gBuffer);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

private:

	bool initializeShadowMapOffsetTexture();

	GBuffer* mGBuffer{ nullptr };

	std::shared_ptr<RenderLib::Context> mContext;

	std::shared_ptr<RenderLib::Shader> mShader;

	RenderLib::Sampler* mShadowMapOffsetTexture;

	ShadowMapRenderingTechnique mShadowMappingTechnique;

	//FullscreenTechnique mLightingTechnique;
};

} // namespace Rendering

} // namespace Reef