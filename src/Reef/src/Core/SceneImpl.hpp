#ifndef REEF_SCENEIMPL_HPP
#define REEF_SCENEIMPL_HPP

#include <Reef/Core/Scene.hpp>

#include <Reef/Core/FrameTime.hpp>

#include <Reef/Rendering/Renderer.hpp>

#include "EventImpl.hpp"

#include "SceneObserver.hpp"

#include "../Component/ComponentStorage.hpp"

#include <memory>

#include <vector>

namespace Reef
{
class ApplicationImpl;
class SceneRenderer;

/*!
 + Implementation of the Scene interface
 */
class SceneImpl : public Scene
{
public:

    SceneImpl(ApplicationImpl& application);

    ~SceneImpl();

    Application& application() override;

    const Application& application() const override;

    void setView(Core::View* view) override;

    const Core::View* getView() const override;

    Core::View* getView() override;

    Reef::Event<uint32_t, uint32_t>& onViewSizeChanged() override;

    Entity* createEntity() override;

    void destroyEntity(Entity* entity) override;

    Component* findComponent(TypeId typeId) override;

    void findComponents(TypeId typeId, std::vector<Component*>& components, bool activeOnly) override;

    Reef::Event<Entity&>& onEntityCreated() override;

    Reef::Event<Entity&>& onEntityDestroyed() override;

    Reef::Event<Component&>& onComponentCreated() override;

    Reef::Event<Component&>& onComponentDestroyed() override;

    Reef::Event<Component&>& onComponentActiveChanged() override;

    Reef::Event<Component&>& onComponentPropertyChanged() override;

    /*!
     * \brief Perform a single frame update for the scene
     *
     * This is the per-frame tick that advances the scene simulation. Typical responsibilities
     * performed by this function include:
     * - updating component state using the provided FrameTime (delta / timestamp)
     * - notifying registered SceneObserver instances about scene updates
     * - forwarding timing information to the renderer or other subsystems as needed
     *
     * \param frameTime contains the elapsed time information for this frame. The function is
     * expected to be called once per frame from the application's main loop.
     */
    void tick(const FrameTime& frameTime);


    //void onUpdateUI();

    //void onViewportChanged(const Viewport& viewport);

    //Reef::Rendering::SceneView createSceneView();

    //Reef::Event<FrameTime>& onFrameUpdateEvent();

    //Reef::Event<>& onUpdateUIEvent();

    //Reef::Event<Viewport>& onViewportChangedEvent();

    //void initialize(Engine& engine);

    //template<typename T>
    //ComponentRange<T> find();

    //bool isRenderOutdated() const override;

    //void markRenderOutdated() override;

    /*!
     * \brief Get the ComponentStorage
     * The returned ComponentStorage object lifetime is bound to the lifetime of this SceneImpl
     * object.
     * \return Reference to the ComponentStorage
     */
    ComponentStorage& componentStorage();

    /*!
     * \brief Get the ComponentStorage
     * The returned ComponentStorage object lifetime is bound to the lifetime of this SceneImpl
     * object.
     * \return Const reference to the ComponentStorage
     */
    const ComponentStorage& componentStorage() const;

    void sendEntityCreated(Entity& entity);

    void sendEntityDestroyed(Entity& entity);

    void sendEntityTransformChanged(Entity& entity);

    void sendComponentCreated(Component& component);

    void sendComponentDestroyed(Component& component);

    void sendComponentPropertyChanged(Component& component);

    void sendComponentActiveChanged(Component& component);

private:

    void onViewSizeChanged(uint32_t width, uint32_t height);

    Application* mApplication{ nullptr };

    Reef::Core::View* mView{ nullptr };

    Reef::EventHandle mOnViewSizeChangedHandle;

    Reef::EventImpl<uint32_t, uint32_t> mOnViewSizeChangedEvent;

    Reef::EventImpl<Entity&> mOnEntityCreatedEvent;
    Reef::EventImpl<Entity&> mOnEntityDestroyedEvent;
    
    Reef::EventImpl<Entity&> mOnEntityTransformChanged;

    Reef::EventImpl<Component&> mOnComponentCreatedEvent;
    Reef::EventImpl<Component&> mOnComponentDestroyedEvent;

    Reef::EventImpl<Component&> mOnComponentActiveChangeEvent;
    Reef::EventImpl<Component&> mOnComponentPropertyChangedEvent;

    ComponentStorage mStorage;

    std::unique_ptr<Reef::SceneRenderer> mRenderer;

    //Reef::Event<FrameTime> mOnFrameUpdateEvent;

    //Reef::Event<> mOnUpdateUIEvent;

    //Reef::EventImpl<Viewport> mOnViewportChangedEvent;

    //Reef::Timestamp mStartTimestamp{};

    //bool mExitRequested{ false };

    //bool mIsRunning{ false };

    //Registry mRegistry;

    //std::atomic<bool> mRenderOutdated{ false };

}; // class SceneImpl

} // namespace Reef

#endif //!ENGINE_SCENEGRAPH_SCENEIMPL_HPP
