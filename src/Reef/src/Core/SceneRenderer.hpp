#ifndef REEF_SCENERENDERER_HPP
#define REEF_SCENERENDERER_HPP

#include "SceneObserver.hpp"

#include <Reef/Core/View.hpp>

#include <Reef/Rendering/Renderer.hpp>

namespace Reef
{
class SceneImpl;
class Component;

class SceneRenderer
{
public:

    SceneRenderer(Reef::Core::View& view, Reef::SceneImpl& scene);

    void render();

private:

    void updateCamera(const CameraComponent& cameraComponent);

    void updateRenderObject(const MeshComponent& component);

    void onComponentCreated(const Component& component);

    void onComponentDestroyed(const Component& component);

    void onComponentActiveChanged(const Component& component);

    Reef::Core::View& mView;

    Reef::SceneImpl& mScene;

    std::unique_ptr<Reef::Rendering::Renderer> mRenderer;

    std::unordered_map<uint64_t, Reef::Rendering::RenderObject*> mRenderObjects;

    Reef::Rendering::CameraInfo mMainCamera;

    Reef::EventHandle mOnComponentCreatedHandle;
    Reef::EventHandle mOnComponentDestroyedHandle;
    Reef::EventHandle mOnComponentActiveChangedHandle;

}; // class SceneRenderer

} // namespace Reef

#endif //!REEF_SCENERENDERER_HPP
