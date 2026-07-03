#ifndef REEF_UTIL_NONMOVABLE_HPP
#define REEF_UTIL_NONMOVABLE_HPP

#include <Reef/Util/Export.hpp>

namespace Reef::Util
{

/*!
 * Derive from this class to disable move capabilities of the derived class.
 */
class UTIL_API NonMovable
{
public:

    NonMovable() = default;

    NonMovable(NonMovable&&) = delete;

    NonMovable& operator=(NonMovable&&) = delete;

    virtual ~NonMovable() = default;

}; // class NonMovable

} // namespace Reef

#endif // !REEF_UTIL_NONMOVABLE_HPP
