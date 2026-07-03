#ifndef REEF_CORE_OBJECT_HPP
#define REEF_CORE_OBJECT_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/BaseClass.hpp>

#include <concepts>

namespace Reef
{

/*!
 * Base class of all serializable polymorphic data types.
 */
class REEF_API Object : public BaseClass<Object>
{
public:

    Object();

    /*!
     * \brief Get the unique id of the object.
     */
    uint64_t id() const;

private:

    uint64_t mId;

}; // class Object

} // namespace Reef

#endif // !REEF_CORE_OBJECT_HPP
