#include <Reef/Component/Component.hpp>

#include <Reef/Core/Entity.hpp>

#include "../Core/SceneImpl.hpp"

using namespace Reef;

Component::Component()
    : mOwner(nullptr)
    , mActive(false)
{
}


void
Component::construct(Entity& owner)
{
    mOwner = &owner;
}


const Entity&
Component::owner() const
{
    return *mOwner;
}


Entity&
Component::owner()
{
    return *mOwner;
}


Transform&
Component::transform()
{
    return mOwner->transform();
}


const Transform& 
Component::transform() const
{
    return mOwner->transform();
}


void
Component::setActive(bool active)
{
    std::swap(active, mActive);

    if (active != mActive)
    {
        auto& sceneImpl = static_cast<SceneImpl&>(owner().scene());
        sceneImpl.sendComponentActiveChanged(*this);
    }
}


bool
Component::isActive() const
{
    return mActive;
}


void
Component::onComponentCreated()
{
    auto& sceneImpl = static_cast<SceneImpl&>(owner().scene());
    sceneImpl.sendComponentCreated(*this);
}


void
Component::onComponentDestroyed()
{
    auto& sceneImpl = static_cast<SceneImpl&>(owner().scene());
    sceneImpl.sendComponentDestroyed(*this);
}
