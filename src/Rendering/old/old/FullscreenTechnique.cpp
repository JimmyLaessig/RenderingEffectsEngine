module;

#include <array>
#include <vector>
#include <span>
#include <memory>

module Engine.Rendering.FullscreenTechnique;


import RenderLib;

using namespace Reef::Rendering;


bool
FullscreenTechnique::initialize(RenderLib::Context& context,
								std::shared_ptr<RenderLib::PipelineState> pipelineState,
								std::shared_ptr<RenderLib::Shader> shader,
								std::shared_ptr<RenderLib::DescriptorSet> uniforms,
								uint32_t width,
								uint32_t height,
								RenderLib::PixelFormat pixelFormat)
{
	//RenderLib::Texture2DConfig textureConfig{};
	//textureConfig.width = width;
	//textureConfig.height = height;
	//textureConfig.format = pixelFormat;
	//textureConfig.generateMips = false;
	//auto texture = RenderLib::createTexture2D(context, textureConfig);

	//return initialize(context, pipelineState, shader, uniforms, texture);
	return false;
}


bool
FullscreenTechnique::initialize(RenderLib::Context& context,
								std::shared_ptr<RenderLib::PipelineState> pipelineState,
								std::shared_ptr<RenderLib::Shader> shader,
								std::shared_ptr<RenderLib::DescriptorSet> uniforms,
								std::shared_ptr<RenderLib::Texture2D> texture)
{
	/*std::array colorAttachments{ RenderLib::ColorAttachment{ 0, texture. } };

	RenderLib::FramebufferConfig framebufferConfig{};
	framebufferConfig.colorAttachments = colorAttachments;

	auto framebuffer = RenderLib::createFramebuffer(context, framebufferConfig);
	
	return initialize(context, pipelineState, shader, uniforms, framebuffer);*/
	return false;
}


bool 
FullscreenTechnique::initialize(RenderLib::Context& context,
								std::shared_ptr<RenderLib::PipelineState> pipelineState,
								std::shared_ptr<RenderLib::Shader> shader,
								std::shared_ptr<RenderLib::DescriptorSet> uniforms,
								std::shared_ptr<RenderLib::Framebuffer> framebuffer)
{
	mContext		= &context;
	mFramebuffer	= framebuffer;

	mPipelineState	= pipelineState;
	mShader			= shader;
	mUniforms		= uniforms;

	return true;
}


RenderLib::CommandBuffer*
FullscreenTechnique::recordRenderCommands()
{
	/*mCommandBuffer = RenderLib::createCommandBuffer(mContext, {});

	commandBuffer->begin();

	commandBuffer->cmdBeginRenderPass({ mFramebuffer, { 0, 0, mFramebuffer->width(), mFramebuffer->height() } });
	commandBuffer->cmdBindPipelineState(mPipelineState);
	commandBuffer->cmdBindShader(mShader);
	commandBuffer->cmdBindDescriptorSet(mUniforms);
	commandBuffer->cmdBindIndexBuffer(mFullscreenQuad.mIndices);
	commandBuffer->cmdVertexBuffer(0, mFullscreenQuad.mPositions);
	commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);

	commandBuffer->cmdEndRenderPass();

	commandBuffer->end();

	return commandBuffer;*/

	return nullptr;
}


RenderLib::Framebuffer*
FullscreenTechnique::framebuffer()
{
	return mFramebuffer.get();
}


RenderLib::Texture2D*
FullscreenTechnique::texture()
{
	return mFramebuffer->colorAttachment(0);
}
