module;

#include <Engine/System.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <mutex>
#include <vector>

module Engine.Application.EngineLayer;
import Engine.Application.WindowLayer;
import Engine.Application;

//
//import Engine.Rendering.Renderer;
//

//import Engine.Application;
//import Engine.GameObject;
//
//import Engine.Component.CameraComponent;
//import Engine.Component.DirectionalLightComponent;
//import Engine.Component.MeshComponent;
//import Engine.Component.SkyLightComponent;
//
//import Engine.Camera;
//import Engine.DirectionalLight;
//import Engine.SkyLight;
//
using namespace Reef;

namespace
{

//template <class T>
//inline void hashCombine(std::size_t& seed, const T& v)
//{
//	std::hash<T> hasher;
//	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//}
//
//
//void
//addRenderObjects(Engine::GameObject& entity, 
//				 const glm::mat4& viewMatrix,
//				 const glm::mat4& projectionMatrix,
//				 const glm::mat4& viewProjectionMatrix, 
//				 std::vector<Engine::Rendering::RenderObject>& results)
//{
//	auto localToWorlMatrix = entity.transform().localToWorldMatrix();
//	auto worldToLocalMatrix = entity.transform().worldToLocalMatrix();
//	glm::mat3 normalMatrix = glm::inverse(glm::transpose(localToWorlMatrix));
//
//	for (auto mc : entity.getComponents<Engine::MeshComponent>())
//	{
//		if (auto mesh = mc->mesh())
//		{
//			for (uint32_t i = 0; i < mesh->getNumPrimitives(); ++i)
//			{
//				auto& ro		= results.emplace_back();
//				ro.primitive	= mesh->getPrimitive(i);
//				ro.material		= ro.primitive->material();
//				if (auto material = mc->material(i))
//				{
//					ro.material = material;
//				}
//				ro.localToWorldMatrix = localToWorlMatrix;
//				ro.worldToLocalMatrix = worldToLocalMatrix;
//				ro.normalMatrix		  = normalMatrix;
//				ro.uniqueId			  = 0;
//				hashCombine(ro.uniqueId, i);
//				hashCombine(ro.uniqueId, mc->runtimeUniqueId());
//			}
//		}
//	}
//
//	for (auto child : entity.children())
//	{
//		addRenderObjects(*child, viewMatrix, projectionMatrix, viewProjectionMatrix, results);
//	}
//}

} // namespace


bool
EngineLayer::initialize()
{
	//if (auto windowLayer = application().getLayer<WindowLayer>())
	//{

	//}

	//return true;

	return true;
}


void
EngineLayer::start()
{

}


void 
EngineLayer::stop()
{
}


void
EngineLayer::update()
{
	//mScene.update(0.f);

	//resolveScene();
}
