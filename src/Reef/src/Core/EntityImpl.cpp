#include "EntityImpl.hpp"

#include "SceneImpl.hpp"

#include <Reef/Component/Component.hpp>

#include <algorithm>
#include <vector>
#include <memory>
#include <string>

using namespace Reef;

EntityImpl::EntityImpl()
    : mTransform(*this)
{
}


EntityImpl::~EntityImpl()
{
    destroyComponents();
}


void
EntityImpl::construct(SceneImpl& scene)
{
    mScene = &scene;
}


const std::string&
EntityImpl::name() const
{
    return mName;
}


void
EntityImpl::setName(std::string_view name)
{
    mName.assign(name.begin(), name.end());
}


void
EntityImpl::children(std::vector<std::reference_wrapper<Entity>> children, 
                     bool includeHierarchy)
{
    for (auto& child : mChildren)
    {
        children.push_back(*child);
        if (includeHierarchy)
        {
            child->children(children, includeHierarchy);
        }
    }
}


void
EntityImpl::children(std::vector<std::reference_wrapper<const Entity>> children, 
                     bool includeHierarchy) const
{
    for (auto& child : mChildren)
    {
        children.push_back(*child);
        if (includeHierarchy)
        {
            child->children(children, includeHierarchy);
        }
    }
}


Entity*
EntityImpl::parent()
{
    return mParent;
}


const Entity*
EntityImpl::parent() const
{
    return mParent;
}


void
EntityImpl::setParent(Entity* parent)
{
    if (mParent)
    {
        std::erase(mParent->mChildren, this);
    }

    if (mParent)
    {
        mParent->mChildren.push_back(this);
    }
}


Scene&
EntityImpl::scene()
{
    return *mScene;
}


const Scene&
EntityImpl::scene() const
{
    return *mScene;
}


Transform&
EntityImpl::transform()
{
    return mTransform;
}


const Transform&
EntityImpl::transform() const
{
    return mTransform;
}


void
EntityImpl::destroyComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter == mComponents.end())
    {
        return;
    }

    auto& storage = mScene->componentStorage();

    component->onComponentDestroyed();
    storage.destroyComponent(*iter);

    mComponents.erase(iter);
}


void 
EntityImpl::destroyComponents()
{
    auto& storage = mScene->componentStorage();

    for (auto component : mComponents)
    {
        component->onComponentDestroyed();
        storage.destroyComponent(component);
    }

    mComponents.clear();
}


Component*
EntityImpl::addComponent(TypeId typeId, bool activate)
{
    auto& storage = mScene->componentStorage();

    if (auto comp = storage.createComponent(typeId))
    {
        comp->construct(*this);
        mComponents.push_back(comp);

        comp->onComponentCreated();
        comp->setActive(activate);

        return comp;
    }

    return nullptr;
}


Component*
EntityImpl::findComponent(TypeId typeId)
{
    auto component = std::ranges::find_if(mComponents, [&](auto c) { return c->type() == typeId; });
    if (component == mComponents.end())
    {
        return nullptr;
    }
    return *component;
}
