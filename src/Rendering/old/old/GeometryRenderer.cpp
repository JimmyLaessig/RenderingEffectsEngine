module;

#include <glm/glm.hpp>

#include <array>
#include <cstdint>
#include <memory>
#include <vector>
#include <variant>

module Engine.Rendering.GeometryRenderer;

import Engine.Rendering.TextureResource;
import Engine.Rendering.PrimitiveResource;
import Engine.Rendering.Renderer;
import Engine.Rendering.UniformBufferFactory;

import Engine.Rendering.SceneView;

import RenderLib;
import RenderLib.RAII;

import Visitor;

using namespace Reef::Rendering;


bool
GeometryRenderer::initialize(RenderLib::Context& context, uint32_t width, uint32_t height)
{
	/*mContext = &context;

	RenderLib::PipelineStateConfig pipelineStateConfig{};
	pipelineStateConfig.faceCullingMode = RenderLib::FaceCullingMode::BackFaceCulling;
	pipelineStateConfig.blendMode		= RenderLib::BlendMode::None;
	pipelineStateConfig.depthTestMode	= RenderLib::DepthTestMode::LessOrEqual;
	mPipelineState						= RenderLib::RAII::createPipelineState(mContext, pipelineStateConfig);

	return mGBuffer.initialize(context, width, height);*/
	return false;
}


RenderLib::CommandBuffer*
GeometryRenderer::recordRenderCommands(SceneView& view)
{
	//auto& resourceManager	= Engine::Rendering::Renderer::instance().resourceManager();
	//auto context			= resourceManager.context();

	//auto commandBuffer = RenderLib::RAII::createCommandBuffer(mContext, { "Geometry pass" });
	//commandBuffer->begin();

	//std::array<RenderLib::ClearColor, 3> clearColors =
	//{
	//	RenderLib::ClearColor{ { 0.0f, 0.0f, 0.0f, 0.0f }, 0 },
	//	RenderLib::ClearColor{ { 0.0f, 0.0f, 0.0f, 0.0f }, 1 },
	//	RenderLib::ClearColor{ { 0.0f, 0.0f, 0.0f, 0.0f }, 2 },
	//};

	//RenderLib::ClearDepth clearDepth{ 1.0f, 0 } ;

	//commandBuffer->cmdBeginRenderPass({ mGBuffer.framebuffer(), { 0, 0, mGBuffer.framebuffer()->width(), mGBuffer.framebuffer()->height() } });

	//commandBuffer->cmdClearAttachments({ clearColors }, clearDepth);

	//commandBuffer->cmdBindPipelineState(mPipelineState.get());

	//for (const auto& ro : view.renderObjects)
	//{
	//	auto data = resourceManager.updateResource(*ro.primitive);

	//	commandBuffer->cmdBindShader(ro.material->shader()->shader());

	//	commandBuffer->cmdBindIndexBuffer(data->indices());

	//	commandBuffer->cmdVertexBuffer(0, data->positions());

	//	if (data->normals())
	//	{
	//		commandBuffer->cmdVertexBuffer(1, data->normals());
	//	}
	//	if (data->tangents())
	//	{
	//		commandBuffer->cmdVertexBuffer(2, data->tangents());
	//	}
	//	if (data->texCoords())
	//	{
	//		commandBuffer->cmdVertexBuffer(3, data->texCoords());
	//	}

	//	auto modelViewProjectionMatrix = view.viewProjectionMatrix * ro.localToWorldMatrix;
	//	
	//	ro.material->setParameter("modelMatrix", ro.localToWorldMatrix);
	//	ro.material->setParameter("modelViewMatrix", view.viewMatrix * ro.localToWorldMatrix);
	//	ro.material->setParameter("modelViewProjectionMatrix", modelViewProjectionMatrix);

	//	ro.material->setParameter("viewMatrix", view.viewMatrix);
	//	ro.material->setParameter("viewProjectionMatrix", view.viewProjectionMatrix);

	//	std::vector<RenderLib::UniformBufferDescriptor> bufferUniforms;
	//	std::vector<RenderLib::UniformSamplerDescriptor> textureUniforms;

	//	for (auto& [location, value] : ro.material->parameters())
	//	{
	//		auto updateUniformBuffer = [&](uint32_t location, const auto& value)
	//		{
	//			auto uniformBuffer = UniformBufferFactory::createUniformBuffer(*context, value);
	//			bufferUniforms.push_back({ location, uniformBuffer.get() });
	//			mUniforms.push_back(std::move(uniformBuffer));
	//		};

	//		auto updateUniformTexture = [&](uint32_t location, std::shared_ptr<Texture> texture)
	//		{
	//			textureUniforms.push_back({ location, resourceManager.updateResource(*texture)->sampler() });
	//		};


	//		std::visit(Visitor {
	//			[&](float v)				{ updateUniformBuffer(location, v); },
	//			[&](const glm::vec2& v)	{ updateUniformBuffer(location, v); },
	//			[&](const glm::vec3& v)	{ updateUniformBuffer(location, v); },
	//			[&](const glm::vec4& v)	{ updateUniformBuffer(location, v); },
	//			[&](int v)					{ updateUniformBuffer(location, v); },
	//			[&](const glm::ivec2& v)	{ updateUniformBuffer(location, v); },
	//			[&](const glm::ivec3& v)	{ updateUniformBuffer(location, v); },
	//			[&](const glm::ivec4& v)	{ updateUniformBuffer(location, v); },
	//			[&](const glm::mat2& v)  { updateUniformBuffer(location, v); },
	//			[&](const glm::mat3& v)  { updateUniformBuffer(location, v); },
	//			[&](const glm::mat4& v)  { updateUniformBuffer(location, v); },

	//			[&](std::shared_ptr<Texture> texture) { updateUniformTexture(location, texture); },
	//			}, value);
	//	}

	//	RenderLib::DescriptorSetConfig config{};
	//	config.uniformBuffers		= bufferUniforms;
	//	config.uniformSamplers		= textureUniforms;
	//	auto uniformDescriptorSet	= RenderLib::RAII::createDescriptorSet(context, config);

	//	commandBuffer->cmdBindDescriptorSet(uniformDescriptorSet.get());

	//	mDescriptorSets.push_back(std::move(uniformDescriptorSet));

	//	commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);
	//}

	//commandBuffer->cmdEndRenderPass();

	//commandBuffer->end();

	//mCommandBuffer = std::move(commandBuffer);
	//return mCommandBuffer.get();

	return nullptr;
}
