#ifndef REEF_UTIL_NONCOPYABLE_HPP
#define REEF_UTIL_NONCOPYABLE_HPP

#include <Reef/Util/Export.hpp>

namespace Reef::Util
{

/*!
 * Derive from this class to disable copy capabilities of the derived class.
 */
class UTIL_API NonCopyable
{
public:

    NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;

    NonCopyable& operator=(const NonCopyable&) = delete;

    virtual ~NonCopyable() = default;

}; // NonCopyable

} // namespace Reef::Util

#endif // !REEF_UTIL_NONCOPYABLE_HPP
