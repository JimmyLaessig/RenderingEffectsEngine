#ifndef REEF_UTIL_FINALLY_HPP
#define REEF_UTIL_FINALLY_HPP

#include <Reef/Util/Export.hpp>

#include <Reef/Util/NonCopyable.hpp>
#include <Reef/Util/NonMovable.hpp>

namespace Reef::Util
{

/*!
 * Utility class that invokes the passed action on destruction
 */
template<typename Action>
class Finally : public NonCopyable, public NonMovable
{
public:
    [[nodiscard]]
    Finally(Action&& action)
        : mAction(std::forward<Action>(action))
    {
    }

    ~Finally()
    {
        mAction();
    }

private:

    Action mAction;

}; // class Finally

} // namespace Reef::Util

#endif // !REEF_UTIL_FINALLY_HPP
