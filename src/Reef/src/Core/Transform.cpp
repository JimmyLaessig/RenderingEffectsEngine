#include <Reef/Core/Transform.hpp>

#include <Reef/Core/Entity.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform.hpp>

using namespace Reef;


Transform::Transform(Entity& entity)
	: mEntity(entity)
{
}


const glm::mat4&
Transform::modelMatrix() const
{
	if (!mModelMatrix)
	{
		auto T = glm::translate(mPosition);
		auto R = glm::toMat4(mRotation);
		auto S = glm::scale(mScale);

		mModelMatrix = T * R * S;
	}

	return *mModelMatrix;
}


const glm::mat4&
Transform::inverseModelMatrix() const
{
	if (!mInverseModelMatrix)
	{
		mInverseModelMatrix = glm::inverse(modelMatrix());
	}

	return *mInverseModelMatrix;
}


const glm::vec3&
Transform::localPosition() const
{
	return mPosition;
}


const glm::vec3&
Transform::localScale() const
{
	return mScale;
}


const glm::quat&
Transform::localRotation() const
{
	return mRotation;
}


glm::vec3
Transform::worldPosition() const
{
	if (auto parent = mEntity.parent())
	{
		auto wp = parent->transform().localToWorldMatrix() * glm::vec4(mPosition, 1.f);

		return glm::vec3(wp / wp[3]);
	}

	return mPosition;
}


glm::vec3
Transform::worldScale() const
{
	if (auto parent = mEntity.parent())
	{
		return parent->transform().worldScale() * mScale;
	}

	return mScale;
}


glm::quat
Transform::worldRotation() const
{
	if (auto parent = mEntity.parent())
	{
		return parent->transform().worldRotation() * mRotation;
	}

	return mRotation;
}


void
Transform::setLocalPosition(const glm::vec3& position)
{
	mPosition = position;
	resetCachedMatrices();
}


void
Transform::setLocalScale(const glm::vec3& scale)
{
	mScale = scale;
	resetCachedMatrices();
}


void
Transform::setLocalRotation(const glm::quat& rotation)
{
	mRotation = rotation;
	resetCachedMatrices();
}


void 
Transform::setLocalPose(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
	mPosition = position;
	mRotation = rotation;
	mScale    = scale;
	resetCachedMatrices();
}


void
Transform::setWorldPosition(const glm::vec3& position)
{
	if (auto parent = mEntity.parent())
	{
		auto pos = parent->transform().worldToLocalMatrix() * glm::vec4(position, 1.0f);

		mPosition = glm::vec3(pos / pos.w);
	}
	else
	{
		mPosition = position;
	}

	resetCachedMatrices();
}


void
Transform::setWorldScale(const glm::vec3& scale)
{
	if (auto parent = mEntity.parent())
	{
		mScale = scale / parent->transform().worldScale();
	}
	else
	{
		mScale = scale;
	}
	resetCachedMatrices();
}


void
Transform::setWorldRotation(const glm::quat& rotation)
{
	if (auto parent = mEntity.parent())
	{
		mRotation = glm::normalize(glm::inverse(parent->transform().worldRotation()) * rotation);
	}
	else
	{
		mRotation = glm::normalize(rotation);
	}
	resetCachedMatrices();
}


void
Transform::setWorldPose(const glm::vec3& worldPosition, const glm::quat& worldRotation)
{
	setWorldPosition(worldPosition);
	setWorldRotation(worldRotation);
}


void
Transform::setWorldPose(const glm::vec3& worldPosition, const glm::quat& worldRotation, const glm::vec3& worldScale)
{
	setWorldPosition(worldPosition);
	setWorldRotation(worldRotation);
	setWorldScale(worldScale);
}


glm::mat4
Transform::localToWorldMatrix() const
{
	if (auto parent = mEntity.parent())
	{
		return parent->transform().localToWorldMatrix() * modelMatrix();
	}

	return modelMatrix();
}


glm::mat4
Transform::worldToLocalMatrix() const
{
	return glm::inverse(localToWorldMatrix());
}


glm::vec3 
Transform::forward() const
{
	glm::vec3 v(0.f, 0.f, -1.f);

	return glm::normalize(mRotation * v);
}


glm::vec3 
Transform::right() const
{
	glm::vec3 v(1.f, 0.f, 0.f);
	return glm::normalize(mRotation * v);
}


glm::vec3 
Transform::up() const
{
	glm::vec3 v(0.f, 1.f, 0.f);
	return glm::normalize(mRotation * v);
}


void
Transform::lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
	auto rotation = glm::quatLookAt(center - eye, up);
	setWorldPose(eye, rotation, worldScale());
}


void
Transform::resetCachedMatrices()
{
	mModelMatrix.reset();
	mInverseModelMatrix.reset();
}
