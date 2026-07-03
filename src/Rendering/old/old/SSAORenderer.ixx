module;

#include <glm/glm.hpp>

#include <array>
#include <cstdint>
#include <memory>

export module Engine.Rendering.SSAORenderer;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.GBuffer;
import Engine.Rendering.SceneView;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class SSAOFirstPass : public FullscreenTechnique
{

public:

	bool initialize(RenderLib::Context& context, 
					std::shared_ptr<RenderLib::PipelineState> pipelineState, 
					GBuffer& gBuffer);

	//void setRadius(float radius);

	void setProjectionMatrix(const glm::mat4& matrix);

	void setViewMatrix(const glm::mat4& viewMatrix);

private:

	RenderLib::RAII::UniformBufferPtr mRadiusUniform;

	RenderLib::RAII::UniformBufferPtr mProjectionMatrixUniform;

	RenderLib::RAII::UniformBufferPtr mInverseProjectionMatrixUniform;

	RenderLib::RAII::UniformBufferPtr mViewMatrixUniform;

	RenderLib::RAII::UniformBufferPtr mKernelUniform;

	RenderLib::Sampler* mNoiseTexture;

	std::array<glm::vec3, 16> mKernel;

	float mRadius{ 0.1f };
};


class SSAOBlurPass : public FullscreenTechnique
{

public:

	bool initialize(RenderLib::Context& context, 
					std::shared_ptr<RenderLib::PipelineState> pipelineState, 
					RenderLib::Sampler* inputTexture);

	void setBlurSize(uint32_t blurSize);

private:

	RenderLib::RAII::UniformBufferPtr mBlurSizeUniform;
	
	RenderLib::Sampler* mInputTexture;

	int32_t mBlurSize{ 4 };
};


class SSAORenderer
{
public:

	bool initialize(RenderLib::Context& context, GBuffer& gBuffer);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

	std::shared_ptr<RenderLib::Texture2D> texture();

private:

	std::shared_ptr<RenderLib::Context> mContext;

	GBuffer* mGBuffer{ nullptr };

	SSAOFirstPass mSSAOPass;

	SSAOBlurPass mBlurPass;
};

} // namespace Rendering

} // namespace Reef