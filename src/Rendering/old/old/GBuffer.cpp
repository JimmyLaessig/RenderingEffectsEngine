module;

#include <array>

module Engine.Rendering.GBuffer;

using namespace Reef::Rendering;


bool
GBuffer::initialize(RenderLib::Context& context, uint32_t width, uint32_t height)
{
	mContext	= &context;
	
	return resize(width, height);
}


bool
GBuffer::resize(uint32_t width, uint32_t height)
{
	mWidth	= width;
	mHeight = height;

	mDepthTexture		= RenderLib::RAII::createTexture2D(mContext, { RenderLib::PixelFormat::DEPTH24_STENCIL8, mWidth, mHeight, false });
	mBaseColorTexture	= RenderLib::RAII::createTexture2D(mContext, { RenderLib::PixelFormat::RGBA32_F, mWidth, mHeight, false });
	mNormalTexture		= RenderLib::RAII::createTexture2D(mContext, { RenderLib::PixelFormat::RGBA32_F, mWidth, mHeight, false });
	mMaterialTexture	= RenderLib::RAII::createTexture2D(mContext, { RenderLib::PixelFormat::RGBA32_F, mWidth, mHeight, false });

	std::array<RenderLib::ColorAttachment, 3> colorAttachments
	{
		RenderLib::ColorAttachment{ 0, mBaseColorTexture.get() },
		RenderLib::ColorAttachment{ 1, mNormalTexture.get()	},
		RenderLib::ColorAttachment{ 2, mMaterialTexture.get()	},
	};

	RenderLib::FramebufferConfig config{};
	config.depthAttachment	= mDepthTexture.get();
	config.colorAttachments = colorAttachments;
	mFramebuffer			= RenderLib::RAII::createFramebuffer(mContext, config);

	mDepthSampler		= RenderLib::RAII::createSampler(mContext, { mDepthTexture.get(),		RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::WrapMode::ONE });
	mBaseColorSampler	= RenderLib::RAII::createSampler(mContext, { mBaseColorTexture.get(),	RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::WrapMode::CLAMP_TO_EDGE });
	mNormalSampler		= RenderLib::RAII::createSampler(mContext, { mNormalTexture.get(),		RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::WrapMode::CLAMP_TO_EDGE });
	mMaterialSampler	= RenderLib::RAII::createSampler(mContext, { mMaterialTexture.get(),	RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::WrapMode::CLAMP_TO_EDGE });

	return true;
}


uint32_t
GBuffer::width()
{
	return mWidth;
}


uint32_t
GBuffer::height()
{
	return mHeight;
}


RenderLib::Sampler*
GBuffer::baseColorTexture()
{
	return mBaseColorSampler.get();
}


RenderLib::Sampler*
GBuffer::normalTexture()
{
	return mNormalSampler.get();
}


RenderLib::Sampler*
GBuffer::materialTexture()
{
	return mMaterialSampler.get();
}


RenderLib::Sampler*
GBuffer::depthTexture()
{
	return mDepthSampler.get();
}


RenderLib::Framebuffer*
GBuffer::framebuffer()
{
	return mFramebuffer.get();
}