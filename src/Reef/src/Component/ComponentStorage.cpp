#include "ComponentStorage.hpp"

#include <Reef/Component/Component.hpp>

#include "../Core/EntityImpl.hpp"

using namespace Reef;

namespace
{

template<typename T>
class FactoryWrapper : public Reef::Util::Hive<T>::Factory
{
public:

    FactoryWrapper(Reef::TypeFactory& factory)
        : mFactory(factory)
    {}

    size_t objectSize() const override
    {
        return mFactory.objectSize();
    }

    void constructAt(void* address) override
    {
        mFactory.constructAt(address);

    }

private:

    Reef::TypeFactory& mFactory;

}; // class FactoryImpl

} // namespace

ComponentStorage::ComponentStorage()
    : mEntities(std::make_unique<FactoryWrapper<EntityImpl>>(*Reef::typeInfo(EntityImpl::classType()).factory()))
{
}


EntityImpl*
ComponentStorage::createEntity()
{
    return mEntities.emplace();
}


void
ComponentStorage::destroyEntity(EntityImpl* entity)
{
    mEntities.erase(entity);
}


Component*
ComponentStorage::createComponent(TypeId type)
{
    auto hive = getHive(type);
    if (!hive)
    {
        return nullptr;
    }

    return hive->emplace();
}


void
ComponentStorage::destroyComponent(Component* component)
{
    if (component == nullptr)
    {
        return;
    }

    auto typeId = component->type();

    auto hive = getHive(typeId);
    if (!hive)
    {
        // This should never happen
        return;
    }

    hive->erase(component);

    if (hive->empty())
    {
        mComponentHives.erase(typeId);
    }
}


Reef::Util::Hive<Component>*
ComponentStorage::getHive(TypeId type)
{
    auto iter = mComponentHives.find(type);
    if (iter == mComponentHives.end())
    {
        auto factory = Reef::typeInfo(type).factory();
        if (!factory)
        {
            return nullptr;
        }

        auto factoryWrapper = std::make_unique<FactoryWrapper<Component>>(*factory);
        iter = mComponentHives.emplace(type, Reef::Util::Hive<Component>(std::move(factoryWrapper))).first;
    }
     
    if (iter == mComponentHives.end())
    {
        return nullptr;
    }

    return &iter->second;
}


Component*
ComponentStorage::findComponent(TypeId type)
{
    if (auto hive = getHive(type))
    {
        auto iter = hive->begin();

        if (iter != hive->end())
        {
            return *iter;
        }
    }

    return nullptr;
}


void
ComponentStorage::findComponents(TypeId type, std::vector<Component*>& components)
{
    if (auto hive = getHive(type))
    {
        auto begin = hive->begin();
        auto end   = hive->end();
        components.reserve(hive->size());
        components.assign(begin, end);
    }
}
