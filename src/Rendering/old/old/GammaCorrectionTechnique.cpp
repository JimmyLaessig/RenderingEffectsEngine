module Engine.Rendering.GammaCorrectionTechnique;

import Engine.Rendering.ShaderManager;

import Engine.Rendering.UniformBufferFactory;

using namespace Reef::Rendering;


bool
GammaCorrectionTechnique::initialize(RenderLib::Context& context,
									 std::shared_ptr<RenderLib::Texture2D> inputTexture)
{
	/*RenderLib::PipelineStateConfig config{};
	config.blendMode = RenderLib::BlendMode::None;
	config.depthTestMode = RenderLib::DepthTestMode::None;
	config.faceCullingMode = RenderLib::FaceCullingMode::None;
	auto pipelineState = RenderLib::createPipelineState(context, config);

	RenderLib::SamplerConfig samplerConfig{};
	samplerConfig.texture = inputTexture;

	mInputTexture = RenderLib::createSampler(context, samplerConfig);

	return FullscreenTechnique::initialize(context,
		ShaderManager::find("GammaCorrection"),
		pipelineState,
		inputTexture->width(),
		inputTexture->height(),
		RenderLib::PixelFormat::RGB8_UI);*/
	return true;
}


std::shared_ptr<RenderLib::CommandBuffer>
GammaCorrectionTechnique::recordRenderCommands(SceneView& view)
{
	/*auto commandBuffer = RenderLib::createCommandBuffer(mContext, {"Gamma correction"});

	beginCommandBuffer(commandBuffer);

	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	uint32_t location;
	if (mShader->getUniformLocation("inputTexture", location))
	{
		uniformSamplers.push_back({ location, mInputTexture });
	}

	if (mShader->getUniformLocation("oneOverGamma", location))
	{
		uniformBuffers.push_back({ location, UniformBufferFactory::createUniformBuffer(mContext, 1.0f / mGamma) });
	}

	RenderLib::DescriptorSetConfig uniformsConfig{};
	uniformsConfig.uniformBuffers = uniformBuffers;
	uniformsConfig.uniformSamplers = uniformSamplers;
	auto uniforms = RenderLib::createDescriptorSet(mContext, uniformsConfig);
	commandBuffer->cmdBindDescriptorSet(uniforms);

	endCommandBuffer(commandBuffer);*/

	//return commandBuffer;
	return nullptr;
}
