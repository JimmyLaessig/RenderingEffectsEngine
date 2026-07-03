#include "EventImpl.hpp"

using namespace Reef;

EventHandle::EventHandle(EventBase& event, uint64_t id)
    : mEvent(&event)
    , mId(id)
{}


EventHandle::EventHandle(EventHandle&& other) noexcept
{
    std::swap(mEvent, other.mEvent);
    std::swap(mId, other.mId);
}


EventHandle&
EventHandle::operator=(EventHandle&& other) noexcept
{
    std::swap(mEvent, other.mEvent);
    std::swap(mId, other.mId);
    return *this;
}


EventHandle::~EventHandle()
{
    reset();
}


void
EventHandle::reset()
{
    if (mEvent)
    {
        mEvent->unsubscribe(mId);
        mEvent = nullptr;
        mId    = 0;
    }
}


EventHandle::operator bool() const
{
    return mEvent != nullptr;
}


EventBase*
EventHandle::event()
{
    return mEvent;
}


const EventBase*
EventHandle::event() const
{
    return mEvent;
}


uint64_t
EventHandle::id() const
{
    return mId;
}