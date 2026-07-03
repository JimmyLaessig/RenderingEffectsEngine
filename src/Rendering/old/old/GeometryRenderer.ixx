module;

#include <cstdint>
#include <memory>
#include <vector>

export module Engine.Rendering.GeometryRenderer;

import Engine.Rendering.SceneView;
import Engine.Rendering.GBuffer;

import RenderLib.RAII;

namespace Reef
{

namespace Rendering
{

class GeometryRenderer
{
public:

	bool initialize(RenderLib::Context& context, uint32_t width, uint32_t height);

	RenderLib::CommandBuffer* recordRenderCommands(Engine::Rendering::SceneView& view);

	GBuffer& gBuffer() { return mGBuffer; }

	RenderLib::Framebuffer* framebuffer() { return mGBuffer.framebuffer(); }

private:

	RenderLib::Context* mContext;

	GBuffer mGBuffer;

	RenderLib::RAII::PipelineStatePtr mPipelineState;

	// Transient objects

	RenderLib::RAII::CommandBufferPtr mCommandBuffer;

	std::vector<RenderLib::RAII::UniformBufferPtr> mUniforms;

	std::vector<RenderLib::RAII::DescriptorSetPtr> mDescriptorSets;
};

} // namespace Rendering

} // namespace Reef
