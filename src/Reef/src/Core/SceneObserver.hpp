#ifndef REEF_SCENEOBSERVER_HPP
#define REEF_SCENEOBSERVER_HPP

namespace Reef
{
class CameraComponent;
class MeshComponent;
class Transform;
class Entity;

/*!
 *
 */
class SceneObserver
{
public:

	virtual ~SceneObserver() = default;

	/*!
	 * \brief Called when a MeshComponent is created, one of it's properties is changed, or it's owning entity is moved.
	 */
	virtual void onComponentChanged(const MeshComponent& component) = 0;

	/*!*/
	virtual void onComponentCreated(const MeshComponent& component) = 0;

	/*!
	 * \brief Called when a MeshComponent is removed from the scene
	 */
	virtual void onComponentRemoved(const MeshComponent& component) = 0;

	/*!
	 * \brief Called when a CameraComponent is created, one of it's properties is changed, or it's owning entity is moved.
	 */
	virtual void onComponentChanged(const CameraComponent& component) = 0;

	/*!
	 * \brief Called when a CameraComponent is removed from the scene
	 */
	virtual void onComponentRemoved(const CameraComponent& component) = 0;

}; // SceneObserver

} // namespace Reef

#endif // !REEF_SCENEIMPLOBSERVER_HPP
