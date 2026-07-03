module;

#include <array>
#include <vector>
#include <span>

module Engine.Rendering.LightingPass;

import Engine.Rendering.ShaderManager;

import RenderLib;

using namespace Reef::Rendering;


bool
LightingPass::initialize(RenderLib::Context& context,
						 GBuffer& gBuffer)
{
	//mContext = context;
	//mGBuffer = &gBuffer;

	//RenderLib::Texture2DConfig textureConfig{};
	//textureConfig.width			= gBuffer.width();
	//textureConfig.height		= gBuffer.height();
	//textureConfig.format		= RenderLib::PixelFormat::RGBA32_F;
	//textureConfig.generateMips	= false;
	//mTexture					= RenderLib::createTexture2D(mContext, textureConfig);

	//std::array colorAttachments =
	//{
	//	RenderLib::ColorAttachment{ 0, mTexture }
	//};

	//RenderLib::FramebufferConfig framebufferConfig{};
	//framebufferConfig.colorAttachments	= colorAttachments;
	//mFramebuffer						= RenderLib::createFramebuffer(mContext, framebufferConfig);
	//
	//return mSkyLightRenderer.initialize(mContext, mFramebuffer, gBuffer) &&
	//	   mDirectionalLightRenderer.initialize(mContext, mFramebuffer, gBuffer);

	return true;
}


std::shared_ptr<RenderLib::Framebuffer>
LightingPass::framebuffer()
{
	return mFramebuffer;
}


std::shared_ptr<RenderLib::CommandBuffer> 
LightingPass::recordRenderCommands(SceneView& view)
{
	//auto commandBuffer = RenderLib::createCommandBuffer(mContext, { "Clear light frame buffer" });
	//commandBuffer->begin();

	//std::array clearColors{ RenderLib::ClearColor{ { 0.0f, 0.0f, 0.0f, 0.0f }, 0 } };
	//commandBuffer->cmdClearAttachments(clearColors);

	//if (auto cb = mDirectionalLightRenderer.recordRenderCommands(view))
	//{
	//	commandBuffer->cmdExecuteCommands(cb);
	//}

	//if (auto cb = mSkyLightRenderer.recordRenderCommands(view))
	//{
	//	commandBuffer->cmdExecuteCommands(cb);
	//}

	//commandBuffer->end();

	//return commandBuffer;

	return nullptr;
}


bool 
LightingPass::resize(uint32_t width, uint32_t height)
{
	return true;
}