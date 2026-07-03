module;

#include <memory>

module Engine.Rendering.FXAATechnique;

import Engine.Rendering.ShaderManager;

using namespace Reef::Rendering;


bool
FXAATechnique::initialize(RenderLib::Context& context,
						  std::shared_ptr<RenderLib::Texture2D> inputTexture)
{
	/*RenderLib::PipelineStateConfig config{};
	config.blendMode		= RenderLib::BlendMode::None;
	config.depthTestMode	= RenderLib::DepthTestMode::None;
	config.faceCullingMode	= RenderLib::FaceCullingMode::None;
	auto pipelineState		= RenderLib::createPipelineState(context, config);

	RenderLib::SamplerConfig samplerConfig{};
	samplerConfig.texture = inputTexture;

	mInputTexture = RenderLib::createSampler(context, samplerConfig);

	return FullscreenTechnique::initialize(context,
										   ShaderManager::find("FXAA"),
										   pipelineState,
										   inputTexture->width(), 
										   inputTexture->height(), 
										   RenderLib::PixelFormat::RGB8_UI);*/

	return true;
}


std::shared_ptr<RenderLib::CommandBuffer>
FXAATechnique::recordRenderCommands(SceneView& view)
{
	/*auto commandBuffer = RenderLib::createCommandBuffer(mContext, { "FXAA" });

	beginCommandBuffer(commandBuffer);

	std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	uint32_t location;
	if (mShader->getUniformLocation("inputTexture", location))
	{
		uniformSamplers.push_back({ location, mInputTexture });
	}

	RenderLib::DescriptorSetConfig uniformsConfig{};
	uniformsConfig.uniformBuffers	= uniformBuffers;
	uniformsConfig.uniformSamplers	= uniformSamplers;
	auto uniforms					= RenderLib::createDescriptorSet(mContext, uniformsConfig);
	commandBuffer->cmdBindDescriptorSet(uniforms);
	endCommandBuffer(commandBuffer);*/

	//return commandBuffer;
	return nullptr;
}
