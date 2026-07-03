module;

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <format>
#include <array>
#include <vector>
#include <span>

module Engine.Rendering.SSAORenderer;

import Engine.Rendering.ShaderManager;
import Engine.Rendering.TextureResource;
import Engine.Rendering.UniformBufferFactory;
import Engine.Rendering.SceneView;

import RenderLib;



using namespace Reef::Rendering;

namespace
{

float random(float min, float max)
{
	auto randVal = std::rand();
	float value = randVal / float(RAND_MAX);

	return value * (max - min) + min;
}

} // namespace


bool
SSAOFirstPass::initialize(RenderLib::Context& context, 
						  std::shared_ptr<RenderLib::PipelineState> pipelineState,
						  GBuffer& gBuffer)
{
	/*auto shader	= Engine::Rendering::ShaderManager::find("AverageBlur");

	float i = 0;
	for (auto& sample : mKernel)
	{
		sample = Math::Vec3(random(-1.f, 1.f),
			random(-1.f, 1.f),
			random(0.f, 1.f));
		sample = Math::normalize(sample);
		sample *= random(0.f, 1.f);

		float scale = i / mKernel.size();

		scale = Math::mix(0.1f, 1.0f, scale * scale);

		sample *= scale;
		i++;
	}

	std::array<Math::Vec3, 16> noise;
	for (auto& value : noise)
	{
		value = Math::normalize(Math::Vec3(random(-1.0f, 1.0f),
										   random(-1.0f, 1.0f),
										   0.f));
	}

	RenderLib::Texture2DConfig noiseTextureConfig{};
	noiseTextureConfig.width		= 4;
	noiseTextureConfig.height		= 4;
	noiseTextureConfig.format		= RenderLib::PixelFormat::RGB32_F;
	noiseTextureConfig.alignment	= RenderLib::Alignment::BYTE;
	noiseTextureConfig.data			= noise.data();

	auto noiseTexture = RenderLib::createTexture2D(context, noiseTextureConfig);

	RenderLib::SamplerConfig samplerConfig{};
	samplerConfig.texture		= noiseTexture;
	samplerConfig.minFilter		= RenderLib::Filter::NEAREST;
	samplerConfig.magFilter		= RenderLib::Filter::NEAREST;
	samplerConfig.mipmapFilter	= RenderLib::Filter::NEAREST;
	samplerConfig.wrapMode		= RenderLib::WrapMode::REPEAT;
	mNoiseTexture				= RenderLib::createSampler(context, samplerConfig);

	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	mRadiusUniform					= UniformBufferFactory::createUniformBuffer(mContext, mRadius);
	mViewMatrixUniform				= UniformBufferFactory::createUniformBuffer(mContext, glm::mat4(1.0f));
	mProjectionMatrixUniform		= UniformBufferFactory::createUniformBuffer(mContext, glm::mat4(1.0f));
	mInverseProjectionMatrixUniform = UniformBufferFactory::createUniformBuffer(mContext, glm::mat4(1.0f));

	uint32_t location{ 0 };
	if (mShader->getUniformLocation("depthTexture", location))
		uniformSamplers.push_back({ location, gBuffer.depthTexture() });

	if (mShader->getUniformLocation("normalTexture", location))
		uniformSamplers.push_back({ location, gBuffer.normalTexture() });

	if (mShader->getUniformLocation("materialTexture", location))
		uniformSamplers.push_back({ location, gBuffer.materialTexture() });

	if (mShader->getUniformLocation("noiseTexture", location))
		uniformSamplers.push_back({ location, mNoiseTexture });

	if (mShader->getUniformLocation("radius", location))
		uniformBuffers.push_back({ location,  mRadiusUniform });

	if (mShader->getUniformLocation("projectionMatrix", location))
		uniformBuffers.push_back({ location, mProjectionMatrixUniform });

	if (mShader->getUniformLocation("inverseProjectionMatrix", location))
		uniformBuffers.push_back({ location, mInverseProjectionMatrixUniform });

	if (mShader->getUniformLocation("viewMatrix", location))
		uniformBuffers.push_back({ location,  mViewMatrixUniform });

	if (mShader->getUniformLocation("samples", location))
	{
		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, std::span<Math::Vec3>(mKernel)) });
	}

	RenderLib::DescriptorSetConfig uniformConfig{};
	uniformConfig.uniformBuffers	= uniformBuffers;
	uniformConfig.uniformSamplers	= uniformSamplers;
	auto uniforms					= RenderLib::createDescriptorSet(mContext, uniformConfig);

	return FullscreenTechnique::initialize(context, 
										   pipelineState,
										   shader, 
										   uniforms,
										   gBuffer.width(), gBuffer.height(), RenderLib::PixelFormat::R16_F);*/

	return false;
}


void
SSAOFirstPass::setProjectionMatrix(const glm::mat4& matrix)
{
	mProjectionMatrixUniform->update((std::byte*)glm::value_ptr(matrix));
	mInverseProjectionMatrixUniform->update((std::byte*)glm::value_ptr(glm::inverse(matrix)));
}


void
SSAOFirstPass::setViewMatrix(const glm::mat4& matrix)
{
	mViewMatrixUniform->update((std::byte*)glm::value_ptr(matrix));
}


bool
SSAOBlurPass::initialize(RenderLib::Context& context,
						 std::shared_ptr<RenderLib::PipelineState> pipelineState,
						 RenderLib::Sampler* inputTexture)
{
/*	auto shader	= Engine::Rendering::ShaderManager::find("AverageBlur");

	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	mInputTexture = inputTexture;
	mBlurSizeUniform = UniformBufferFactory::createUniformBuffer(mContext, mBlurSize);

	uint32_t location;
	if (mShader->getUniformLocation("blurSize", location))
		uniformBuffers.push_back({ location,  mBlurSizeUniform });

	if (mShader->getUniformLocation("sourceTexture", location))
		uniformSamplers.push_back({ location, inputTexture });

	RenderLib::DescriptorSetConfig uniformConfig{};
	uniformConfig.uniformBuffers	= uniformBuffers;
	uniformConfig.uniformSamplers	= uniformSamplers;
	auto uniformDescriptorSet		= RenderLib::createDescriptorSet(mContext, uniformConfig);

	return FullscreenTechnique::initialize(context, 
										   pipelineState, 
										   shader, 
										   uniformDescriptorSet, 
										   inputTexture->texture()->width(),
										   inputTexture->texture()->height(), 
										   RenderLib::PixelFormat::R16_F);*/

	return true;
}


void
SSAOBlurPass::setBlurSize(uint32_t blurSize)
{
	mBlurSize = blurSize;
	mBlurSizeUniform->update((const std::byte*)(&mBlurSize));
}


bool
SSAORenderer::initialize(RenderLib::Context& context, GBuffer& gBuffer)
{
	/*mContext = context;

	RenderLib::PipelineStateConfig config{};
	config.blendMode		= RenderLib::BlendMode::None;
	config.depthTestMode	= RenderLib::DepthTestMode::None;
	config.faceCullingMode	= RenderLib::FaceCullingMode::None;
	auto pipelineState		= RenderLib::createPipelineState(context, config);

	if (!mSSAOPass.initialize(context, pipelineState, gBuffer))
	{
		return false;
	}

	auto ssaoTexture = RenderLib::createSampler(context, {mSSAOPass.texture(), RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::Filter::NEAREST, RenderLib::WrapMode::ONE });

	if (!mBlurPass.initialize(context, pipelineState, ssaoTexture))
	{
		return false;
	}*/

	return true;
}


std::shared_ptr<RenderLib::Texture2D>
SSAORenderer::texture()
{
	//return mBlurPass.texture();

	return nullptr;
}


std::shared_ptr<RenderLib::CommandBuffer>
SSAORenderer::recordRenderCommands(SceneView& view)
{
	/*auto cb = RenderLib::createCommandBuffer(mContext, { "Screen Space Ambient Occlusion" });

	cb->cmdExecuteCommands(mSSAOPass.recordRenderCommands());
	cb->cmdExecuteCommands(mBlurPass.recordRenderCommands());

	return cb;*/

	return nullptr;
}