module;

#include <random>
#include <cmath>
#include <memory>

module Engine.Rendering.DirectionalLightRenderer;

import Engine.Rendering.ShaderManager;

import Engine.Rendering.UniformBufferFactory;



using namespace Reef::Rendering;


bool
DirectionalLightRenderer::initialize(RenderLib::Context& context,
									 std::shared_ptr<RenderLib::Framebuffer> framebuffer, 
									 GBuffer& gBuffer)
{
	//mContext	= context;
	//mShader		= ShaderManager::find("DirectionalLight");
	//mGBuffer	= &gBuffer;

	//RenderLib::PipelineStateConfig pipelineStateConfig{};
	//pipelineStateConfig.blendMode		= { RenderLib::BlendMode::Additive };
	//pipelineStateConfig.depthTestMode	= { RenderLib::DepthTestMode::None };
	//pipelineStateConfig.faceCullingMode = { RenderLib::FaceCullingMode::BackFaceCulling };
	//auto pipelineState					= RenderLib::createPipelineState(mContext, pipelineStateConfig);
	// 
	//return mLightingTechnique.initialize(mContext, mShader, pipelineState, framebuffer) && 
	//	   mShadowMappingTechnique.initialize(mContext, 2048, 2048) && 
	//	   initializeShadowMapOffsetTexture();

	return true;
}


float
jitter()
{
	static std::default_random_engine engine;
	static std::uniform_real_distribution<float> distribution(-0.5f, 0.5f);

	return distribution(engine);
}


bool
DirectionalLightRenderer::initializeShadowMapOffsetTexture()
{
	//constexpr auto PI			= 3.14159265359f;
	//constexpr auto TWO_PI		= PI * 2.0f;
	//constexpr auto PI_OVER_TWO	= PI * 0.5f;

	//uint32_t textureSize = 16;
	//uint32_t filterSize = 8;

	//std::vector<Math::Vec2> data(textureSize * textureSize * filterSize * filterSize);

	//uint32_t i{ 0 };
	//for (uint32_t y = 0; y < textureSize; ++y)
	//{
	//	for (uint32_t x = 0; x < textureSize; ++x)
	//	{
	//		for (float v = filterSize - 1; v >= 0; --v)
	//		{
	//			for (float u = 0; u < filterSize; ++u)
	//			{
	//				float fx = (u + 0.5f + jitter()) / filterSize;
	//				float fy = (u + 0.5f + jitter()) / filterSize;

	//				data[i] = {
	//					std::sqrt(fy) * std::cos(TWO_PI * fx),
	//					std::sqrt(fy) * std::sin(TWO_PI * fx),
	//				};
	//				++i;
	//			}
	//		}
	//	}
	//}

	//RenderLib::Texture3DConfig config{};
	//config.format		= RenderLib::PixelFormat::RG32_F;
	//config.width		= filterSize * filterSize;
	//config.height		= textureSize;
	//config.depth		= textureSize;
	//config.generateMips = false;
	//config.data			= data.data();
	//auto texture		= RenderLib::createTexture3D(mContext, config);

	//RenderLib::SamplerConfig samplerConfig{};
	//samplerConfig.texture		= texture;
	//samplerConfig.minFilter		= RenderLib::Filter::NEAREST;
	//samplerConfig.magFilter		= RenderLib::Filter::NEAREST;
	//samplerConfig.mipmapFilter	= RenderLib::Filter::NEAREST;
	//samplerConfig.wrapMode		= RenderLib::WrapMode::REPEAT;
	//mShadowMapOffsetTexture		= RenderLib::createSampler(mContext, samplerConfig);

	return true;
}


std::shared_ptr<RenderLib::CommandBuffer>
DirectionalLightRenderer::recordRenderCommands(SceneView& view)
{
	//auto cb = RenderLib::createCommandBuffer(mContext, { "DirectionalLight" });

	//for (const auto& directionalLight : view.directionalLights)
	//{
	//	//// TODO: Every DirectionalLight should have it's own shadow map
	//	//mShadowMappingTechnique.recordRenderCommands(view, commandQueue);

	//	auto commandBuffer = RenderLib::createCommandBuffer(mContext, {});
	//	mLightingTechnique.beginCommandBuffer(commandBuffer);

	//	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	//	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	//	uint32_t location{ 0 };
	//	if (mShader->getUniformLocation("normalTexture", location))
	//		uniformSamplers.push_back({ location, mGBuffer->normalTexture()});

	//	if (mShader->getUniformLocation("baseColorTexture", location))
	//		uniformSamplers.push_back({ location, mGBuffer->baseColorTexture()});

	//	if (mShader->getUniformLocation("materialTexture", location))
	//		uniformSamplers.push_back({ location, mGBuffer->materialTexture()});

	//	if (mShader->getUniformLocation("depthTexture", location))
	//		uniformSamplers.push_back({ location, mGBuffer->depthTexture()});

	//	/*if (mShader->getUniformLocation("shadowMapTexture", location))
	//		uniformSamplers.push_back({ location, mShadowMappingTechnique.texture() });

	//	if (mShader->getUniformLocation("shadowMapOffsetTexture", location))
	//		uniformSamplers.push_back({ location, mShadowMapOffsetTexture });*/

	//	//if (mShader->getUniformLocation("inverseViewProjectionMatrix", location))
	//	//	uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, view.inverseViewProjectionMatrix) });

	//	//if (mShader->getUniformLocation("lightSpaceMatrix", location))
	//	//	uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, directionalLight->lightSpaceMatrix()) });

	//	if (mShader->getUniformLocation("lightDirection", location))
	//		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, directionalLight->direction()) });

	//	if (mShader->getUniformLocation("lightColor", location))
	//		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, directionalLight->color()) });

	//	RenderLib::DescriptorSetConfig uniformsConfig{};
	//	uniformsConfig.uniformBuffers = uniformBuffers;
	//	uniformsConfig.uniformSamplers = uniformSamplers;
	//	auto uniforms = RenderLib::createDescriptorSet(mContext, uniformsConfig);
	//	commandBuffer->cmdBindDescriptorSet(uniforms);

	//	mLightingTechnique.endCommandBuffer(commandBuffer);

	//	cb->cmdExecuteCommands(commandBuffer);
	//}

	return nullptr;
}
