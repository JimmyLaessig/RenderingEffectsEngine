#ifndef REEF_RENDERING_TRANSFORMRESOURCE_HPP
#define REEF_RENDERING_TRANSFORMRESOURCE_HPP

#include "RenderResource.hpp"
#include <Coral/Util/RAII.hpp>

#include <glm/glm.hpp>

namespace Reef::Rendering
{

class TransformResource : public RenderResource
{
public:

    TransformResource(ResourceManager& resourceManager);

    CoBuffer getUniformBuffer();

    bool update(const glm::mat4& localToWorldMatrix, CoContext context);

    bool bind(CoCommandBuffer commandBuffer);

private:

    Coral::BufferPtr mUniformBuffer;

}; // class TransformResource

} // Reef::Rendering

#endif // !REEF_RENDERING_TRANSFORMRESOURCE_HPP
