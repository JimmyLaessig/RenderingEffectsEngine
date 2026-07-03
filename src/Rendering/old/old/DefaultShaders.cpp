module;

#include "Shaders/generated/CalculateIrradianceShader.h"
#include "Shaders/generated/DefaultPBR.h"
#include "Shaders/generated/DirectionalLightShader.h"
#include "Shaders/generated/UnlitSkyboxShader.h"
#include "Shaders/generated/EnvironmentLightShader.h"
#include "Shaders/generated/SSAO.h"
#include "Shaders/generated/AverageBlurShader.h"
#include "Shaders/generated/DepthShader.h"
#include "Shaders/generated/ToneMappingShader.h"
#include "Shaders/generated/GammaCorrectionShader.h"
#include "Shaders/generated/FXAAShader.h"
#include "Shaders/generated/UniformColor.h"
#include "Shaders/generated/Selection.h"

module Engine.Rendering.DefaultShaders;

import Engine.Shader;

namespace Reef
{

namespace Rendering
{

namespace DefaultShaders
{

bool initialize(Engine::Rendering::ShaderManager& shaderManager)
{

	return
		shaderManager.addShader("SelectionShader",
			Shaders::Selection::vertexShaderSourceGLSL,
			Shaders::Selection::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("UniformColor",
			Shaders::UniformColor::vertexShaderSourceGLSL,
			Shaders::UniformColor::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("DefaultPBR",
			Shaders::DefaultPBR::vertexShaderSourceGLSL,
			Shaders::DefaultPBR::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("UnlitSkybox",
			Shaders::UnlitSkybox::vertexShaderSourceGLSL,
			Shaders::UnlitSkybox::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("CalculateIrradiance",
			Shaders::CalculateIrradianceShader::vertexShaderSourceGLSL,
			Shaders::CalculateIrradianceShader::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("DirectionalLight",
			Shaders::DirectionalLightPass::vertexShaderSourceGLSL,
			Shaders::DirectionalLightPass::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("EnvironmentLight",
			Shaders::EnvironmentLightShader::vertexShaderSourceGLSL,
			Shaders::EnvironmentLightShader::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("SSAO",
			Shaders::SSAO::vertexShaderSourceGLSL,
			Shaders::SSAO::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("AverageBlur",
			Shaders::AverageBlur::vertexShaderSourceGLSL,
			Shaders::AverageBlur::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("DepthShader",
			Shaders::DepthShader::vertexShaderSourceGLSL,
			Shaders::DepthShader::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("ToneMapping",
			Shaders::ToneMappingShader::vertexShaderSourceGLSL,
			Shaders::ToneMappingShader::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("GammaCorrection",
			Shaders::GammaCorrectionShader::vertexShaderSourceGLSL,
			Shaders::GammaCorrectionShader::fragmentShaderSourceGLSL) &&

		shaderManager.addShader("FXAA",
			Shaders::FXAAShader::vertexShaderSourceGLSL,
			Shaders::FXAAShader::fragmentShaderSourceGLSL);
}

} // namespace DefaultShaders

} // namespace Rendering

} // namespace Reef
