
//#include "PostprocessingEffect.h"
//
//#include <Engine/ShaderManager.h>
//#include <Rendering/Framebuffer.h>
//#include <Rendering/Shader.h>
//#include <Rendering/PipelineState.h>
//#include <Rendering/RenderPass.h>
//#include <Rendering/CommandBuffer.h>
//#include <Rendering/RenderCommand.h>
//#include <Rendering/CommandQueue.h>
//#include "TextureResource.h"
//
//#include "SceneRenderer.h"
//#include <array>
//vector>;
//
//#include <glm/gtc/type_ptr.hpp>
//#include <format>
//
//using namespace Reef::Rendering;
//
//namespace
//{
//
//float random(float min, float max)
//{
//	auto randVal = std::rand();
//	float value = randVal / float(RAND_MAX);
//
//	return value * (max - min) + min;
//}
//
//} // namespace
//
//bool
//ScreenSpaceAmbientOcclusion::initialize(RenderLib::Context& context, GBuffer& gBuffer, uint32_t width, uint32_t height)
//{
//	if (!FullscreenPass::initialize(context, ShaderManager::find("SSAO"), width, height, RenderLib::PixelFormat::R8_UI))
//	{
//		return false;
//	}
//	
//	mDepthTexture	 = gBuffer.depthTexture;
//	mNormalTexture	 = gBuffer.normalTexture;
//	mMaterialTexture = gBuffer.materialTexture;
//
//	float i = 0;
//	for (auto& sample : mKernel)
//	{
//		sample = Math::Vec3(random(-1, 1), 
//						   random(-1, 1),
//						   random( 0, 1));
//		sample = glm::normalize(sample);
//		sample *= random(0, 1);
//
//		float scale = i / mKernel.size();
//
//		scale = glm::mix(0.1f, 1.0f, scale * scale);
//
//		sample *= scale;
//		i++;
//	}
//
//	std::array<Math::Vec3, 16> noise;
//	for (auto& value : noise)
//	{
//		value = Math::Vec3(random(-1.0f, 1.0f),
//						  random(-1.0f, 1.0f), 0);
//		value = glm::normalize(value);
//	}
//	
//	RenderLib::Texture2DConfig config{};
//	config.width = 4;
//	config.height = 4;
//	config.generateMips = false;
//	config.format = RenderLib::PixelFormat::RGB32_F;
//	config.alignment = RenderLib::Alignment::BYTE;
//	config.data = (void*)noise.data();
//	auto noiseTexture = RenderLib::createTexture2D(context, config);
//
//	RenderLib::SamplerConfig samplerConfig{};
//	samplerConfig.magFilter = RenderLib::Filter::NEAREST;
//	samplerConfig.minFilter = RenderLib::Filter::NEAREST;
//	samplerConfig.texture	= noiseTexture;
//	samplerConfig.wrapMode	= RenderLib::WrapMode::REPEAT;
//
//	mNoiseTexture = RenderLib::createSampler(context, samplerConfig);
//
//	if (!mBlurPass.initialize(mContext, mTexture, 4))
//	{
//		return false;
//	}
//
//	samplerConfig.texture = mBlurPass.texture();
//	mOcclusionTexture = RenderLib::createSampler(context, samplerConfig);
//
//	return true;
//}
//
//
//void
//ScreenSpaceAmbientOcclusion::resize(uint32_t width, uint32_t height)
//{
//	mBlurPass.resize(width, height);
//}
//
//
//void 
//ScreenSpaceAmbientOcclusion::recordCommandBuffer(SceneView& view, RenderLib::CommandQueue& commandQueue)
//{
//	RenderLib::RenderCommandConfig config{};
//	std::vector<RenderLib::VertexBufferBinding> vertexBufferBindings =
//	{
//		{ 0u, mPositions }
//	};
//	config.vertexBufferBindings = vertexBufferBindings;
//	config.indexBuffer			= mIndices;
//	config.pipelineState		= mPipelineState;
//	config.renderPass			= mRenderPass;
//	config.shader				= mShader;
//
//	auto renderCommand = RenderLib::createRenderCommand(mContext, config);
//
//	uint32_t location;
//	if (config.shader->getUniformLocation("depthTexture", location))
//	{
//		renderCommand->setUniform(location, mDepthTexture);
//	}
//
//	if (config.shader->getUniformLocation("normalTexture", location))
//	{
//		renderCommand->setUniform(location, mNormalTexture);
//	}
//
//	if (config.shader->getUniformLocation("materialTexture", location))
//	{
//		renderCommand->setUniform(location, mMaterialTexture);
//	}
//
//	if (config.shader->getUniformLocation("noiseTexture", location))
//	{
//		renderCommand->setUniform(location, mNoiseTexture);
//	}
//
//	if (config.shader->getUniformLocation("radius", location))
//	{
//		renderCommand->setUniform(location, RenderLib::UniformType::FLOAT, &mRadius);
//	}
//
//	if (config.shader->getUniformLocation("projectionMatrix", location))
//	{
//		renderCommand->setUniform(location, RenderLib::UniformType::MAT4X4F, glm::value_ptr(view.camera.projectionMatrix));
//	}
//
//	if (config.shader->getUniformLocation("inverseProjectionMatrix", location))
//	{
//		renderCommand->setUniform(location, RenderLib::UniformType::MAT4X4F, glm::value_ptr(view.camera.inverseProjectionMatrix));
//	}
//
//	if (config.shader->getUniformLocation("viewMatrix", location))
//	{
//		renderCommand->setUniform(location, RenderLib::UniformType::MAT4X4F, glm::value_ptr(view.viewMatrix));
//	}
//
//	for (uint32_t i = 0; i < mKernel.size(); ++i)
//	{
//		auto name = std::format("samples[{0}]", i);
//		if (config.shader->getUniformLocation(name.c_str(), location))
//		{
//			renderCommand->setUniform(location, RenderLib::UniformType::VEC3F, &mKernel[i]);
//		}
//	}
//
//	RenderLib::CommandBufferConfig commandBufferConfig{};
//	auto commandBuffer = RenderLib::createCommandBuffer(mContext, commandBufferConfig);
//	commandBuffer->addRenderCommand(renderCommand);
//	commandQueue.submit(commandBuffer);
//
//	mBlurPass.recordCommandBuffer(view, commandQueue);
//}