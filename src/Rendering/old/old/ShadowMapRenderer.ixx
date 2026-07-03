module;

#include <memory>

export module Engine.Rendering.ShadowMapRenderingTechnique;

import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class ShadowMapRenderingTechnique
{
public:

	bool initialize(RenderLib::Context& context, unsigned int width, unsigned int height);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

	RenderLib::Sampler* texture();

	std::shared_ptr<RenderLib::Framebuffer> framebuffer();

private:

	std::shared_ptr<RenderLib::Context> mContext;

	std::shared_ptr<RenderLib::Shader> mDepthShader;

	std::shared_ptr<RenderLib::Framebuffer> mFramebuffer;

	std::shared_ptr<RenderLib::PipelineState> mPipelineState;

	RenderLib::Sampler* mDepthTexture;
};

} // namespace Rendering

} // namespace Reef