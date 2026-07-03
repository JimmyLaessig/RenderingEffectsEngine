#include "SceneRenderer.hpp"
#include "SceneImpl.hpp"
#include "MeshImpl.hpp"

#include <Reef/Component/CameraComponent.hpp>
#include <Reef/Component/MeshComponent.hpp>
#include <Reef/Core/Transform.hpp>

using namespace Reef;

SceneRenderer::SceneRenderer(Reef::Core::View& view, Reef::SceneImpl& scene)
    : mView(view)
    , mScene(scene)
    , mRenderer(Reef::Rendering::Renderer::create(view.nativeWindowHandle()))
{
    mOnComponentCreatedHandle = mScene.onComponentCreated().subscribe([this](Component& component)
    {
        onComponentCreated(component);
    });

    mOnComponentDestroyedHandle = mScene.onComponentCreated().subscribe([this](Component& component)
    {
        onComponentDestroyed(component);
    });

    mOnComponentActiveChangedHandle = mScene.onComponentActiveChanged().subscribe([this](Component& component)
    {
        onComponentActiveChanged(component);
    });
}


void
SceneRenderer::render()
{
    mRenderer->render(mMainCamera);
}


void
SceneRenderer::updateCamera(const CameraComponent& cameraComponent)
{
    mMainCamera.cameraInWorldMatrix = cameraComponent.transform().localToWorldMatrix();
    mMainCamera.camera              = cameraComponent.camera();
}


void
SceneRenderer::updateRenderObject(const MeshComponent& component)
{
    auto iter = mRenderObjects.find(component.id());

    if (iter == mRenderObjects.end())
    {
        auto ro = mRenderer->createRenderObject();

        iter = mRenderObjects.emplace(component.id(), ro).first;
    }

    auto ro = iter->second;
    ro->setVisible(component.isActive());
    ro->setLocalToWorldMatrix(component.transform().localToWorldMatrix());
   
    if (auto meshImpl = std::static_pointer_cast<const MeshImpl>(component.mesh()))
    {
        ro->setMesh(meshImpl->geometry());
    }
    else
    {
        ro->setMesh(nullptr);
    }
}


void
SceneRenderer::onComponentCreated(const Reef::Component& component)
{
}


void
SceneRenderer::onComponentDestroyed(const Reef::Component& component)
{
    auto iter = mRenderObjects.find(component.id());
    if (iter == mRenderObjects.end())
    {
        return;
    }

    mRenderer->destroyRenderObject(iter->second);
    mRenderObjects.erase(iter);
}


void 
SceneRenderer::onComponentActiveChanged(const Reef::Component& component)
{
    if (auto camera = Reef::cast<const CameraComponent>(&component))
    {
        updateCamera(*camera);
        return;
    }

    if (auto mesh = Reef::cast<const MeshComponent>(&component))
    {
        updateRenderObject(*mesh);
    }
}
