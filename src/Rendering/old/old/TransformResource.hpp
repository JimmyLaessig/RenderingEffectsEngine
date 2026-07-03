#ifndef ENGINE_RENDERING_TRANSFORMRESOURCE_HPP
#define ENGINE_RENDERING_TRANSFORMRESOURCE_HPP

#include <Engine/Core/Transform.hpp>

#include <Engine/Rendering/RenderResource.hpp>
#include <Engine/Rendering/SceneView.hpp>
#include <Engine/Rendering/DefaultUniforms.hpp>


namespace Reef::Rendering
{

class ENGINE_API TransformResource : public RenderResource
{
public:

	TransformResource(ResourceManager& resourceManager);

	Coral::Buffer* getUniformBuffer();

	bool update(const Transform& transform, Coral::Context& context);

	bool bind(Coral::CommandBuffer& commandBuffer);

private:

	std::unique_ptr<Reef::Rendering::UniformBuffer> mUniformBuffer{ nullptr };

};

} // Reef::Rendering 

#endif // !ENGINE_RENDERING_TRANSFORMRESOURCE_HPP
