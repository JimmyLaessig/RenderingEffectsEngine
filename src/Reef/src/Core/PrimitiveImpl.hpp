#ifndef ENGINE_CORE_PRIMITIVEIMPL_HPP
#define	ENGINE_CORE_PRIMITIVEIMPL_HPP

#include <Engine/System.hpp>

#include <Engine/Core/Primitive.hpp>
#include <Engine/Core/Resource.hpp>

#include <vector>

namespace Reef
{

class ENGINE_API PrimitiveImpl : public Primitive, 
	                             public SubclassOf<PrimitiveImpl, Resource>
{
public:

	PrimitiveImpl();

	// Set the attributes of the primitive
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	bool set(std::span<const uint16_t> indices,
		     std::span<const glm::vec3> positions,
		     std::span<const glm::vec3> normals,
		     std::span<const glm::vec3> tangents,
		     std::span<const glm::vec2> texCoords) override;

	// Set the attributes of the primitive
	/*
     * \Note: This function is not thread-safe and should only be called from within a locked scope.
     */
	bool set(std::span<const uint32_t> indices,
		     std::span<const glm::vec3> positions,
		     std::span<const glm::vec3> normals,
		     std::span<const glm::vec3> tangents,
		     std::span<const glm::vec2> texCoords) override;

	// Get the format of the indices
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	IndexFormat indexFormat() const override;

	// Get the primitive's indices
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	std::span<const std::byte> indices() const override;

	// Get the primitive's per-vertex position attribute
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	std::span<const glm::vec3> positions() const override;

	// Get the primitive's per-vertex normal attribute
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	std::span<const glm::vec3> normals() const override;

	// Get the primitive's per-vertex tangent attribute
	/*
	 * \Note: This function is not thread-safe and should only be called from within a locked scope.
	 */
	std::span<const glm::vec3> tangents() const override;

	// Get the primitive's per-vertex texture coordinate attribute
	/*
		* \Note: This function is not thread-safe and should only be called from within a locked scope.
		*/
	std::span<const glm::vec2> texcoords() const override;

	// Get the primitive's indices
	/*
		* \Note: This function is not thread-safe and should only be called from within a locked scope.
		*/
	std::shared_ptr<Material> material() override;

	// Get the primitive's material
	/*
		* \Note: This function is not thread-safe and should only be called from within a locked scope.
		*/
	std::shared_ptr<const Material> material() const override;

	// Set the primitive's material
	/*
		* \Note: This function is not thread-safe and should only be called from within a locked scope.
		*/
	void setMaterial(std::shared_ptr<Material> material) override;

	// Get the bounding box of the primitive
	/*
		* \Note: This function is not thread-safe and should only be called from within a locked scope.
		*/
	const BoundingBox3D& boundingBox() const override;

private:

	bool set(std::span<const std::byte> indices,
		     IndexFormat indexFormat,
		     std::span<const glm::vec3> positions,
		     std::span<const glm::vec3> normals,
		     std::span<const glm::vec3> tangents,
		     std::span<const glm::vec2> texCoords);

	void recalculateTangents();

	void recalculateNormals();

	void recalculateBoundingBox();

	IndexFormat mIndexFormat{ IndexFormat::UNSIGNED_SHORT };

	std::vector<std::byte> mIndices;

	std::vector<glm::vec3> mPositions;

	std::vector<glm::vec3> mNormals;

	std::vector<glm::vec3> mTangents;

	std::vector<glm::vec2> mTexCoords;

	BoundingBox3D mBoundingBox{ glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f) };

	std::shared_ptr<Material> mMaterial;
};

} // namespace Reef

#endif // !ENGINE_CORE_PRIMITIVEIMPL_HPP
