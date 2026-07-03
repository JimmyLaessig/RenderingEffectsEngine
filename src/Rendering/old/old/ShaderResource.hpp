#ifndef ENGINE_RENDERING_SHADERRESOURCE_HPP
#define ENGINE_RENDERING_SHADERRESOURCE_HPP

#include <memory>

#include <Engine/Rendering/RenderResource.hpp>

#include <Engine/Rendering/Shader.hpp>
#include <Coral/Coral.hpp>

namespace Reef::Rendering
{

class ResourceManager;

class ShaderResource : public RenderResource
{
public:

	ShaderResource(ResourceManager& resourceManager);

	bool update(const Reef::Rendering::Shader& shader, Coral::Context& context);

private:

};

} // Reef::Rendering 

#endif //! ENGINE_RENDERING_SHADERRESOURCE_HPP
