module;

#include <glm/glm.hpp>

#include <vector>

module Engine.Rendering.SceneRenderer;

import Engine.Rendering.TextureResource;
import Engine.Rendering.PrimitiveResource;
import Engine.Rendering.RenderResource;
import Engine.Rendering.SceneView;

import Engine.SkyLight;

import Engine.Texture;

import RenderLib;


using namespace Reef::Rendering;


bool
SceneRenderer::initialize(RenderLib::Context& context,
						  uint32_t width, uint32_t height,
						  RenderLib::Framebuffer& framebuffer)
{
	mContext		= &context;
	mFramebuffer	= &framebuffer;

	return mGeometryRenderer.initialize(context, width, height);/* &&
		   mLightingPass.initialize(context, mGeometryRenderer.gBuffer()) &&
		   mTonemappingTechnique.initialize(context, mLightingPass.framebuffer()->colorAttachment(0)) &&
		   mGammaCorrectionTechnique.initialize(context, mTonemappingTechnique.framebuffer()->colorAttachment(0)) &&
		   mFXAATechnique.initialize(context, mGammaCorrectionTechnique.framebuffer()->colorAttachment(0));*/
}


void
SceneRenderer::setSceneView(const SceneView& view)
{
	mSceneView = view;
}


RenderLib::CommandBuffer*
SceneRenderer::recordRenderCommands()
{
	updateRenderResource(mSceneView);
	mCommandBuffer = RenderLib::RAII::createCommandBuffer(mContext, {});
	mCommandBuffer->begin();
	if (auto cb = mGeometryRenderer.recordRenderCommands(mSceneView))
	{
		mCommandBuffer->cmdExecuteCommands(cb);
	}

	/*if (auto cb = mLightingPass.recordRenderCommands(mSceneView))
	{
		commandBuffer->cmdExecuteCommands(cb);
	}

	if (auto cb = mTonemappingTechnique.recordRenderCommands(mSceneView))
	{
		commandBuffer->cmdExecuteCommands(cb);
	}

	if (auto cb = mGammaCorrectionTechnique.recordRenderCommands(mSceneView))
	{
		commandBuffer->cmdExecuteCommands(cb);
	}

	if (auto cb = mFXAATechnique.recordRenderCommands(mSceneView))
	{
		commandBuffer->cmdExecuteCommands(cb);
	}*/

	/*mLightingPass.recordCommandBuffer(mSceneView, *mCommandQueue);
	mTonemappingTechnique.recordCommandBuffer(mSceneView, *mCommandQueue);
	mGammaCorrectionTechnique.recordCommandBuffer(mSceneView, *mCommandQueue);
	mFXAATechnique.recordCommandBuffer(mSceneView, *mCommandQueue);*/

	auto source = mGeometryRenderer.framebuffer();
	auto target = mFramebuffer;

	mCommandBuffer->cmdBlitFramebuffer(source,
									   target,
									   { 0, 0, source->width(), source->height() },
									   { 0, 0, target->width(), target->height() },
									   RenderLib::BlitAttachment::COLOR);

	source = mGeometryRenderer.framebuffer();

	mCommandBuffer->cmdBlitFramebuffer(source,
									   target,
									   { 0, 0, source->width(), source->height() },
									   { 0, 0, target->width(), target->height() },
									   RenderLib::BlitAttachment::DEPTH);

	mCommandBuffer->end();
	return mCommandBuffer.get();
}

GBuffer&
SceneRenderer::gBuffer()
{
	return mGeometryRenderer.gBuffer();
}


void 
SceneRenderer::updateRenderResource(SceneView& view)
{
	//auto& resourceManager = Engine::Rendering::Renderer::instance().resourceManager();
	//
	//for (auto& ro : view.renderObjects)
	//{	
	//	resourceManager.updateResource(*ro.primitive);
	//	resourceManager.updateResource(*ro.material);
	//}

	//for (auto& light : view.skyLights)
	//{
	//	resourceManager.updateResource(*light->skyLightTexture());
	//	resourceManager.updateResource(*light->irradianceTexture());
	//}
}