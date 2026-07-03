module;

#include <memory>
#include <cstdint>
#include <span>

export module Engine.Rendering.FullscreenTechnique;

import Engine.Texture;

import RenderLib;
import RenderLib.RAII;

import Engine.Mesh;


namespace Reef
{

namespace Rendering
{

export struct GBuffer;
export struct SceneView;

export struct FullscreenQuad
{
	bool initialize(RenderLib::Context& context);

	std::shared_ptr<RenderLib::BufferView> mPositions;

	std::shared_ptr<RenderLib::BufferView> mIndices;
};


class FullscreenTechnique
{
public:
	virtual ~FullscreenTechnique() = default;

	bool initialize(RenderLib::Context& context, 
					std::shared_ptr<RenderLib::PipelineState> pipelineState,
					std::shared_ptr<RenderLib::Shader> shader,
					std::shared_ptr<RenderLib::DescriptorSet> uniforms,
					uint32_t width, uint32_t height, RenderLib::PixelFormat pixelFormat);

	bool initialize(RenderLib::Context& context,
					std::shared_ptr<RenderLib::PipelineState> pipelineState,
					std::shared_ptr<RenderLib::Shader> shader,
					std::shared_ptr<RenderLib::DescriptorSet> uniforms,
					std::shared_ptr<RenderLib::Texture2D> texture);

	bool initialize(RenderLib::Context& context,
					std::shared_ptr<RenderLib::PipelineState> pipelineState,
					std::shared_ptr<RenderLib::Shader> shader,
					std::shared_ptr<RenderLib::DescriptorSet> uniforms,
					std::shared_ptr<RenderLib::Framebuffer> framebuffer);

	RenderLib::CommandBuffer* recordRenderCommands();

	RenderLib::Framebuffer* framebuffer();

	RenderLib::Texture2D* texture();

protected:

	RenderLib::Context* mContext;

	std::shared_ptr<Engine::Mesh> mFullscreenQuad;

	std::shared_ptr<RenderLib::PipelineState> mPipelineState;

	std::shared_ptr<RenderLib::Shader> mShader;

	std::shared_ptr<RenderLib::DescriptorSet> mUniforms;

	std::shared_ptr<RenderLib::Texture2D> mTexture;

	std::shared_ptr<RenderLib::Framebuffer> mFramebuffer;

	RenderLib::RAII::CommandBufferPtr mCommandBuffer;
};

} // namespace Rendering

} // namespace Reef
