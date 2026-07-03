#ifndef REEF_UTIL_SINGLETON_HPP
#define REEF_UTIL_SINGLETON_HPP

#include <Reef/Util/NonCopyable.hpp>
#include <Reef/Util/NonMovable.hpp>

namespace Reef::Util
{

/*!
 * Base class for a singleton using Meyer's singleton pattern
 */
template<typename T>
class UTIL_API Singleton : NonCopyable, NonMovable
{
public:

    /*!
     * \brief Get the instance of T
     * \return Returns the singleton object
     */
    static T& instance()
    {
        static T sInstance;
        return sInstance;
    }

protected:

    Singleton() = default;

};

} // namespace Reef::Util

#endif // !REEF_UTIL_SINGLETON_HPP