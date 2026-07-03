#ifndef REEF_UTIL_INTERVALL_HPP
#define REEF_UTIL_INTERVALL_HPP


#include <Reef/Util/BoundingBox.hpp>

namespace Reef::Util
{

template<typename T>
using Intervall = BoundingBox<1, T>;

} // namespace Reef::Util

#endif // !REEF_UTIL_INTERVALL_HPP
