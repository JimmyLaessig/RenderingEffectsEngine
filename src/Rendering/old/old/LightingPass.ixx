module;

#include <memory>

export module Engine.Rendering.LightingPass;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SkyLightTechnique;
import Engine.Rendering.DirectionalLightRenderer;
import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

import Engine.Texture;

import RenderLib;

export struct ImageLight
{
	std::shared_ptr<Engine::Texture> environmentTexture;
	std::shared_ptr<Engine::Texture> irradianceTexture;
	// TODO add other texture for image based light
};

namespace Reef
{

namespace Rendering
{

class LightingPass
{
public:

	bool initialize(RenderLib::Context& context,
					GBuffer& gBuffer);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

	std::shared_ptr<RenderLib::Framebuffer> framebuffer();

	bool resize(uint32_t width, uint32_t height);

private:

	GBuffer* mGBuffer{ nullptr };

	std::shared_ptr<RenderLib::Context> mContext;

	std::shared_ptr<RenderLib::Texture2D> mTexture;

	std::shared_ptr<RenderLib::Framebuffer> mFramebuffer;

	SkyLightRenderer mSkyLightRenderer;

	DirectionalLightRenderer mDirectionalLightRenderer;
};

} // namespace Rendering

} // namespace Reef