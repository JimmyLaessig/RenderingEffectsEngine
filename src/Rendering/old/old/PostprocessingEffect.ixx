export module Engine.Rendering.PostprocessingEffect;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

import glm;

import <array>;

namespace Reef
{

namespace Rendering
{

class PostprocessingEffect
{
public:

	/*bool initialize(std::shared_ptr<::Rendering::Context> context, GBuffer& gBuffer, uint32_t width, uint32_t height);

	void resize(uint32_t width, uint32_t height);

	void recordCommandBuffer(SceneView& view, ::Rendering::CommandQueue& commandQueue);

	std::shared_ptr<::Rendering::Sampler> occlusionTexture() { return mOcclusionTexture; }

	std::shared_ptr<::Rendering::Framebuffer> framebuffer() override { return mBlurPass.framebuffer(); };


private:

	std::array<glm::vec3, 16> mKernel;

	std::shared_ptr<::Rendering::Sampler> mNoiseTexture;

	std::shared_ptr<::Rendering::Sampler> mDepthTexture;

	std::shared_ptr<::Rendering::Sampler> mNormalTexture;

	std::shared_ptr<::Rendering::Sampler> mMaterialTexture;

	std::shared_ptr<::Rendering::Sampler> mOcclusionTexture;
	
	BlurPass mBlurPass;

	float mRadius{ 0.1 };*/
};

} // namespace Rendering

} // namespace Reef
