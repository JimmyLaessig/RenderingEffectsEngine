#include "SceneImpl.hpp"
#include "Platform/ApplicationImpl.hpp"
#include "EntityImpl.hpp"
#include "SceneRenderer.hpp"

#include <Reef/Component/CameraComponent.hpp>
#include <Reef/Component/MeshComponent.hpp>

#include <Reef/Core/View.hpp>

#include <Reef/Core/SmartPointer.hpp>


#include <glm/glm.hpp>

#include <chrono>
#include <mutex>
#include <string>
#include <vector>
#include <numeric>

using namespace Reef;


//void
//SceneImpl::start()
//{
//	if (mIsRunning)
//	{
//		// TODO: Log error that scene is already running
//		return;
//	}
//	mIsRunning = true;
//}
//
//
//void
//SceneImpl::stop()
//{
//	if (!mIsRunning)
//	{
//		// TODO: Log error that scene is not running
//		return;
//	}
//
//	mIsRunning = false;
//}


//void
//SceneImpl::onUpdateFrame(const FrameTime& frameTime)
//{
//	mOnFrameUpdateEvent.invoke(frameTime);
//}
//
//void
//SceneImpl::onUpdateUI()
//{
//	mOnUpdateUIEvent.invoke();
//}
//
//
//
//void
//SceneImpl::onViewportChanged(const Viewport& viewport)
//{
//	mOnViewportChangedEvent.invoke(viewport);
//}


//bool
//SceneImpl::isRunning() const
//{
//	return mIsRunning;
//}


//Reef::Rendering::SceneView
//SceneImpl::createSceneView()
//{
//	Reef::Rendering::SceneView view{};
//	auto cameras = find<CameraComponent>();
//	if (cameras.begin() != cameras.end())
//	{
//		auto& cameraComponent            = *cameras.begin();
//		view.camera						 = cameraComponent.camera();
//		view.viewMatrix					 = cameraComponent.viewMatrix();
//		view.viewProjectionMatrix	     = view.camera.projectionMatrix() * view.viewMatrix;
//		view.inverseViewProjectionMatrix = glm::inverse(view.viewProjectionMatrix);
//	}
//
//	auto renderObjectCount = 0;
//
//	auto meshComponents = find<MeshComponent>();
//	for (auto& meshComponent : meshComponents)
//	{
//		if (auto mesh = meshComponent.mesh())
//		{
//			renderObjectCount += mesh->primitiveCount();
//		}
//	}
//
//	view.renderObjects.reserve(renderObjectCount);
//	for (auto& meshComponent: meshComponents)
//	{
//		if (auto mesh = meshComponent.mesh())
//		{
//			Reef::Rendering::RenderObject ro;
//			ro.transform.objectId = reinterpret_cast<size_t>(&meshComponent.owner());
//			auto& transform       = meshComponent.owner().transform();
//
//			ro.transform.localToWorldMatrix = transform.localToWorldMatrix();
//			ro.transform.worldToLocalMatrix = transform.worldToLocalMatrix();
//			ro.transform.normalMatrix       = glm::mat3(glm::inverse(glm::transpose(ro.transform.localToWorldMatrix)));
//
//			for (uint32_t i = 0; i < mesh->primitiveCount(); ++i)
//			{
//				ro.primitive = static_pointer_cast<PrimitiveImpl>(mesh->getPrimitive(i));
//				ro.material  = static_pointer_cast<MaterialImpl>(meshComponent.material(i));
//				view.renderObjects.push_back(ro);
//			}
//		}
//	}
//
//	return view;
//}




SceneImpl::SceneImpl(ApplicationImpl& application)
	: mApplication(&application)
	, mStorage()
{
}


SceneImpl::~SceneImpl()
{
}


Application&
SceneImpl::application()
{
	return *mApplication;
}


const Application&
SceneImpl::application() const
{
	return *mApplication;
}


void 
SceneImpl::setView(Core::View* view)
{
	mOnViewSizeChangedHandle.reset();
    mView = view;
	mRenderer.reset();

	if (mView)
	{
		mOnViewSizeChangedHandle = mView->onViewResized().subscribe([this](uint32_t width, uint32_t height)
		{
			onViewSizeChanged(width, height);
		});

		mRenderer = std::make_unique<SceneRenderer>(*mView, *this);
	}

}


const Core::View*
SceneImpl::getView() const
{
    return mView;
}


Core::View*
SceneImpl::getView()
{
	return mView;
}


Reef::Event<uint32_t, uint32_t>&
SceneImpl::onViewSizeChanged()
{
    return mOnViewSizeChangedEvent;
}


Entity*
SceneImpl::createEntity()
{
    auto entity = mStorage.createEntity();
	if (!entity)
	{
		return nullptr;
	}

	entity->construct(*this);
	sendEntityCreated(*entity);

	return entity;
}


void
SceneImpl::destroyEntity(Entity* entity)
{
	sendEntityDestroyed(*entity);
	mStorage.destroyEntity(static_cast<EntityImpl*>(entity));
}


Component*
SceneImpl::findComponent(TypeId typeId)
{
	return nullptr;// return mRegistry.findComponent(type);
}


void
SceneImpl::findComponents(TypeId typeId, std::vector<Component*>& components, bool activeOnly)
{
	//return mRegistry.findComponents(type, components);
}


Reef::Event<Entity&>&
SceneImpl::onEntityCreated()
{
	return mOnEntityCreatedEvent;
}


Reef::Event<Entity&>&
SceneImpl::onEntityDestroyed()
{
	return mOnEntityDestroyedEvent;
}


Reef::Event<Component&>&
SceneImpl::onComponentCreated()
{
	return mOnComponentCreatedEvent;
}


Reef::Event<Component&>&
SceneImpl::onComponentDestroyed()
{
	return mOnComponentDestroyedEvent;
}


Reef::Event<Component&>&
SceneImpl::onComponentActiveChanged()
{
	return mOnComponentActiveChangeEvent;
}


Reef::Event<Component&>& 
SceneImpl::onComponentPropertyChanged()
{
	return mOnComponentPropertyChangedEvent;
}


void 
SceneImpl::onViewSizeChanged(uint32_t width, uint32_t height)
{
    mOnViewSizeChangedEvent.invoke(width, height);
}


void
SceneImpl::tick(const FrameTime& frameTime)
{
	mRenderer->render();
}


ComponentStorage&
SceneImpl::componentStorage()
{
	return mStorage;
}


const ComponentStorage&
SceneImpl::componentStorage() const
{
	return mStorage;
}


void
SceneImpl::sendEntityCreated(Entity& entity)
{
	mOnEntityCreatedEvent.invoke(entity);
}


void
SceneImpl::sendEntityDestroyed(Entity& entity)
{
	mOnEntityDestroyedEvent.invoke(entity);
}


void
SceneImpl::sendEntityTransformChanged(Entity& entity)
{
	mOnEntityTransformChanged.invoke(entity);
}


void
SceneImpl::sendComponentCreated(Component& component)
{
	mOnComponentCreatedEvent.invoke(component);
}


void
SceneImpl::sendComponentDestroyed(Component& component)
{
    mOnComponentDestroyedEvent.invoke(component);
}


void
SceneImpl::sendComponentPropertyChanged(Component& component)
{
	mOnComponentPropertyChangedEvent.invoke(component);
}


void
SceneImpl::sendComponentActiveChanged(Component& component)
{
    mOnComponentActiveChangeEvent.invoke(component);
}
