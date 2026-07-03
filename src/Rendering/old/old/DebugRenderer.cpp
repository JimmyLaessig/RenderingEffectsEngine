module;

#include <vector>
#include <array>
#include <span>

module Engine.Rendering.DebugRenderer;

import Engine.Component.CameraComponent;
import Engine.Component.MeshComponent;

import Engine.Rendering.UniformBufferFactory;
import Engine.Rendering.ShaderManager;
import Engine.GameObject;
import Engine.Transform;
import Engine.Mesh;

import Engine.Rendering.RenderResource;
import Engine.Rendering.PrimitiveResource;

import Engine.Rendering.SceneView;

import Engine.Rendering.PrimitiveResource;
import Engine.Rendering.RenderResource;
import RenderLib;

using namespace Reef::Rendering;


bool
DebugRenderer::initialize(RenderLib::Context& context,
						  uint32_t width, uint32_t height,
						  RenderLib::Framebuffer& framebuffer)
{
	/*mContext		= &context;
	mFramebuffer	= &framebuffer;

	mWidth = width;

	mHeight = height;
	
	{
		RenderLib::PipelineStateConfig config{};
		config.faceCullingMode	= RenderLib::FaceCullingMode::BackFaceCulling;
		config.blendMode		= RenderLib::BlendMode::None;
		config.depthTestMode	= RenderLib::DepthTestMode::LessOrEqual;
		config.depthTestMode.writeDepth = false;
		config.polygonMode		= RenderLib::PolygonMode::WIREFRAME;
		mPipelineState			= RenderLib::createPipelineState(context, config);
	}
	{
		RenderLib::PipelineStateConfig config{};
		config.faceCullingMode	= RenderLib::FaceCullingMode::BackFaceCulling;
		config.blendMode		= RenderLib::BlendMode::None;
		config.depthTestMode	= RenderLib::DepthTestMode::LessOrEqual;
		config.polygonMode		= RenderLib::PolygonMode::SOLID;
		mSelectionPipelineState	= RenderLib::createPipelineState(context, config);
	}
	{
		RenderLib::Texture2DConfig config{};
		config.width		= mWidth;
		config.height		= mHeight;
		config.format		= RenderLib::PixelFormat::R8_UI;
		auto selectionTexture	= RenderLib::createTexture2D(context, config);

		RenderLib::SamplerConfig samplerConfig{};
		samplerConfig.texture = selectionTexture;
		samplerConfig.minFilter = RenderLib::Filter::NEAREST;
		samplerConfig.magFilter = RenderLib::Filter::NEAREST;
		samplerConfig.mipmapFilter = RenderLib::Filter::NEAREST;
		mSelectionTexture = RenderLib::createSampler(context, samplerConfig);
	}
	{
		RenderLib::Texture2DConfig config{};
		config.width	= mWidth;
		config.height	= mHeight;
		config.format	= RenderLib::PixelFormat::DEPTH16;
		auto selectionDepthTexture = RenderLib::createTexture2D(context, config);

		RenderLib::SamplerConfig samplerConfig{};
		samplerConfig.texture = selectionDepthTexture;
		samplerConfig.minFilter = RenderLib::Filter::NEAREST;
		samplerConfig.magFilter = RenderLib::Filter::NEAREST;
		samplerConfig.mipmapFilter = RenderLib::Filter::NEAREST;
		mSelectionDepthTexture = RenderLib::createSampler(context, samplerConfig);
	}
	{
		RenderLib::FramebufferConfig config{};
		config.depthAttachment = std::static_pointer_cast<RenderLib::Texture2D>(mSelectionDepthTexture->texture());

		std::array colorAttachments
		{
			RenderLib::ColorAttachment{0, std::static_pointer_cast<RenderLib::Texture2D>(mSelectionTexture->texture())}
		};

		config.colorAttachments = colorAttachments;

		mSelectionFramebuffer = RenderLib::createFramebuffer(context, config);
	}*/

	return true;
}


bool
DebugRenderer::resize(uint32_t width, uint32_t height)
{
	return true;
}


void
DebugRenderer::setSceneView(const SceneView& view)
{
	//mSceneView = view;
}


void
DebugRenderer::setSelection(const std::vector<MeshComponent*> meshes)
{
	//mSelectedMeshes = meshes;
}


RenderLib::CommandBuffer*
DebugRenderer::recordRenderCommands()
{
	/*updateRenderResource();

	auto commandBuffer = RenderLib::createCommandBuffer(context(), {});

	if (auto cb = renderWireframeOverlay())
	{
		commandBuffer->cmdExecuteCommands(cb);
	}

	if (auto cb = renderSelectionOverlay())
	{
	}
	
	renderSelectionOverlay();

	return commandBuffer;*/

	return nullptr;
}


//void 
//DebugRenderer::updateRenderResource()
//{
//	std::vector<RenderResource*> RenderResource;
//	for (auto& ro : mSceneView.renderObjects)
//	{
//		ro.primitive->RenderResource().update(context());
//	}
//}


//RenderLib::CommandBuffer*
//DebugRenderer::renderWireframeOverlay()
//{
//	/*if (!mDrawWireframeOverlay)
//	{
//		return nullptr;
//	}
//
//	auto shader = ShaderManager::find("UniformColor");
//	auto commandBuffer = RenderLib::createCommandBuffer(context(), { "Debug Wireframe Overlay" });
//	commandBuffer->begin();
//	RenderLib::RenderPassBeginConfig beginConfig{};
//	beginConfig.framebuffer = mFramebuffer;
//	beginConfig.viewport = { 0, 0, mWidth, mHeight };
//
//	commandBuffer->cmdBeginRenderPass(beginConfig);
//	commandBuffer->cmdBindPipelineState(mPipelineState);
//	commandBuffer->cmdBindShader(shader);
//
//	for (const auto& ro : mSceneView.renderObjects)
//	{
//		auto& data = ro.primitive->RenderResource();
//
//		commandBuffer->cmdBindIndexBuffer(data.indices());
//
//		commandBuffer->cmdVertexBuffer(0, data.positions());
//
//		auto modelViewProjectionMatrix = mSceneView.viewProjectionMatrix * ro.localToWorldMatrix;
//
//		std::array<RenderLib::UniformBufferDescriptor, 2> uniformBuffers =
//		{
//			RenderLib::UniformBufferDescriptor{ 1, UniformBufferFactory::createUniformBuffer(context(), modelViewProjectionMatrix) },
//			RenderLib::UniformBufferDescriptor{ 0, UniformBufferFactory::createUniformBuffer(context(), mWireframeColor) }
//		};
//
//		RenderLib::DescriptorSetConfig materialUniformsConfig{};
//		materialUniformsConfig.uniformBuffers = uniformBuffers;
//		auto materialUniforms = RenderLib::createDescriptorSet(context(), materialUniformsConfig);
//		commandBuffer->cmdBindDescriptorSet(materialUniforms);
//		commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);
//	}
//
//	commandBuffer->cmdEndRenderPass();
//	commandBuffer->end();
//
//	return commandBuffer;*/
//
//	return nullptr;
//}


//RenderLib::CommandBuffer*
//DebugRenderer::renderSelectionOverlay()
//{
//	/*if (mSelectedMeshes.empty())
//	{
//		return nullptr;
//	}
//	auto shader = ShaderManager::find("UniformColor");
//	auto commandBuffer = RenderLib::createCommandBuffer(context(), { "Debug Wireframe Overlay" });
//	commandBuffer->begin();
//
//	std::array clearColor
//	{
//		RenderLib::ClearColor{ { 0.f, 0.f, 0.f, 0.f }, 0 }
//	};
//
//	RenderLib::ClearDepth clearDepth{1.f, 0 };
//
//	commandBuffer->cmdBeginRenderPass({ mSelectionFramebuffer, { 0, 0, mWidth, mHeight } });
//	commandBuffer->cmdClearAttachments(clearColor, clearDepth);
//	commandBuffer->cmdBindPipelineState(mSelectionPipelineState);
//	commandBuffer->cmdBindShader(shader);
//
//	float id = 1;
//	for (auto meshComp : mSelectedMeshes)
//	{
//		auto localToWorldMatrix = meshComp->entity().transform().localToWorldMatrix();
//		for (auto primitive : meshComp->mesh()->primitives())
//		{
//			auto& data = static_cast<PrimitiveResource&>(primitive->RenderResource());
//			data.update(context());
//
//			commandBuffer->cmdBindIndexBuffer(data.indices());
//
//			commandBuffer->cmdVertexBuffer(0, data.positions());
//
//			auto modelViewProjectionMatrix = mSceneView.viewProjectionMatrix * localToWorldMatrix;
//
//			std::array<RenderLib::UniformBufferDescriptor, 2> uniformBuffers =
//			{
//				RenderLib::UniformBufferDescriptor{ 1, UniformBufferFactory::createUniformBuffer(context(), modelViewProjectionMatrix) },
//				RenderLib::UniformBufferDescriptor{ 0, UniformBufferFactory::createUniformBuffer(context(), Math::Vec4(id, id, id, id)) }
//			};
//
//			RenderLib::DescriptorSetConfig materialUniformsConfig{};
//			materialUniformsConfig.uniformBuffers = uniformBuffers;
//			auto materialUniforms = RenderLib::createDescriptorSet(context(), materialUniformsConfig);
//			commandBuffer->cmdBindDescriptorSet(materialUniforms);
//			commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);
//		}
//		id++;
//	}
//
//	commandBuffer->cmdEndRenderPass();
//
//	{
//		auto shader = ShaderManager::find("SelectionShader");
//		commandBuffer->cmdBeginRenderPass({ mFramebuffer, { 0, 0, mWidth, mHeight } });
//		commandBuffer->cmdBindShader(shader);
//
//		uint32_t selectionColorLocation{ 0 };
//		shader->getUniformLocation("selectionColor", selectionColorLocation);
//
//		uint32_t selectionTextureLocation{ 0 };
//		shader->getUniformLocation("selectionTexture", selectionTextureLocation);
//
//		uint32_t selectionDepthTextureLocation{ 0 };
//		shader->getUniformLocation("selectionDepthTexture", selectionDepthTextureLocation);
//
//		std::array uniformBuffers =
//		{
//			RenderLib::UniformBufferDescriptor{ selectionColorLocation, UniformBufferFactory::createUniformBuffer(context(), mSelectionColor) }
//		};
//
//		std::array uniformSamplers =
//		{
//			RenderLib::UniformSamplerDescriptor{ selectionTextureLocation, mSelectionTexture },
//			RenderLib::UniformSamplerDescriptor{ selectionDepthTextureLocation, mSelectionDepthTexture }
//		};
//
//		RenderLib::DescriptorSetConfig uniformsConfig{};
//		uniformsConfig.uniformBuffers = uniformBuffers;
//		uniformsConfig.uniformSamplers = uniformSamplers;
//		auto descriptors = RenderLib::createDescriptorSet(context(), uniformsConfig);
//		commandBuffer->cmdBindDescriptorSet(descriptors);
//
//		auto quad = Engine::Mesh::Quad();
//		auto p = quad->getPrimitive(0);
//		p->RenderResource().update(context());
//
//		auto& data = p->RenderResource();
//		commandBuffer->cmdBindIndexBuffer(data.indices());
//		commandBuffer->cmdVertexBuffer(0, data.positions());
//		commandBuffer->cmdDrawIndexed(RenderLib::PrimitiveType::Triangles);
//		commandBuffer->cmdEndRenderPass();
//	}
//
//	commandBuffer->end();
//	return commandBuffer;*/
//
//	return nullptr;
//}
