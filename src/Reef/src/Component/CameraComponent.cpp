#include <Reef/Component/CameraComponent.hpp>

#include "../Core/EntityImpl.hpp"
#include "../Core/SceneImpl.hpp"

using namespace Reef;

const Reef::Util::Camera<float>&
CameraComponent::camera() const
{
	return mCamera;
}


const glm::uvec2&
CameraComponent::resolution() const
{
	return mCamera.resolution();
}


void
CameraComponent::setResolution(const glm::uvec2& resolution)
{
	mCamera.set(resolution, mCamera.nearFar(), mCamera.verticalFoV());
	static_cast<SceneImpl&>(owner().scene()).sendComponentPropertyChanged(*this);
}


float
CameraComponent::aspect() const
{
	return mCamera.aspect();
}


float
CameraComponent::nearPlane() const
{
	return mCamera.nearFar().x;
}


float
CameraComponent::farPlane() const
{
	return mCamera.nearFar().y;
}


void
CameraComponent::setNearFar(float near, float far)
{
	mCamera.set(mCamera.resolution(), { near, far }, mCamera.verticalFoV());
	static_cast<SceneImpl&>(owner().scene()).sendComponentPropertyChanged(*this);
}


float
CameraComponent::verticalFieldOfView() const
{
	return mCamera.verticalFoV();
}


void
CameraComponent::setVerticalFieldOfView(float fov)
{
	mCamera.set(mCamera.resolution(), mCamera.nearFar(), fov);
	static_cast<SceneImpl&>(owner().scene()).sendComponentPropertyChanged(*this);
}


const glm::mat4&
CameraComponent::projectionMatrix() const
{
	return mCamera.projectionMatrix();
}


glm::mat4
CameraComponent::viewMatrix() const
{
	return owner().transform().worldToLocalMatrix();
}


const glm::vec4&
CameraComponent::backgroundColor() const
{
	return mBackgroundColor;
}


void
CameraComponent::setBackgroundColor(const glm::vec4& clearColor)
{
	mBackgroundColor = clearColor;
	static_cast<SceneImpl&>(owner().scene()).sendComponentPropertyChanged(*this);
}


void
CameraComponent::onComponentCreated()
{
	SubclassOf<CameraComponent, Component>::onComponentCreated();

    mViewSizeChangedEventHandle = owner().scene().onViewSizeChanged().subscribe([&](uint32_t width, uint32_t height)
    {
         //onViewSizeChanged(width, height);
    });
}


void
CameraComponent::onComponentDestroyed()
{
    mViewSizeChangedEventHandle.reset();

	SubclassOf<CameraComponent, Component>::onComponentDestroyed();
}


//void
//CameraComponent::onViewSizeChanged(uint32_t width, uint32_t height)
//{
//	setResolution({ width, height });
//}
