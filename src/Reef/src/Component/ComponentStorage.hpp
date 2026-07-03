#ifndef REEF_COMPONENT_COMPONENTSTORAGE_HPP
#define REEF_COMPONENT_COMPONENTSTORAGE_HPP

#include <Reef/Util/Hive.hpp>

#include <Reef/Core/TypeInfo.hpp>

#include <unordered_map>

namespace Reef
{

class EntityImpl;
class Component;
class SceneImpl;

/*!
 *
 */
class ComponentStorage
{
public:

    ComponentStorage();

    EntityImpl* createEntity();

    void destroyEntity(EntityImpl* entity);

    Component* createComponent(TypeId type);

    void destroyComponent(Component* component);

    Component* findComponent(TypeId type);

    void findComponents(TypeId type, std::vector<Component*>& components);

private:

    Reef::Util::Hive<Component>* getHive(TypeId type);

    std::unordered_map<TypeId, Reef::Util::Hive<Component>> mComponentHives;

    Reef::Util::Hive<EntityImpl> mEntities;

}; // class ComponentStorage

} // namespace Reef

#endif // !REEF_COMPONENT_COMPONENTSTORAGE_HPP
