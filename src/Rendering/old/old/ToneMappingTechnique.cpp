module;

#include <span>

module Engine.Rendering.ToneMappingTechnique;

import Engine.Rendering.ShaderManager;

using namespace Reef::Rendering;


bool
ToneMappingTechnique::initialize(RenderLib::Context& context,
								 std::shared_ptr<RenderLib::Texture2D> inputTexture)
{
	//auto shader	= ShaderManager::find("ToneMapping");

	//RenderLib::PipelineStateConfig config{};
	//config.blendMode		= RenderLib::BlendMode::None;
	//config.depthTestMode	= RenderLib::DepthTestMode::None;
	//config.faceCullingMode	= RenderLib::FaceCullingMode::None;
	//auto pipelineState		= RenderLib::createPipelineState(context, config);

	//RenderLib::SamplerConfig samplerConfig{};
	//samplerConfig.texture = inputTexture;

	//auto sampler = RenderLib::createSampler(context, samplerConfig);

	//std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	//std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	//uint32_t location;
	//if (shader->getUniformLocation("inputTexture", location))
	//{
	//	uniformSamplers.push_back({ location, sampler });
	//}

	//RenderLib::DescriptorSetConfig uniformsConfig{};
	//uniformsConfig.uniformBuffers	= uniformBuffers;
	//uniformsConfig.uniformSamplers	= uniformSamplers;
	//auto uniforms					= RenderLib::createDescriptorSet(mContext, uniformsConfig);

	//return FullscreenTechnique::initialize(context,
	//									   pipelineState,
	//									   shader,
	//									   uniforms,
	//									   inputTexture->width(), 
	//									   inputTexture->height(), 
	//									   RenderLib::PixelFormat::RGB8_UI);

	return false;
}