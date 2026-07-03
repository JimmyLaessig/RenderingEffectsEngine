#ifndef REEF_COMPONENT_COMPONENT_HPP
#define REEF_COMPONENT_COMPONENT_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/Object.hpp>

#include <Reef/Core/SubclassOf.hpp>

#include <concepts>

namespace Reef
{

class Entity;
class Transform;

class REEF_API Component: public SubclassOf<Component, Object>
{
public:

    Component();

    /*!
     * \brief Construct the component with the given owner entity.
     * \note This function is called by the constructing entity and should not be called directly.
     * \param owner The entity that owns the component.
     */
    void construct(Entity& owner);

    /*!
     * Get the owning entity of the component
     * \return Reference to the owning entity
     */
    virtual const Entity& owner() const;

    /*!
     * Get the owning entity of the component
     * \return Reference to the owning entity
     */
    virtual Entity& owner();

    /*!
     * \brief Get the transform of the component's entity
     */
    virtual Transform& transform();

    /*!
     * \brief Get the transform of the component's entity
     */
    virtual const Transform& transform() const;

    /*!
     * \brief (De-)activate the component
     */
    virtual void setActive(bool active);

    /*!
     * \brief Flag indicating if the component is active
     * \return Returns true if the component is active, false otherwise.
     */
    virtual bool isActive() const;

    /*!
     * \brief Called when the component is created. Override this function to perform
     *        initialization logic.
     */
    virtual void onComponentCreated();

    /*!
     * \brief Called when the component is destroyed. Override this function to perform
     *        destruction logic.
     */
    virtual void onComponentDestroyed();

private:

    Entity* mOwner;

    bool mActive;

}; // class Component

// Concept to determine if T derives from component
template<typename T>
concept IsComponent = std::derived_from<T, Component>;

} // namespace Reef

#endif // !REEF_COMPONENT_COMPONENT_HPP
