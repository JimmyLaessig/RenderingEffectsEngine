module;

#include <array>

export module Engine.Rendering.PostprocessingEffect;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

namespace Reef
{

namespace Rendering
{

class PostprocessingEffect
{
public:

	/*bool initialize(RenderLib::Context& context, GBuffer& gBuffer, uint32_t width, uint32_t height);

	void resize(uint32_t width, uint32_t height);

	void recordCommandBuffer(SceneView& view, RenderLib::CommandQueue& commandQueue);

	RenderLib::Sampler* occlusionTexture() { return mOcclusionTexture; }

	std::shared_ptr<RenderLib::Framebuffer> framebuffer() override { return mBlurPass.framebuffer(); };


private:

	std::array<Math::Vec3, 16> mKernel;

	RenderLib::Sampler* mNoiseTexture;

	RenderLib::Sampler* mDepthTexture;

	RenderLib::Sampler* mNormalTexture;

	RenderLib::Sampler* mMaterialTexture;

	RenderLib::Sampler* mOcclusionTexture;
	
	BlurPass mBlurPass;

	float mRadius{ 0.1 };*/
};

} // namespace Rendering

} // namespace Reef
