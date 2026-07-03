module;

#include <memory>
#include <optional>
#include <unordered_map>

export module Engine.Rendering.SkyLightTechnique;

import Engine.Rendering.SkyLightData;

import Engine.Rendering.SSAORenderer;
import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.GBuffer;
import Engine.Rendering.SceneView;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class SkyLightRenderer
{
public:

	bool initialize(RenderLib::Context& context,
					std::shared_ptr<RenderLib::Framebuffer> target, 
					GBuffer& gBuffer);

	void update(const SceneView& view);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands();

private:

	std::shared_ptr<RenderLib::Context> mContext;

	SSAORenderer mSSAORenderer;

	std::shared_ptr<RenderLib::Shader> mShader;

	std::shared_ptr<RenderLib::PipelineState> mPipelineState;

	RenderLib::Sampler* mDepthTexture;

	RenderLib::Sampler* mMaterialTexture;

	RenderLib::Sampler* mNormalTexture;

	RenderLib::Sampler* mDiffuseColorTexture;

	RenderLib::Sampler* occlusionTexture;

	std::shared_ptr<RenderLib::Framebuffer> mFramebuffer;

	std::unordered_map<Engine::Rendering::SkyLightData*, std::shared_ptr<RenderLib::CommandBuffer>> mSkyLightCommands;
};

} // namespace Rendering

} // namespace Reef