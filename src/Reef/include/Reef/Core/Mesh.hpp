#ifndef REEF_CORE_MESH_HPP
#define REEF_CORE_MESH_HPP

#include <Reef/Export.hpp>

#include <glm/glm.hpp>
#include <memory>
#include <span>
#include <string_view>
#include <string>

namespace Reef
{

struct BoundingBox3D
{
	glm::vec3 min;
	glm::vec3 max;
};

struct BoundingSphere
{
    glm::vec3 center;
    float radius;
};

class REEF_API Mesh
{
public:

	static std::shared_ptr<Mesh> create();

	static std::shared_ptr<Mesh> Sphere();

	static std::shared_ptr<Mesh> Sphere(uint32_t numSubdivisions);

	static std::shared_ptr<Mesh> Quad();

	static std::shared_ptr<Mesh> Cube();

	static std::shared_ptr<Mesh> Plane();

	virtual ~Mesh() = default;

	virtual void setName(std::string_view name) = 0;

	virtual const std::string& name() const = 0;

	//virtual std::shared_ptr<Material> material(uint32_t index) = 0;

	virtual uint32_t sectionCount() const = 0;

	virtual uint32_t addSection(std::span<const glm::vec3> positions, 
		                        std::span<const glm::vec3> normals, 
		                        std::span<const glm::vec3> tangents,
		                        std::span<const glm::vec2> texcoord0,
		                        std::span<const uint32_t> indices) = 0;

	virtual BoundingBox3D boundingBox() const = 0;

}; // class Mesh

} // namespace Reef

#endif // !REEF_CORE_MESH_HPP
