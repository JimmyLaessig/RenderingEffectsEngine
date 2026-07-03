#include <Engine/Rendering/MaterialFUnctionResource.hpp>

#include <Engine/Rendering/ShaderImpl.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Core/Visitor.hpp>

#include <Coral/ShaderLanguage/CompilerSPV.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <span>
#include <ranges>
#include <iostream>

using namespace Reef::Rendering;

namespace
{

std::optional<Coral::ShaderLanguage::Compiler::Result>
buildShader(const Reef::MaterialFunction& materialFunction)
{
	constexpr auto POSITION  = "Position";
	constexpr auto NORMAL    = "Normal";
	constexpr auto TANGENT   = "Tangent";
	constexpr auto TEXCOORD0 = "Texcoord0";

	constexpr auto MODEL_MATRIX			  = "modelMatrix";
	constexpr auto NORMAL_MATRIX		  = "normalMatrix";
	constexpr auto VIEW_PROJECTION_MATRIX = "viewProjectionMatrix";

	constexpr auto WORLD_POSITION = "WorldPosition";
	constexpr auto WORLD_NORMAL   = "WorldNormal";

	using namespace csl;
	csl::ShaderGraph vertexShader;
	csl::ShaderGraph fragmentShader;

	// Vertex Shader
	{
		csl::Input<float3> position(POSITION);
		csl::Input<float3> normal(NORMAL);
		csl::Input<float3> tangent(TANGENT);
		csl::Input<float2> texcoords(TEXCOORD0);

		auto modelMatrix          = Parameter<Float4x4>(MODEL_MATRIX);
		auto normalMatrix         = Parameter<Float3x3>(NORMAL_MATRIX);
		auto viewProjectionMatrix = Parameter<Float4x4>(VIEW_PROJECTION_MATRIX);

		auto wp = modelMatrix * float4(position, 1.f);
		auto worldPosition = wp.xyz() / wp.w();

		if (auto worldPositionFun = materialFunction.worldPosition())
		{
			worldPosition = *worldPositionFun;
		}

		auto worldNormal = normalMatrix * normal;
		if (auto worldNormalFun = materialFunction.worldNormal())
		{
			worldNormal = *worldNormalFun;
		}

		worldNormal = csl::normalize(worldNormal);

		auto p = viewProjectionMatrix * wp;

		auto glPosition       = csl::Output(csl::DefaultAttribute::POSITION, p);
		auto outPosition      = csl::Output(POSITION, p);
		auto outWorldPosition = csl::Output(WORLD_POSITION, worldPosition);
		auto outWorldNormal   = csl::Output(WORLD_NORMAL, worldNormal);
		auto outTexcoord0     = csl::Output(TEXCOORD0, texcoords);

		vertexShader.registerOutputAttribute(glPosition);
		vertexShader.registerOutputAttribute(outPosition);
		vertexShader.registerOutputAttribute(outWorldPosition);
		vertexShader.registerOutputAttribute(outWorldNormal);
		vertexShader.registerOutputAttribute(outTexcoord0);
	}

	// Fragment Shader
	{
		auto position  = Input<float4>(POSITION);
		auto normal    = Input<float3>(NORMAL);
		auto tangent   = Input<float3>(TANGENT);
		auto texcoords = Input<float3>(TEXCOORD0);

		materialFunction.baseColor();

		float3 baseColor(1.f, 1.f, 1.f);
		if (auto baseColorFun = materialFunction.baseColor())
		{
			baseColor = *baseColorFun;
		}

		if (auto mask = materialFunction.mask())
		{
			//auto depth = csl::If(*mask).Then(position.z() / position.w()).Else(csl::Float(1.f));
			//auto glDepth = csl::Output(csl::DefaultAttribute::DEPTH, depth);
			//fragmentShader.registerOutputAttribute(glDepth);
		}

		auto baseColorAndOpacity = csl::Output("BaseColorAndOpacity", float4(baseColor, 1.f));
		fragmentShader.registerOutputAttribute(baseColorAndOpacity);
	}

	return Coral::ShaderLanguage::CompilerSPV()
		.addShaderModule(Coral::ShaderStage::VERTEX, vertexShader)
		.addShaderModule(Coral::ShaderStage::FRAGMENT, fragmentShader)
		.addUniformBlockOverride(TransformData::Binding, TransformData::Name, TransformData::UniformBlockDefinition)
		.addUniformBlockOverride(FrameData::Binding, FrameData::Name, FrameData::UniformBlockDefinition)
		.setDefaultUniformBlockName(MaterialData::Name)
		.compile()
		.transform([](const auto& result) { return std::optional(result); })
		.transform_error([](const auto& error) { std::cerr << error.message << std::endl; return error; })
		.value_or(std::nullopt);
}

} // namespace


MaterialFunctionResource::MaterialFunctionResource(ResourceManager& resourceManager)
	: RenderResource(resourceManager)
{
}


bool
MaterialFunctionResource::createPipelineState(const Reef::MaterialFunctionImpl& materialFun, Coral::Context& context)
{
	auto shader = buildShader(materialFun);
	if (!shader)
	{
		assert(false);
		return false;
	}

	{
		Coral::ShaderModuleCreateConfig config{};
		config.name       = "VertexShader";
		config.stage      = Coral::ShaderStage::VERTEX;
		config.entryPoint = "main";
		config.source     = std::as_bytes(std::span{ shader->vertexShader });
		mVertexShader     = context.createShaderModule(config).value();
	}

	{
		Coral::ShaderModuleCreateConfig config{};
		config.name       = "FragmentShader";
		config.stage      = Coral::ShaderStage::FRAGMENT;
		config.entryPoint = "main";
		config.source     = std::as_bytes(std::span{ shader->fragmentShader });
		mFragmentShader   = context.createShaderModule(config).value();
	}

	{
		std::array shaders{ mVertexShader.get(), mFragmentShader.get() };
		Coral::PipelineStateCreateConfig config{};
		config.shaderModules        = shaders;
		config.framebufferSignature = { { Coral::PixelFormat::RGBA8_SRGB }, Coral::PixelFormat::DEPTH24_STENCIL8 };
		mPipelineState              = context.createPipelineState(config).value();
	}

	return true;
}



bool
MaterialFunctionResource::update(const Reef::MaterialFunctionImpl& materialFunction, Coral::Context& context)
{
	if (!shouldUpdate(materialFunction.version()))
	{
		return true;
	}

	if (!mPipelineState && !createPipelineState(materialFunction, context))
	{
		return false;
	}

	return true;
}


bool
MaterialFunctionResource::bind(Coral::CommandBuffer& commandBuffer)
{
	commandBuffer.cmdBindPipeline(mPipelineState.get());

	return true;
}


const Coral::ShaderModule&
MaterialFunctionResource::vertexShader() const
{ 
	return *mVertexShader;
}


const Coral::ShaderModule&
MaterialFunctionResource::fragmentShader() const
{
	return *mFragmentShader;
}


const Coral::PipelineState&
MaterialFunctionResource::pipelineState() const
{
	return *mPipelineState;
}
