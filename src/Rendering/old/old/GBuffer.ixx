module;

#include <memory>

export module Engine.Rendering.GBuffer;

import RenderLib.RAII;

namespace Reef
{
namespace Rendering
{

///
/**
 * GBuffer Layout:
 * Texture0: 32-bit depth
 * Texture1: R: diffuseColor.r
 *			 G: diffuseColor.g,
 *			 B: diffuseColor.b
 *			 A: unused
 * Texture2: R: normal.x (world space)
 *			 G: normal.y (world space)
 *			 B: normal.y (world space)
 *			 A: unused
 * Texture3: R: occlusion
 *			 G: roughness
 *			 B: metallic
 *			 A: MaterialMode
 * Texture4: R: velocity.x (screen space)
 *			 G: velocity.y (screen space)
 *			 B: unused
 *			 A: unused
 */
 /// </summary>
class GBuffer
{
public:

	bool initialize(RenderLib::Context& context, uint32_t width, uint32_t height);

	bool resize(uint32_t width, uint32_t height);

	RenderLib::Sampler* baseColorTexture();

	RenderLib::Sampler* normalTexture();

	RenderLib::Sampler* materialTexture();

	RenderLib::Sampler* depthTexture();

	RenderLib::Framebuffer* framebuffer();

	uint32_t width();

	uint32_t height();

private:

	RenderLib::Context* mContext{ nullptr };

	RenderLib::RAII::SamplerPtr mBaseColorSampler;
	RenderLib::RAII::SamplerPtr mNormalSampler;
	RenderLib::RAII::SamplerPtr mMaterialSampler;
	RenderLib::RAII::SamplerPtr mDepthSampler;

	RenderLib::RAII::Texture2DPtr mBaseColorTexture;
	RenderLib::RAII::Texture2DPtr mNormalTexture;
	RenderLib::RAII::Texture2DPtr mMaterialTexture;
	RenderLib::RAII::Texture2DPtr mDepthTexture;

	RenderLib::RAII::FramebufferPtr mFramebuffer;

	uint32_t mWidth{ 0 };

	uint32_t mHeight{ 0 };
};

} // namespace Rendering

} // namespace Reef

