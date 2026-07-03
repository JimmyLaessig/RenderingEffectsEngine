#ifndef REEF_CORE_ENTITY_HPP
#define REEF_CORE_ENTITY_HPP

#include <cstdint>

#include <Reef/Export.hpp>

#include <Reef/Core/Transform.hpp>

#include <Reef/Core/Object.hpp>
#include <Reef/Core/SubclassOf.hpp>

#include <string_view>
#include <string>
#include <tuple>
#include <span>
#include <vector>
#include <functional>

namespace Reef
{

class Component;
class Scene;

class REEF_API Entity : public SubclassOf<Entity, Object>
{
public:

	virtual ~Entity() = default;

	virtual const std::string& name() const = 0;

	virtual void setName(std::string_view name) = 0;

	virtual Entity* parent() = 0;

	virtual const Entity* parent() const = 0;

	virtual void setParent(Entity* parent) = 0;

	virtual void children(std::vector<std::reference_wrapper<Entity>> children, bool includeHierarchy) = 0;

	virtual void children(std::vector<std::reference_wrapper<const Entity>> children, bool includeHierarchy) const = 0;

	virtual Component* addComponent(TypeId type, bool activate = true) = 0;

	virtual Component* findComponent(TypeId type) = 0;

	virtual void destroyComponent(Component* component) = 0;

	virtual void destroyComponents() = 0;

	virtual Scene& scene() = 0;

	virtual const Scene& scene() const = 0;

	virtual Transform& transform() = 0;

	virtual const Transform& transform() const = 0;

	template<typename T>
	T* addComponent(bool activate = true);

	template<typename T, typename ...Ts>
	auto addComponents(bool activate = true);

	template<typename T>
	T* findComponent();
};


template<typename T>
T*
Entity::addComponent(bool activate)
{
	return static_cast<T*>(addComponent(T::classType(), activate));
}


template<typename T>
T*
Entity::findComponent()
{
	return static_cast<T*>(findComponent(T::classType()));
}


template<typename T, typename ...Ts>
auto
Entity::addComponents(bool activate)
{
	auto c1 = addComponent<T>(activate);
	return std::tuple(c1, addComponent<Ts>(activate)...);
}

} // namespace Reef

#endif // !REEF_ENTITY_HPP
