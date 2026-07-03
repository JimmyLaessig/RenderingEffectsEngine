#include <Reef/Export.hpp>

#include <Reef/Component/ScriptableComponent.hpp>

#include <Reef/Core/Entity.hpp>

using namespace Reef;


using Base = SubclassOf<ScriptableComponent, Component>;


void
ScriptableComponent::onComponentCreated()
{
    Base::onComponentCreated();

    /*auto& sceneImpl = static_cast<SceneImpl&>(scene());

    if (mComponentCallbacks.onFrameUpdate)
    {
        mOnFrameUpdateHandle = sceneImpl.onFrameUpdateEvent().subscribe([this](const FrameTime& frameTime)
        {
            if (isActive())
            {
                mComponentCallbacks.onFrameUpdate(frameTime);
            }
        });
    }

    if (mComponentCallbacks.onUpdateUI)
    {
        mOnUpdateUIHandle = sceneImpl.onUpdateUIEvent().subscribe([this]()
        {
            if (isActive())
            {
                mComponentCallbacks.onUpdateUI();
            }
        });
    }

    if (mComponentCallbacks.onViewportChanged)
    {
        mOnViewportChangedHandle = sceneImpl.onViewportChangedEvent().subscribe([this](const Viewport& viewport)
        {
            if (isActive())
            {
                mComponentCallbacks.onViewportChanged(viewport);
            }
        });
    }

    if (mComponentCallbacks.onComponentCreated)
    {
        mComponentCallbacks.onComponentCreated();
    }*/
}


//void
//ScriptableComponent::deinitialize()
//{
//    //setActive(false);
//
//    //if (mComponentCallbacks.onComponentDestroyed)
//    //{
//    //    mComponentCallbacks.onComponentDestroyed();
//    //}
//
//    //Base::deinitialize();
//}


void
ScriptableComponent::setActive(bool active)
{
    //if (Base::setActive(active))
    //{
    //    if (active)
    //    {
    //        if (mComponentCallbacks.onComponentActivated)
    //        {
    //            mComponentCallbacks.onComponentActivated();
    //        }
    //    }
    //    else
    //    {
    //        if (mComponentCallbacks.onComponentDeactivated)
    //        {
    //            mComponentCallbacks.onComponentDeactivated();
    //        }
    //    }
    //}
}
