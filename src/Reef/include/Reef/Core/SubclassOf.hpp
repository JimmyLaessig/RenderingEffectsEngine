#ifndef REEF_CORE_SUBCLASSOF_HPP
#define REEF_CORE_SUBCLASSOF_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/TypeInfo.hpp>

#include <concepts>
#include <memory>

namespace Reef
{

//template<typename Derived, typename Base>
//class SubclassOf;

/*!
 *
 */
template<typename Derived, typename Base>
class SubclassOf : public Base
{
public:

    /*!
     * \brief Get the type of the class
     */
    static TypeId classType()
    {
        static TypeId sTypeId = registerType<Derived>(Base::classType());
        return sTypeId;
    }

    /*!
     * \brief Get the type of the object
     */
    virtual TypeId type() const override
    {
        return classType();
    }

private:

    static inline const bool sTypeRegistered = classType() != INVALID_TYPE_ID;

}; // class SubclassOf

} // namespace Reef

#endif // !ENGINE_CORE_SUBCLASSOF_HPP
