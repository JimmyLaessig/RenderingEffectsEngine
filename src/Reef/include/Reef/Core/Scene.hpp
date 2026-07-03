#ifndef REEF_CORE_SCENE_HPP
#define REEF_CORE_SCENE_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/Event.hpp>
#include <Reef/Core/TypeInfo.hpp>

#include <vector>

namespace Reef
{

class Entity;
class Application;
class Component;

namespace Core
{
    class View;
} // namespace Core

/*!
 *
 */
class REEF_API Scene
{
public:

    virtual ~Scene() = default;

    /*!
     * \brief Get the application
     * \return Returns a reference to the application 
     */
    virtual Application& application() = 0;

    /*!
     * \brief Get the application
     * \return Returns a reference to the application 
     */
    virtual const Application& application() const = 0;

    /*!
     * \brief Set the view to render the scene to.
     * Thew view is not owned by the scene and must remain valid as long as it is set to the scene.
     * \param view The view to render the scene to.
     */
    virtual void setView(Core::View* view) = 0;

    /*!
     * \brief Get the view that the scene is rendered to.
     * \return Pointer to the view or nullptr if no view is set.
     */
    virtual const Core::View* getView() const = 0;

    /*!
     * \brief Get the view that the scene is rendered to.
     * \return Pointer to the view or nullptr if no view is set.
     */
    virtual Core::View* getView() = 0;

    /*!
     * \brief Get the event that is invoked when the view size changes.
     */
    virtual Reef::Event<uint32_t, uint32_t>& onViewSizeChanged() = 0;

    //virtual void start() = 0;

    //virtual void stop() = 0;

    //virtual bool isRunning() const = 0;

    /*!
     * \brief Create a new entity
     * 
     * The entity is owned by the scene and will be destroyed when the scene is destroyed or when
     * the entity is explicitly destroyed via \ref destroyEntity.
     * 
     * \return Returns a pointer to the newly created entity. 
     */
    virtual Entity* createEntity() = 0;

    /*!
     * \brief Destroy the entity
     * \param entity Pointer to the entity to destroy. The entity must be owned by the scene.
     */
    virtual void destroyEntity(Entity* entity) = 0;

    /*!
     * \brief Find the first component of the given type in the scene
     * \param typeId The type id of the component
     * \return Returns a pointer to the component or nullptr if no component of the given type is found.
     */
    virtual Component* findComponent(TypeId typeId) = 0;

    /*!
     * \brief Find all components of the given type in the scene
     * \param typeId The type id of the component
     * \param components A vector to store the found components. The vector is cleared before adding the found
     *                   components.
     * \param activeOnly If true, only active components are returned, otherwise all components are
     *                   returned.
     */
    virtual void findComponents(TypeId typeId, std::vector<Component*>& components, bool activeOnly) = 0;

    /*!
     * \brief Event that is invoked when an entity is created.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Entity&>& onEntityCreated() = 0;

    /*!
     * \brief Event that is invoked when an entity is created.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Entity&>& onEntityDestroyed() = 0;

    /*!
     * \brief Event that is invoked when a component is created.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Component&>& onComponentCreated() = 0;

    /*!
     * \brief Event that is invoked when a component is destroyed.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Component&>& onComponentDestroyed() = 0;

    /*!
     * \brief Event that is invoked when a component is activated or deactivated.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Component&>& onComponentActiveChanged() = 0;

    /*!
     * \brief Event that is invoked when a component's property is changed.
     * \return Returns a reference to the event
     */
    virtual Reef::Event<Component&>& onComponentPropertyChanged() = 0;

}; // class Scene

} // namespace Reef

#endif // !REEF_CORE_SCENE_HPP
