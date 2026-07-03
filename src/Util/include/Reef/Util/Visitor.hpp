#ifndef REEF_UTIL_VISITOR_HPP
#define REEF_UTIL_VISITOR_HPP

#include <Reef/Util/Export.hpp>
#include <variant>

namespace Reef::Util
{

/*!
 * Visitor class definition for std::visit
 */
template<class... Callables>
struct UTIL_API Visitor : Callables...
{ 
    using Callables::operator()...;
};

/*!
 * \brief Apply the visitor to the given variant
 * \param variant The variant to be visited
 * \param visitor The visitor to be applied to the variant
 */
template<typename Variant, typename ...Callables>
auto visit(Variant&& variant, Visitor<Callables...>&& visitor) -> decltype(auto)
{
    return std::visit(std::forward<Visitor<Callables...>>(visitor), std::forward<Variant>(variant));
}

} // namespace Reef::Util

#endif //!REEF_UTIL_VISITOR_HPP
