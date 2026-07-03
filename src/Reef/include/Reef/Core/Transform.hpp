#ifndef REEF_CORE_TRANSFORM_HPP
#define REEF_CORE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <optional>

namespace Reef
{
class Entity;

class Transform
{
public:

    Transform(Entity& entity);

	const glm::mat4& modelMatrix() const;

	const glm::mat4& inverseModelMatrix() const;

	const glm::vec3& localPosition() const;

	const glm::vec3& localScale() const;

	const glm::quat& localRotation() const;

	glm::vec3 worldPosition() const;

	glm::vec3 worldScale() const;

	glm::quat worldRotation() const;

	void setLocalPosition(const glm::vec3& position);

	void setLocalScale(const glm::vec3& scale);

	void setLocalRotation(const glm::quat& rotation);

	void setLocalPose(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

	void setWorldPosition(const glm::vec3& position);

	void setWorldScale(const glm::vec3& scale);

	void setWorldRotation(const glm::quat& rotation);

	void setWorldPose(const glm::vec3& worldPosition, const glm::quat& worldRotation);

	void setWorldPose(const glm::vec3& worldPosition, const glm::quat& worldRotation, const glm::vec3& worldScale);

	glm::mat4 localToWorldMatrix() const;

	glm::mat4 worldToLocalMatrix() const;

	glm::vec3 forward() const;

	glm::vec3 right() const;

	glm::vec3 up() const;

	void lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);

private:

	void resetCachedMatrices();

    Entity& mEntity;
    glm::vec3 mPosition{ 0.f, 0.f, 0.f };
    glm::vec3 mScale{ 1.f, 1.f, 1.f };
    glm::quat mRotation{ 1.f, 0.f, 0.f, 0.f };
    mutable std::optional<glm::mat4> mModelMatrix;
    mutable std::optional<glm::mat4> mInverseModelMatrix;

}; // class Transform

} // namespace Reef

#endif // !REEF_CORE_TRANSFORM_HPP
