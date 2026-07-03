#ifndef REEF_CORE_MESHIMPL_HPP
#define REEF_CORE_MESHIMPL_HPP

#include <Reef/Core/Mesh.hpp>

#include <Reef/Rendering/IndexedGeometry.hpp>

namespace Reef
{

class MeshImpl : public Mesh
                    //        public SubclassOf<MeshImpl, Object>
{
public:

    MeshImpl();

    void setName(std::string_view name) override;

    const std::string& name() const override;

    uint32_t sectionCount() const override;

    uint32_t addSection(std::span<const glm::vec3> positions,
                        std::span<const glm::vec3> normals,
                        std::span<const glm::vec3> tangents,
                        std::span<const glm::vec2> texcoord0,
                        std::span<const uint32_t> indices) override;

    BoundingBox3D boundingBox() const override;

    std::shared_ptr<Reef::Rendering::IndexedGeometry> geometry();

    std::shared_ptr<const Reef::Rendering::IndexedGeometry> geometry() const;

private:

    std::string mName;

    std::shared_ptr<Reef::Rendering::IndexedGeometry> mGeometry;

}; // class MeshImpl

} // namespace Reef::Core

#endif // !REEF_CORE_MESHIMPL_HPP
