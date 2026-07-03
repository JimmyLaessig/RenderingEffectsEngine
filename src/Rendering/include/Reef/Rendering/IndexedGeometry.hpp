#ifndef REEF_RENDERING_INDEXEDGEOMETRY_HPP
#define REEF_RENDERING_INDEXEDGEOMETRY_HPP

#include <Reef/Rendering/IndexBuffer.hpp>

#include <Reef/Rendering/Resource.hpp>

#include <Reef/Util/BoundingBox.hpp>

#include <span>

namespace Reef::Rendering
{

/*!
 *
 */
class RENDERING_API IndexedGeometry : public Resource
{
public:

    /*!
     * \brief Add a new section to the geometry with the given vertex attributes and indices
     */
    uint32_t addSection(std::span<const glm::vec3> positions,
                        std::span<const glm::vec3> normals,
                        std::span<const glm::vec3> tangents,
                        std::span<const glm::vec2> texcoord0,
                        std::span<const uint16_t>  indices);

    uint32_t addSection(std::span<const glm::vec3> positions,
                        std::span<const glm::vec3> normals,
                        std::span<const glm::vec3> tangents,
                        std::span<const glm::vec2> texcoord0,
                        std::span<const uint32_t>  indices);

    // Get the format of the indices
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    IndexFormat indexFormat() const;

    // Get the primitive's indices
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    std::span<const std::byte> indices() const;

    // Get the primitive's per-vertex position attribute
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    std::span<const glm::vec3> positions() const;

    // Get the primitive's per-vertex normal attribute
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    std::span<const glm::vec3> normals() const;

    // Get the primitive's per-vertex tangent attribute
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    std::span<const glm::vec3> tangents() const;

    // Get the primitive's per-vertex texture coordinate attribute
    /*
    * \Note: This function is not thread-safe and should only be called from within a locked scope.
    */
    std::span<const glm::vec2> texcoords() const;
    
    uint32_t indexCount() const;

    uint32_t vertexCount() const;

    struct Section
    {
        uint32_t startIndex;

        uint32_t indexCount;
    };

    uint32_t sectionCount() const;

    std::vector<Section> sections() const;

    Reef::Util::BoundingBox3D boundingBox() const;

private:

    IndexBuffer mIndices{ IndexFormat::UNSIGNED_SHORT, 0 };

    std::vector<glm::vec3> mPositions;

    std::vector<glm::vec3> mNormals;

    std::vector<glm::vec3> mTangents;

    std::vector<glm::vec2> mTexcoords;

    std::vector<Section> mSections;

    Reef::Util::BoundingBox3D mBoundingBox;

}; // class IndexedGeometry

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_INDEXEDGEOMETRY_HPP
