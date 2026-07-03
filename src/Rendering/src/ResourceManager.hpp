
#ifndef REEF_RENDERING_RESOURCEMANAGER_H
#define REEF_RENDERING_RESOURCEMANAGER_H

#include "IndexedGeometryResource.hpp"
#include "TransformResource.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <variant>

#include <glm/glm.hpp>

namespace Reef::Rendering
{

class IndexedGeometry;

class Renderer;

/*!
 * 
 */
class ResourceManager
{
public:

    ResourceManager(Renderer& renderer);

    IndexedGeometryResource* getResource(const IndexedGeometry& geometry);

    TransformResource* getResource(const glm::mat4& localToWorldMatrix, uint64_t instanceId);

    /*TextureResource* getResource(const Reef::TextureImpl& texture);

    MaterialFunctionResource* getResource(const Reef::MaterialFunctionImpl& materialFunction);*/

private:

    Renderer& mRenderer;

    using Resource = std::variant<std::unique_ptr<IndexedGeometryResource>,
                                  std::unique_ptr<TransformResource>>;

    std::unordered_map<size_t, Resource> mResources;

}; // class ResourceManager

} // namespace Reef::Rendering

#endif // !ENGINE_RENDERING_RESOURCEMANAGER_H

