#ifndef REEF_CORE_EVENT_HPP
#define REEF_CORE_EVENT_HPP

#include <Reef/Export.hpp>

#include <functional>

namespace Reef
{

class EventHandle;

class REEF_API EventBase
{
public: 

    virtual ~EventBase() = default;

    virtual void unsubscribe(uint64_t id) = 0;

}; // class EventBase

/*!
 *
 */
class REEF_API EventHandle
{
public:

    EventHandle() = default;

    EventHandle(EventBase& event, uint64_t id);

    EventHandle(EventHandle&& other) noexcept;

    EventHandle& operator=(EventHandle&& other) noexcept;

    ~EventHandle();

    operator bool() const;

    void reset();

    EventBase* event();

    const EventBase* event() const;

    uint64_t id() const;

private:

    EventBase* mEvent{ nullptr };

    uint64_t mId{ 0 };

}; // class EventHandle

/*!
 * 
 */
template<typename ...Args>
class REEF_API Event : public EventBase
{
public:

    ~Event() = default;

    virtual EventHandle subscribe(std::function<void(Args...)>&& func) = 0;

};// class Event

} // namespace Reef

#endif // !ENGINE_CORE_EVENT_HPP
