#include <Reef/Rendering/IndexedGeometry.hpp>

using namespace Reef::Rendering;

uint32_t
IndexedGeometry::addSection(std::span<const glm::vec3> positions,
                            std::span<const glm::vec3> normals,
                            std::span<const glm::vec3> tangents,
                            std::span<const glm::vec2> texcoord0,
                            std::span<const uint16_t> indices)
{
    auto start  = indexCount();
    auto count  = static_cast<uint32_t>(indices.size());
    auto offset = static_cast<uint32_t>(mPositions.size());

    mPositions.append_range(positions);
    mNormals.append_range(normals);
    mTangents.append_range(tangents);
    mTexcoords.append_range(texcoord0);
    mBoundingBox.add(positions);

    // We've exceeded the maximum number of vertices that can be indexed with 16-bit indices, so we
    // need to switch to 32-bit indices.
    if (offset >= std::numeric_limits<uint16_t>::max())
    {
        std::vector<uint32_t> indices32;
        indices32.reserve(indices.size());
        for (const auto& index : indices)
        {
            indices32.push_back(index + offset);
        }

        mIndices.append(std::span(indices32));
    }
    else
    {
        std::vector<uint16_t> indices16;
        indices16.reserve(indices.size());
        for (const auto& index : indices)
        {
            indices16.push_back(index + offset);
        }

        mIndices.append(std::span(indices16));
    }

    markOutdated();
    mSections.push_back({ start, count });
    return static_cast<uint32_t>(mSections.size()) - 1;
}


uint32_t
IndexedGeometry::addSection(std::span<const glm::vec3> positions,
                            std::span<const glm::vec3> normals,
                            std::span<const glm::vec3> tangents,
                            std::span<const glm::vec2> texcoord0,
                            std::span<const uint32_t> indices)
{
    auto start  = indexCount();
    auto count  = static_cast<uint32_t>(indices.size());
    auto offset = static_cast<uint32_t>(mPositions.size());

    mPositions.append_range(positions);
    mNormals.append_range(normals);
    mTangents.append_range(tangents);
    mTexcoords.append_range(texcoord0);
    mBoundingBox.add(positions);

    std::vector<uint32_t> indices32;
    indices32.reserve(indices.size());
    for (const auto& index : indices)
    {
        indices32.push_back(index + offset);
    }

    mIndices.append(std::span(indices32));

    markOutdated();
    mSections.push_back({ start, count });
    return static_cast<uint32_t>(mSections.size()) - 1;
}


std::vector<IndexedGeometry::Section>
IndexedGeometry::sections() const
{
    return mSections;
}


uint32_t 
IndexedGeometry::sectionCount() const
{
    return static_cast<uint32_t>(mSections.size());
}


Reef::Util::BoundingBox3D
IndexedGeometry::boundingBox() const
{
    return mBoundingBox;
}


IndexFormat
IndexedGeometry::indexFormat() const
{
    return mIndices.format();
}


uint32_t
IndexedGeometry::indexCount() const
{
    return static_cast<uint32_t>(mIndices.size());
}


uint32_t
IndexedGeometry::vertexCount() const
{
    return static_cast<uint32_t>(mPositions.size());
}


std::span<const std::byte>
IndexedGeometry::indices() const
{
    return mIndices.data();
}


std::span<const glm::vec3>
IndexedGeometry::positions() const
{
    return mPositions;
}


std::span<const glm::vec3>
IndexedGeometry::normals() const
{
    return mNormals;
}


std::span<const glm::vec3>
IndexedGeometry::tangents() const
{
    return mTangents;
}


std::span<const glm::vec2>
IndexedGeometry::texcoords() const
{
    return mTexcoords;
}


//std::shared_ptr<IndexedGeometry>
//IndexedGeometry::Sphere()
//{
//    static std::shared_ptr<IndexedGeometry> sMesh;
//
//    if (!sMesh)
//    {
//        sMesh = IndexedGeometry::Sphere(32);
//    }
//
//    return sMesh;
//}


//std::shared_ptr<IndexedGeometry>
//IndexedGeometry::Sphere(uint32_t numSubdivisions)
//{
// //float thetaStepSize = glm::pi<float>() / numSubdivisions;
// //float phiStepSize = Math::TWO_PI / numSubdivisions;
// //
// //std::vector<glm::vec3> positions;
// //std::vector<glm::vec3> normals;
// //std::vector<glm::vec2> uvs;
//
// //std::vector<uint32_t> indices;
//
// //for (uint32_t i = 0; i <= numSubdivisions; ++i)
// //{
// // float theta = -Math::HALF_PI + thetaStepSize * (i);
//
// // for (uint32_t j = 0; j <= numSubdivisions; ++j)
// // {
// //  float phi = j * phiStepSize;
//
// //  glm::vec2 latLon(phi, theta);
// //  glm::vec3 p = glm::normalize(Math::sphericalCoordsToCartesianCoords(latLon));
// //  positions.push_back(p);
// //  normals.push_back(p);
// //  glm::vec2 scale(Math::TWO_PI, Math::PI);
// //  glm::vec2 offset(0.f, 0.5f);
//
// //  auto uv = 1.f - latLon / scale + offset;
//
// //  uvs.push_back(uv);
// // }
// //}
//
// //// Build indices
// //for (uint32_t y = 0; y < numSubdivisions; ++y)
// //{
// // for (uint32_t x = 0; x < numSubdivisions; ++x)
// // {
// //  auto topLeft  = y * (numSubdivisions + 1) + x;
// //  auto topRight  = y * (numSubdivisions + 1) + x + 1;
// //  auto bottomLeft  = (y + 1) * (numSubdivisions + 1) + x;
// //  auto bottomRight = (y + 1) * (numSubdivisions + 1) + x + 1;
//
// //  // Only emit these triangles when not at the north pole
// //  if (y > 0)
// //  {
// //   indices.push_back(topLeft);
// //   indices.push_back(topRight);
// //   indices.push_back(bottomLeft);
// //  }
// //  // Only emit these triangles when not at the south pole
// //  if (y <= numSubdivisions)
// //  {
// //   indices.push_back(topRight);
// //   indices.push_back(bottomRight);
// //   indices.push_back(bottomLeft);
// //  }
// // }
// //}
//
// //auto mesh = Mesh::create();
// //auto& primitive = mesh->addPrimitive();
// //primitive.setPositions(positions);
// //primitive.setIndices(indices);
// //primitive.setNormals(normals);
// //primitive.setTexcoords(uvs);
// //primitive.recalculateTangents();
// //primitive.setMaterial(std::make_shared<Material>(*Material::DefaultPBR()));
//
// //return mesh;
//    return nullptr;
//}


//std::shared_ptr<IndexedGeometry>
//IndexedGeometry::Quad()
//{
//    static std::shared_ptr<IndexedGeometry> sMesh;
//
//    if (sMesh)
//    {
//        return sMesh;
//    }
//
//    std::array positions
//    {
//        glm::vec3(-1.f, -1.f, 0.f),
//        glm::vec3( 1.f, -1.f, 0.f),
//        glm::vec3(-1.f,  1.f, 0.f),
//        glm::vec3( 1.f,  1.f, 0.f),
//    };
//
//    std::array uvs
//    {
//        glm::vec2(0.f, 0.f),
//        glm::vec2(1.f, 0.f),
//        glm::vec2(0.f, 1.f),
//        glm::vec2(1.f, 1.f),
//    };
//
//    std::array normals
//    {
//        glm::vec3(0.f, 0.f, 1.f),
//        glm::vec3(0.f, 0.f, 1.f),
//        glm::vec3(0.f, 0.f, 1.f),
//        glm::vec3(0.f, 0.f, 1.f),
//    };
//
//    std::array<uint16_t, 6> indices
//    {
//        0, 1, 2,
//        2, 1, 3
//    };
//
//    sMesh = std::make_shared<IndexedGeometry>();
//    sMesh->setName("Quad");
//    sMesh->addSection(positions, normals, {}, uvs, indices);
//
//    return sMesh;
//}


//std::shared_ptr<IndexedGeometry>
//IndexedGeometry::Cube()
//{
//    static std::shared_ptr<IndexedGeometry> sMesh;
//
//    if (sMesh)
//    {
//        return sMesh;
//    }
//
//    std::array positions
//    {
//        // -z
//        glm::vec3{  .5f, -.5f, -.5f },
//        glm::vec3{ -.5f, -.5f, -.5f },
//        glm::vec3{  .5f,  .5f, -.5f },
//        glm::vec3{ -.5f,  .5f, -.5f },
//
//        // +z
//        glm::vec3{ -.5f, -.5f,  .5f },
//        glm::vec3{  .5f, -.5f,  .5f },
//        glm::vec3{ -.5f,  .5f,  .5f },
//        glm::vec3{  .5f,  .5f,  .5f },
//
//        // -x
//        glm::vec3{ -.5f, -.5f, -.5f },
//        glm::vec3{ -.5f, -.5f,  .5f },
//        glm::vec3{ -.5f,  .5f, -.5f },
//        glm::vec3{ -.5f,  .5f,  .5f },
//
//        // +x
//        glm::vec3{ .5f, -.5f,  .5f },
//        glm::vec3{ .5f, -.5f, -.5f },
//        glm::vec3{ .5f,  .5f,  .5f },
//        glm::vec3{ .5f,  .5f, -.5f },
//
//        // -y
//        glm::vec3{ -.5f, -.5f, -.5f },
//        glm::vec3{  .5f, -.5f, -.5f },
//        glm::vec3{ -.5f, -.5f,  .5f },
//        glm::vec3{  .5f, -.5f,  .5f },
//
//        // +y
//        glm::vec3{ -.5f, .5f,  .5f },
//        glm::vec3{  .5f, .5f,  .5f },
//        glm::vec3{ -.5f, .5f, -.5f },
//        glm::vec3{  .5f, .5f, -.5f },
//    };
//
//    std::array uvs
//    {
//        // -z
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//
//        // +z
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//
//        // -x
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//
//        // +x
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//
//        // -y
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//
//        // +y
//        glm::vec2{ 0.f, 0.f },
//        glm::vec2{ 1.f, 0.f },
//        glm::vec2{ 0.f, 1.f },
//        glm::vec2{ 1.f, 1.f },
//    };
//
//    std::array normals
//    {
//        // -z
//        glm::vec3{ 0.f, 0.f, -1.f },
//        glm::vec3{ 0.f, 0.f, -1.f },
//        glm::vec3{ 0.f, 0.f, -1.f },
//        glm::vec3{ 0.f, 0.f, -1.f },
//
//        // +z
//        glm::vec3{ 0.f, 0.f, 1.f },
//        glm::vec3{ 0.f, 0.f, 1.f },
//        glm::vec3{ 0.f, 0.f, 1.f },
//        glm::vec3{ 0.f, 0.f, 1.f },
//
//        // -x
//        glm::vec3{ -1.f, 0.f, 0.f },
//        glm::vec3{ -1.f, 0.f, 0.f },
//        glm::vec3{ -1.f, 0.f, 0.f },
//        glm::vec3{ -1.f, 0.f, 0.f },
//
//        // +x
//        glm::vec3{ 1.f, 0.f, 0.f },
//        glm::vec3{ 1.f, 0.f, 0.f },
//        glm::vec3{ 1.f, 0.f, 0.f },
//        glm::vec3{ 1.f, 0.f, 0.f },
//
//        // -y
//        glm::vec3{ 0.f, -1.f, 0.f },
//        glm::vec3{ 0.f, -1.f, 0.f },
//        glm::vec3{ 0.f, -1.f, 0.f },
//        glm::vec3{ 0.f, -1.f, 0.f },
//
//        // +y
//        glm::vec3{ 0.f, 1.f, 0.f },
//        glm::vec3{ 0.f, 1.f, 0.f },
//        glm::vec3{ 0.f, 1.f, 0.f },
//        glm::vec3{ 0.f, 1.f, 0.f },
//    };
//
//    std::array<uint16_t, 36> indices
//    {
//        // -z
//        0, 1, 2,
//        2, 1, 3,
//
//        // +z
//        4, 5, 6,
//        6, 5, 7,
//
//        // -x
//        8, 9, 10,
//        10, 9, 11,
//
//        // +x
//        12, 13, 14,
//        14, 13, 15,
//
//        // -y
//        16, 17, 18,
//        18, 17, 19,
//
//        // +y
//        20, 21, 22,
//        22, 21, 23,
//    };
//
//    sMesh = std::make_shared<IndexedGeometry>();
//    sMesh->setName("Cube");
//    sMesh->addSection(positions, normals, {}, uvs, indices);
//
//    return sMesh;
//}


//std::shared_ptr<IndexedGeometry>
//IndexedGeometry::Plane()
//{
//    static std::shared_ptr<IndexedGeometry> sMesh;
//
//    if (sMesh)
//    {
//        return sMesh;
//    }
//
//    constexpr static auto Size = 10;
//    constexpr static auto NumVertices = Size * Size;
//    std::array<glm::vec3, NumVertices> positions;
//    std::array<glm::vec3, NumVertices> normals;
//    std::array<glm::vec2, NumVertices> uvs;
//    constexpr static auto NumFaces = (Size - 1) * (Size - 1) * 2;
//    std::array<uint16_t, NumFaces * 3> indices;
//
//    // Build the grid
//    for (float z = 0; z < Size; ++z)
//    {
//        for (float x = 0; x < Size; ++x)
//        {
//            positions[z * Size + x] = glm::vec3(x - Size * 0.5f, 0.f, z - Size * 0.5f);
//            normals[z * Size + x] = glm::vec3(0.f, 1.f, 0.f);
//            uvs[z * Size + x]  = glm::vec2(x / (Size - 1.0f), z / (Size - 1.0f));
//        }
//    }
//
//    uint16_t i = 0;
//    // Build the triangles
//    for (uint16_t z = 0; z < Size - 1; ++z)
//    {
//        for (uint16_t x = 0; x < Size - 1; ++x)
//        {
//            uint16_t bottomLeft = z * Size + x;
//            uint16_t bottomRight = z * Size + x + 1;
//            uint16_t topLeft = (z + 1) * Size + x;
//            uint16_t topRight = (z + 1) * Size + x + 1;
//
//            indices[i++] = bottomRight;
//            indices[i++] = bottomLeft;
//            indices[i++] = topLeft;
//            indices[i++] = bottomRight;
//            indices[i++] = topLeft;
//            indices[i++] = topRight;
//        }
//    }
//
//    sMesh = std::make_shared<IndexedGeometry>();
//    sMesh->setName("Plane");
//    sMesh->addSection(positions, normals, {}, uvs, indices);
//
//    return sMesh;
//}
