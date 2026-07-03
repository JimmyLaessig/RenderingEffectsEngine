#ifndef REEF_COMPONENT_CAMERACOMPONENT_HPP
#define REEF_COMPONENT_CAMERACOMPONENT_HPP

#include <Reef/Component/Component.hpp>

#include <Reef/Core/Event.hpp>

#include <Reef/Util/Camera.hpp>

namespace Reef
{

/*!
 *
 */
class REEF_API CameraComponent : public SubclassOf<CameraComponent, Component>
{
public:

	const Reef::Util::Camera<float>& camera() const;

	/// The size of the camera in pixel
	const glm::uvec2& resolution() const;

	/// Set the resolution of the camera in pixel
	void setResolution(const glm::uvec2& resolution);

	/// Get the aspect ratio of the camera ( size.x / size.y)
	float aspect() const;

	/// Get the near plane of the camera
	float nearPlane() const;

	/// Get the far plane of the camera
	float farPlane() const;

	/// Set the near plane of the camera in scene units
	void setNearFar(float nearPlane, float farPlane);

	/// Set the vertical field of view in degrees
	void setVerticalFieldOfView(float fov);

	/// The vertical field of view in degrees
	float verticalFieldOfView() const;

	/// The projection matrix of the camera
	const glm::mat4& projectionMatrix() const;

	/// The view matrix of the camera transforms from world space to view space
	glm::mat4 viewMatrix() const;

	const glm::vec4& backgroundColor() const;

	void setBackgroundColor(const glm::vec4& clearColor);

	virtual void onComponentCreated() override;

	virtual void onComponentDestroyed() override;

private:

    Reef::EventHandle mViewSizeChangedEventHandle;

	Reef::Util::Camera<float> mCamera;

	glm::vec4 mBackgroundColor{ 0.f, 0.f, 0.f, 1.f };

}; // class CameraComponent

} // namespace Reef

#endif // !ENGINE_COMPONENT_CAMERACOMPONENT_HPP
