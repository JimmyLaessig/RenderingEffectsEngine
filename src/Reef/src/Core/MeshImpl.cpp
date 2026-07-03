#include "MeshImpl.hpp"

#include <array>

using namespace Reef;


std::shared_ptr<Reef::Mesh>
Mesh::create()
{
    return std::make_shared<MeshImpl>();
}


MeshImpl::MeshImpl()
    : mGeometry(std::make_shared<Reef::Rendering::IndexedGeometry>())
{

}

void
MeshImpl::setName(std::string_view name)
{
    mName = name;
}


const std::string&
MeshImpl::name() const
{
    return mName;
}

uint32_t 
MeshImpl::sectionCount() const
{
    return static_cast<uint32_t>(mGeometry->sectionCount());
}


uint32_t
MeshImpl::addSection(std::span<const glm::vec3> positions,
                     std::span<const glm::vec3> normals,
                     std::span<const glm::vec3> tangents,
                     std::span<const glm::vec2> texcoord0,
                     std::span<const uint32_t> indices)
{
    return mGeometry->addSection(positions, normals, tangents, texcoord0, indices);
}


BoundingBox3D
MeshImpl::boundingBox() const
{
    auto bbox = mGeometry->boundingBox();
    return  { bbox.min(), bbox.max() };
}


std::shared_ptr<Reef::Rendering::IndexedGeometry>
MeshImpl::geometry()
{
    return mGeometry;
}


std::shared_ptr<const Reef::Rendering::IndexedGeometry> 
MeshImpl::geometry() const
{
    return mGeometry;
}


std::shared_ptr<Mesh>
Mesh::Sphere()
{
    static std::shared_ptr<Mesh> sMesh;

    if (!sMesh)
    {
        sMesh = MeshImpl::Sphere(32);
    }

    return sMesh;
}


std::shared_ptr<Mesh>
Mesh::Sphere(uint32_t numSubdivisions)
{
    return nullptr;
}


std::shared_ptr<Mesh>
Mesh::Quad()
{
    return nullptr;
}


std::shared_ptr<Mesh>
Mesh::Cube()
{
    auto mesh = std::make_shared<MeshImpl>();

    std::array positions
    {
        // -z
        glm::vec3{  .5f, -.5f, -.5f },
        glm::vec3{ -.5f, -.5f, -.5f },
        glm::vec3{  .5f,  .5f, -.5f },
        glm::vec3{ -.5f,  .5f, -.5f },

        // +z
        glm::vec3{ -.5f, -.5f,  .5f },
        glm::vec3{  .5f, -.5f,  .5f },
        glm::vec3{ -.5f,  .5f,  .5f },
        glm::vec3{  .5f,  .5f,  .5f },

        // -x
        glm::vec3{ -.5f, -.5f, -.5f },
        glm::vec3{ -.5f, -.5f,  .5f },
        glm::vec3{ -.5f,  .5f, -.5f },
        glm::vec3{ -.5f,  .5f,  .5f },

        // +x
        glm::vec3{ .5f, -.5f,  .5f },
        glm::vec3{ .5f, -.5f, -.5f },
        glm::vec3{ .5f,  .5f,  .5f },
        glm::vec3{ .5f,  .5f, -.5f },

        // -y
        glm::vec3{ -.5f, -.5f, -.5f },
        glm::vec3{  .5f, -.5f, -.5f },
        glm::vec3{ -.5f, -.5f,  .5f },
        glm::vec3{  .5f, -.5f,  .5f },

        // +y
        glm::vec3{ -.5f, .5f,  .5f },
        glm::vec3{  .5f, .5f,  .5f },
        glm::vec3{ -.5f, .5f, -.5f },
        glm::vec3{  .5f, .5f, -.5f },
    };

    std::array uvs
    {
        // -z
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },

        // +z
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },

        // -x
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },

        // +x
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },

        // -y
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },

        // +y
        glm::vec2{ 0.f, 0.f },
        glm::vec2{ 1.f, 0.f },
        glm::vec2{ 0.f, 1.f },
        glm::vec2{ 1.f, 1.f },
    };

    std::array normals
    {
        // -z
        glm::vec3{ 0.f, 0.f, -1.f },
        glm::vec3{ 0.f, 0.f, -1.f },
        glm::vec3{ 0.f, 0.f, -1.f },
        glm::vec3{ 0.f, 0.f, -1.f },

        // +z
        glm::vec3{ 0.f, 0.f, 1.f },
        glm::vec3{ 0.f, 0.f, 1.f },
        glm::vec3{ 0.f, 0.f, 1.f },
        glm::vec3{ 0.f, 0.f, 1.f },

        // -x
        glm::vec3{ -1.f, 0.f, 0.f },
        glm::vec3{ -1.f, 0.f, 0.f },
        glm::vec3{ -1.f, 0.f, 0.f },
        glm::vec3{ -1.f, 0.f, 0.f },

        // +x
        glm::vec3{ 1.f, 0.f, 0.f },
        glm::vec3{ 1.f, 0.f, 0.f },
        glm::vec3{ 1.f, 0.f, 0.f },
        glm::vec3{ 1.f, 0.f, 0.f },

        // -y
        glm::vec3{ 0.f, -1.f, 0.f },
        glm::vec3{ 0.f, -1.f, 0.f },
        glm::vec3{ 0.f, -1.f, 0.f },
        glm::vec3{ 0.f, -1.f, 0.f },

        // +y
        glm::vec3{ 0.f, 1.f, 0.f },
        glm::vec3{ 0.f, 1.f, 0.f },
        glm::vec3{ 0.f, 1.f, 0.f },
        glm::vec3{ 0.f, 1.f, 0.f },
    };

    std::array<uint32_t, 36> indices
    {
        // -z
        0, 1, 2,
        2, 1, 3,

        // +z
        4, 5, 6,
        6, 5, 7,

        // -x
        8, 9, 10,
        10, 9, 11,

        // +x
        12, 13, 14,
        14, 13, 15,

        // -y
        16, 17, 18,
        18, 17, 19,

        // +y
        20, 21, 22,
        22, 21, 23,
    };

    mesh->addSection(positions, normals, {}, uvs, indices);

    return mesh;
}


std::shared_ptr<Mesh>
Mesh::Plane()
{
    return nullptr;
}
