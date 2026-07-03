#ifndef REEF_CORE_BASECLASS_HPP
#define REEF_CORE_BASECLASS_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/TypeInfo.hpp>

namespace Reef
{

/*!
 * Base class of all serializable polymorphic data types
 */ 
template<typename T>
class REEF_API BaseClass
{
public:

    virtual ~BaseClass() = default;

    /*!
     * \brief Get the type of the class
     */
    static TypeId classType()
    {
        static TypeId sTypeId = registerType<T>();
        return sTypeId;
    }

    /*!
     * \brief Get the type id of the object
     */
    virtual TypeId type() const
    {
        return classType();
    }

private:

    static inline const bool sTypeRegistered = classType() != INVALID_TYPE_ID;

}; // class BaseClass


template<typename Derived, typename Base>
Derived* cast(Base* base)
{
    if (!typeInfo(Derived::classType()).subclassOf(base->type()))
    {
        return nullptr;
    }
    return static_cast<Derived*>(base);
}

template<typename Derived, typename Base>
const Derived* cast(const Base* base)
{
    if (!typeInfo(Derived::classType()).subclassOf(base->type()))
    {
        return nullptr;
    }
    return static_cast<const Derived*>(base);
}

} // namespace Reef

#endif // !REEF_CORE_BASECLASS_HPP
