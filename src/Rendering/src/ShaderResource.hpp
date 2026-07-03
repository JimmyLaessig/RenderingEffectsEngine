#ifndef ENGINE_RENDERING_MATERIALFUNCTIONRESOURCE_HPP
#define ENGINE_RENDERING_MATERIALFUNCTIONRESOURCE_HPP

#include <Engine/Rendering/RenderResource.hpp>

#include <Engine/Core/MaterialFunctionImpl.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <Coral/Coral.hpp>

#include <memory>

namespace Reef::Rendering
{

class ENGINE_API MaterialFunctionResource : public RenderResource
{
public:

	MaterialFunctionResource(ResourceManager& resourceManager);

	/// Update the material functions's render resource
	bool update(const Reef::MaterialFunctionImpl& materialFunction, Coral::Context& context);

	/// Bind the material resource to the command buffer
	bool bind(Coral::CommandBuffer& commandBuffer);

	const Coral::ShaderModule& vertexShader() const;

	const Coral::ShaderModule& fragmentShader() const;

	const Coral::PipelineState& pipelineState() const;

private:

	bool createPipelineState(const Reef::MaterialFunctionImpl& materialFunction, Coral::Context& context);

	/// The pipeline state of the materials
	Coral::PipelineStatePtr mPipelineState;

	Coral::ShaderModulePtr mVertexShader;

	Coral::ShaderModulePtr mFragmentShader;

};

} // namespace Reef::Rendering

#endif //!ENGINE_RENDERING_MATERIALFUNCTIONRESOURCE_HPP
