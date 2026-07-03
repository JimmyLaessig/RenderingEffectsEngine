#ifndef REEF_SCRIPTABLECOMPONENT_HPP
#define REEF_SCRIPTABLECOMPONENT_HPP

#include <Reef/Export.hpp>

#include <Reef/Component/Component.hpp>
#include <Reef/Core/Entity.hpp>
#include <Reef/Core/Scene.hpp>

#include <Reef/Core/FrameTime.hpp>
#include <Reef/Core/Viewport.hpp>
#include <Reef/Core/Event.hpp>

#include <concepts>
#include <functional>

namespace Reef
{

template<typename T>
concept Tickable = requires(T t, const FrameTime& frameTime)
{
	{ t.tick(frameTime) } -> std::convertible_to<void>;
};


template<typename T>
concept TickableUI = requires(T t, const FrameTime& frameTime)
{
	{ t.tickUI(frameTime) } -> std::convertible_to<void>;
};


struct ComponentTickFunction
{
	std::function<void(FrameTime)> TickFunction;

	std::function<void()> TickUIFunction;
};


class REEF_API ScriptableComponent : public SubclassOf<ScriptableComponent, Component>
{
public:

	virtual void onComponentCreated();

    virtual void onComponentDestroyed() {}

    virtual void onComponentActivated() {}

    virtual void onComponentDeactivated() {}

	//virtual void deinitialize() override;

	virtual void setActive(bool active) override;

protected:

	ComponentTickFunction mTickFunction;

private:

	/*Event<FrameTime>::Handle mOnFrameUpdateHandle;

	Event<>::Handle mOnUpdateUIHandle;

	Event<Viewport>::Handle mOnViewportChangedHandle;*/

}; // class ScriptableComponent


// Concept to determine if T derives from ScriptableComponent
//template<typename T>
//concept IsScriptableComponent = std::derived_from<T, ScriptableComponent>&& IsComponent<T>;


/// Specialization of the SubclassOf CRTP helper for all classes the derive from ScriptableComponent
/**
 *
 **/
//template<typename Derived, typename Base>
//requires IsScriptableComponent<Base>
//class REEF_API SubclassOf<Derived, Base> : public Base
//{
//public:
//
//	SubclassOf()
//	{
//		auto self = static_cast<Derived*>(this);
//
//		if constexpr (HasOnFrameUpdate<Derived>)
//		{
//			self->mComponentCallbacks.onFrameUpdate = [self](FrameTime frameTime)
//			{
//				self->onFrameUpdate(frameTime);
//			};
//		}
//
//		if constexpr (HasOnViewportChanged<Derived>)
//		{
//			self->mComponentCallbacks.onViewportChanged = [self](const Viewport& viewport)
//			{
//				self->onViewportChanged(viewport);
//			};
//		}
//
//		if constexpr (HasOnComponentActivated<Derived>)
//		{
//			self->mComponentCallbacks.onComponentActivated = [self]()
//			{
//				self->onComponentActivated();
//			};
//		}
//
//		if constexpr (HasOnComponentDeactivated<Derived>)
//		{
//			self->mComponentCallbacks.onComponentDeactivated = [self]()
//			{
//				self->onComponentDeactivated();
//			};
//		}
//
//		if constexpr (HasOnComponentCreated<Derived>)
//		{
//			self->mComponentCallbacks.onComponentCreated = [self]()
//			{
//				self->onComponentCreated();
//			};
//		}
//
//		if constexpr (HasOnComponentDestroyed<Derived>)
//		{
//			self->mComponentCallbacks.onComponentDestroyed = [self]()
//			{
//				self->onComponentDestroyed();
//			};
//		}
//
//		if constexpr (HasOnUpdateUI<Derived>)
//		{
//			self->mComponentCallbacks.onUpdateUI = [self]()
//			{
//				self->onUpdateUI();
//			};
//		}
//	}
//
//	/// Get the type of the class
//	static const Type& classType()
//	{
//		static Type sType = Type::create<Derived>(&Base::classType());
//		return sType;
//	}
//
//	/// Get the type of the object
//	virtual const Type& type() const override
//	{
//		return classType();
//	}
//
//private:
//
//	// Register the component class with the registry during startup
//	static inline const bool sComponentRegistered = TypeRegistry::registerType<Derived>();
//};

} // namespace Reef

#endif // !REEF_SCRIPTABLECOMPONENT_HPP
