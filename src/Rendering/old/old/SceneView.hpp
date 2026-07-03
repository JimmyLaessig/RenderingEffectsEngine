#ifndef ENGINE_RENDERING_SCENEVIEW_HPP
#define ENGINE_RENDERING_SCENEVIEW_HPP

#include <Engine/Core/Camera.hpp>
#include <Engine/Core/PrimitiveImpl.hpp>
#include <Engine/Core/MaterialImpl.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

#include <imgui_threaded_rendering/imgui_threaded_rendering.h>

namespace Reef::Rendering
{

struct Transform
{
	glm::mat4 localToWorldMatrix{ 1.f };

	glm::mat4 worldToLocalMatrix{ 1.f };

	glm::mat3 normalMatrix{ 1.f };

	size_t objectId{ 0 };
};


struct ENGINE_API RenderObject
{
	/// The transform data of the render object
	Transform transform{};

	/// The primitive of the render object
	std::shared_ptr<Reef::PrimitiveImpl> primitive;

	/// The material of the render object
	std::shared_ptr<Reef::MaterialImpl> material;
};


struct ENGINE_API SceneView
{	
	/// The camera through which to view the scene
	Reef::Camera<float> camera;
	
	glm::vec4 clearColor;
	/// View matrix of the camera
	glm::mat4 viewMatrix;
	/// World-space position of the camera
	glm::vec3 cameraPosition;
	/// View-projection matrix of the camera
	glm::mat4 viewProjectionMatrix;
	/// Inverse view-projection matrix of the camera
	glm::mat4 inverseViewProjectionMatrix;
	/// The 3D objects in the scene
	std::vector<RenderObject> renderObjects;

	std::shared_ptr<ImDrawDataSnapshot> drawData;
};

} // namespace Reef

#endif // !ENGINE_RENDERING_SCENEVIEW_HPP
