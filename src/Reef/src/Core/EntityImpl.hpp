#ifndef REEF_CORE_ENTITYIMPL_HPP
#define REEF_CORE_ENTITYIMPL_HPP

#include <Reef/Core/Entity.hpp>

#include <Reef/Core/Object.hpp>

#include <cstdint>


#include <vector>

namespace Reef
{

class Registry;
class SceneImpl;

class EntityImpl : public SubclassOf<EntityImpl, Entity>
{
public:

	EntityImpl();

	virtual ~EntityImpl();

	void construct(SceneImpl& scene);

	const std::string& name() const override;

	void setName(std::string_view name) override;

	Entity* parent() override;

	const Entity* parent() const override;

	void setParent(Entity* parent) override;

	void children(std::vector<std::reference_wrapper<Entity>> children, bool includeHierarchy) override;

	void children(std::vector<std::reference_wrapper<const Entity>> children, bool includeHierarchy) const override;

	Component* addComponent(TypeId type, bool activate) override;

	Component* findComponent(TypeId type) override;

	void destroyComponent(Component* component) override;

	void destroyComponents() override;

	Scene& scene() override;

	const Scene& scene() const override;

	Transform& transform() override;

	const Transform& transform() const override;

private:

	std::string mName;

	Transform mTransform;

	SceneImpl* mScene{ nullptr };

	EntityImpl* mParent{ nullptr };

	std::vector<EntityImpl*> mChildren;

	std::vector<Component*> mComponents;
};

} // namespace Reef

#endif // !REEF_CORE_ENTITYIMPL_HPP
