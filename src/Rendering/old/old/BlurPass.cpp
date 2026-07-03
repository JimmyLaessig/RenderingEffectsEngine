//
//#include "BlurPass.h"
//
//#include <Engine/ShaderRegistry.h>
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
//#include <vector>
//
//#include <glm/gtc/type_ptr.hpp>
//#include <format>
//
//using namespace Reef::Rendering;
//
////
////bool
////BlurTechnique::initialize(std::shared_ptr<::Rendering::Context> context, std::shared_ptr<::Rendering::Texture2D> source, uint32_t blurSize)
////{
////	mBlurSize = blurSize;
////
////	::Rendering::SamplerConfig samplerConfig{};
////	samplerConfig.texture	= source;
////	samplerConfig.magFilter = ::Rendering::Filter::NEAREST;
////	samplerConfig.minFilter = ::Rendering::Filter::NEAREST;
////	samplerConfig.wrapMode	= ::Rendering::WrapMode::CLAMP_TO_EDGE;
////	mSourceTexture			= ::Rendering::createSampler(context, samplerConfig);
////
////	auto shader = Engine::ShaderRegistry::find("AverageBlur");
////
////	::Rendering::PipelineStateConfig config{};
////	config.blendMode		= { ::Rendering::BlendFactor::ONE, ::Rendering::BlendFactor::ZERO, ::Rendering::BlendOp::ADD };
////	config.depthTestMode	= { false, ::Rendering::CompareOp::ALWAYS };
////	auto pipelineState		= ::Rendering::createPipelineState(context, config);
////
////	return FullscreenTechnique::initialize(context, shader, pipelineState, source->width(), source->height(), source->pixelFormat());
////}
//
//
////std::shared_ptr<::Rendering::RenderCommand> 
////BlurTechnique::renderCommand()
////{
////	auto rc = FullscreenTechnique::renderCommand();
////
////	rc->setUniform(mBlurSizeLocation, ::Rendering::UniformType::INT32, &mBlurSize);
////	rc->setUniform(mSourceTextureLocation, mSourceTexture);
////
////	return rc;
////}