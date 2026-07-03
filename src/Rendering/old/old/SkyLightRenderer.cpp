module Engine.Rendering.SkyLightTechnique;

import Engine.Rendering.ShaderManager;
import Engine.Rendering.UniformBufferFactory;
import Engine.Rendering.TextureResource;
import Engine.SkyLight;

import RenderLib.CommandQueue;

using namespace Reef::Rendering;

bool 
SkyLightRenderer::initialize(RenderLib::Context& context,
							 std::shared_ptr<RenderLib::Framebuffer> framebuffer, 
							  GBuffer& gBuffer)
{
	/*if (!mSSAORenderer.initialize(context, gBuffer))
	{
		return false;
	}

	auto shader = ShaderManager::find("EnvironmentLight");

	RenderLib::PipelineStateConfig pipelineStateConfig{};
	pipelineStateConfig.blendMode		= RenderLib::BlendMode::Additive;
	pipelineStateConfig.depthTestMode	= RenderLib::DepthTestMode::None;
	pipelineStateConfig.faceCullingMode = RenderLib::FaceCullingMode::BackFaceCulling;
	auto pipelineState					= RenderLib::createPipelineState(mContext, pipelineStateConfig);

	RenderLib::SamplerConfig samplerConfig{};
	samplerConfig.texture = occlusionTexture;

	auto occlusionSampler = RenderLib::createSampler(mContext, samplerConfig);

	auto irradianceTexture = data.irradianceTexture();


	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	uint32_t location{ 0 };
	if (shader->getUniformLocation("depthTexture", location))
		uniformSamplers.push_back({ location, gBuffer.depthTexture() });

	if (shader->getUniformLocation("baseColorTexture", location))
		uniformSamplers.push_back({ location, gBuffer.baseColorTexture() });

	if (shader->getUniformLocation("normalTexture", location))
		uniformSamplers.push_back({ location, gBuffer.normalTexture() });

	if (shader->getUniformLocation("materialTexture", location))
		uniformSamplers.push_back({ location, gBuffer.materialTexture() });

	if (shader->getUniformLocation("occlusionTexture", location))
		uniformSamplers.push_back({ location, occlusionSampler });

	if (shader->getUniformLocation("irradianceTexture", location))
		uniformSamplers.push_back({ location, irradianceTexture });

	if (shader->getUniformLocation("inverseViewProjectionMatrix", location))
		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, glm::mat4()) });

	if (shader->getUniformLocation("cameraPosition", location))
		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, glm::mat4()) });

	if (shader->getUniformLocation("lightColor", location))
		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, data.color()) });

	RenderLib::DescriptorSetConfig uniformsConfig{};
	uniformsConfig.uniformBuffers = uniformBuffers;
	uniformsConfig.uniformSamplers = uniformSamplers;
	auto uniforms = RenderLib::createDescriptorSet(mContext, uniformsConfig);

	return FullscreenTechnique::initialize(context, pipelineState, shader, uniforms, framebuffer);*/

	return true;
}

//
//void
//SkyLightRenderer::update(const Engine::Rendering::SkyLightData& data)
//{
//
//}




//bool
//SkyLightRenderer::initialize(RenderLib::Context& context,
//							 std::shared_ptr<RenderLib::Framebuffer> target,
//							 GBuffer& gBuffer)
//{
//	mContext = context;
//	return mSSAORenderer.initialize(context, gBuffer);
//}


void
SkyLightRenderer::update(const SceneView& view)
{
	//for (auto& skyLight : view.skyLights)
	//{
	//	auto data = std::static_pointer_cast<SkyLightData>(skyLight->RenderResource());

	//	auto iter = mSkyLightRenderers.find(data.get());
	//	if (iter == mSkyLightRenderers.end())
	//	{
	//		SkyLightTechnique technique;

	//		if (technique.initialize(mContext, mFramebuffer))
	//		mSkyLightRenderers[data] = SkyLightTechnique();
	//	}
	//	mSkyLightRenderers[data] = 
	//}
}
	


std::shared_ptr<RenderLib::CommandBuffer> 
SkyLightRenderer::recordRenderCommands()
{
	/*auto cb = RenderLib::createCommandBuffer(mContext, {});

	cb->cmdExecuteCommands(mSSAOTechnique.recordRenderCommands());
	for (auto& technique : mSkyLightTechniques)
	{
		cb->cmdExecuteCommands(technique.recordRenderCommands());
	}

	return cb;*/
	return nullptr;
}