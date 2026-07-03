module;

#include <random>
#include <span>

module Engine.Rendering.ShadowMapRenderingTechnique;

import Engine.Rendering.ShaderManager;
import Engine.Rendering.UniformBufferFactory;
import Engine.Rendering.PrimitiveResource;

using namespace Reef::Rendering;

bool
ShadowMapRenderingTechnique::initialize(RenderLib::Context& context, uint32_t width, uint32_t height)
{
	/*mContext = context;

	mDepthShader = Engine::Rendering::ShaderManager::find("DepthShader");

	RenderLib::Texture2DConfig depthTextureConfig{};
	depthTextureConfig.width		= width;
	depthTextureConfig.height		= height;
	depthTextureConfig.format		= RenderLib::PixelFormat::DEPTH32_F;
	depthTextureConfig.generateMips = false;
	auto depthTexture = RenderLib::createTexture2D(context, depthTextureConfig);

	RenderLib::SamplerConfig depthSamplerConfig{};
	depthSamplerConfig.minFilter	= RenderLib::Filter::NEAREST;
	depthSamplerConfig.magFilter	= RenderLib::Filter::NEAREST;
	depthSamplerConfig.mipmapFilter = RenderLib::Filter::NEAREST;
	depthSamplerConfig.texture		= depthTexture;
	mDepthTexture = RenderLib::createSampler(context, depthSamplerConfig);

	RenderLib::FramebufferConfig framebufferConfig{};
	framebufferConfig.depthAttachment = depthTexture;
	mFramebuffer = RenderLib::createFramebuffer(context, framebufferConfig);

	RenderLib::PipelineStateConfig psConfig{};
	psConfig.blendMode			= RenderLib::BlendMode::None;
	psConfig.depthTestMode		= RenderLib::DepthTestMode{ true, RenderLib::CompareOp::LESS_OR_EQUAL, { 1.1, 4.0 } };
	psConfig.faceCullingMode	= RenderLib::FaceCullingMode::BackFaceCulling;
	mPipelineState = RenderLib::createPipelineState(context, psConfig);*/

	return true;
}


std::shared_ptr<RenderLib::CommandBuffer>
ShadowMapRenderingTechnique::recordRenderCommands(Engine::Rendering::SceneView& view)
{
	//auto commandBuffer = RenderLib::createCommandBuffer(mContext, { "ShadowMapping_DepthPass" });
	/*commandBuffer->begin();
	commandBuffer->cmdClearAttachments(mFramebuffer, RenderLib::ClearDepth{ 1.0, 0 });

	commandBuffer->cmdBindFramebuffer(mFramebuffer);
	commandBuffer->cmdBindPipelineState(mPipelineState);
	commandBuffer->cmdBindShader(mDepthShader);
	commandBuffer->cmdSetViewport({ 0, 0, mFramebuffer->width(), mFramebuffer->height() });

	for (auto& ro : view.renderObjects)
	{
		if (!ro.material->castShadow())
		{
			continue;
		}

		auto& resource = static_cast<Engine::Rendering::PrimitiveResource&>(ro.primitive->RenderResource());

		commandBuffer->cmdBindIndexBuffer(resource.indices());
		commandBuffer->cmdVertexBuffer(0, resource.positions());

		auto modelViewProjectionMatrix = view.lightSpaceMatrix * ro.localToWorldMatrix;

		std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
		std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

		uint32_t location{ 0 };
		if (mDepthShader->getUniformLocation("modelViewProjectionMatrix", location))
		{
			uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, modelViewProjectionMatrix) });
		}

		RenderLib::DescriptorSetConfig uniformsConfig{};
		uniformsConfig.uniformBuffers = uniformBuffers;
		uniformsConfig.uniformSamplers = uniformSamplers;
		auto uniforms = RenderLib::createDescriptorSet(mContext, uniformsConfig);
		commandBuffer->cmdBindDescriptorSet(uniforms);
		commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);
	}

	commandBuffer->end();*/
	//return commandBuffer;
	return nullptr;
}


RenderLib::Sampler*
ShadowMapRenderingTechnique::texture()
{
	return mDepthTexture;
}


std::shared_ptr<RenderLib::Framebuffer>
ShadowMapRenderingTechnique::framebuffer()
{
	return mFramebuffer;
}
