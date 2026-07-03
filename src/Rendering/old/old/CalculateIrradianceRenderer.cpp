module;

#include <span>
#include <memory>

module Engine.Rendering.CalculateIrradiance;

import Engine.Rendering.GeometryRenderer;

import Engine.Rendering.ShaderManager;

import Engine.Rendering.TextureResource;

import RenderLib;

using namespace Reef::Rendering;


bool
CalculateIrradiance::initialize(RenderLib::Context& context,
								std::shared_ptr<Engine::Texture> sourceTexture,
								std::shared_ptr<Engine::Texture> targetTexture)
{
	//sourceTexture->RenderResource().update(context);
	//targetTexture->RenderResource().update(context);
	//auto source = sourceTexture->RenderResource().sampler();
	//auto target = targetTexture->RenderResource().texture();

	//auto shader = Engine::Rendering::ShaderManager::find("CalculateIrradiance");

	//RenderLib::PipelineStateConfig config{};
	//config.blendMode		= { RenderLib::BlendFactor::ONE, RenderLib::BlendFactor::ZERO, RenderLib::BlendOp::ADD };
	//config.depthTestMode	= { false, RenderLib::CompareOp::ALWAYS };
	//config.faceCullingMode	= RenderLib::FaceCullingMode::BackFaceCulling;
	//auto pipelineState		= RenderLib::createPipelineState(context, config);

	//std::vector<RenderLib::UniformBufferDescriptor> uniformBuffers;
	//std::vector<RenderLib::UniformSamplerDescriptor> uniformSamplers;

	//uint32_t location;
	//if (shader->getUniformLocation("environmentTexture", location))
	//{
	//	uniformSamplers.push_back({ location, source });
	//}

	//RenderLib::DescriptorSetConfig uniformsConfig{};
	//uniformsConfig.uniformBuffers	= uniformBuffers;
	//uniformsConfig.uniformSamplers	= uniformSamplers;
	//auto uniforms = RenderLib::createDescriptorSet(context, uniformsConfig);

	//return FullscreenTechnique::initialize(context, pipelineState, shader, uniforms, target);

	return false;
}