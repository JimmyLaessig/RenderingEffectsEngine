#ifndef REEF_CORE_EVENTIMPL_HPP
#define REEF_CORE_EVENTIMPL_HPP 

#include <Reef/Core/Event.hpp>

namespace Reef
{

template<typename... Args>
class EventImpl : public Event<Args...>
{
public:

    EventHandle
    subscribe(std::function<void(Args...)> && func) override
    {
        auto id = mIdCounter++;
        mSubscribers.emplace(id, func);

        return EventHandle(*this, id);
    }

    void
    unsubscribe(uint64_t id) override
    {
        mSubscribers.erase(id);
    }

    template<typename ...Params>
    void invoke(Params&&... params)
    {
        for (const auto& [obj, callback] : mSubscribers)
        {
            callback(params...);
        }
    }

private:

    std::unordered_map<size_t, std::function<void(Args...)>> mSubscribers;

    uint64_t mIdCounter{ 0 };

}; // class EventImpl

} // namespace Reef

#endif // !REEF_CORE_EVENTIMPL_HPP
