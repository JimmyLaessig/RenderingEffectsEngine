/*
 * Copyright 2025 Bernhard Rainer.
 *
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REEF_CORE_TYPEINFO_HPP
#define REEF_CORE_TYPEINFO_HPP

#include <Reef/Export.hpp>

#include <Reef/Util/TypeName.hpp>

#include <memory>
#include <string_view>

namespace Reef
{

/*!
 * \brief Factory interface for constructing objects of a particular type
 */
class REEF_API TypeFactory
{
public:

    ~TypeFactory() = default;

    /*!
     * \brief Get the size of an object constructed by this factory
     * \return The size of an object of the particular type in bytes
     */
    virtual size_t objectSize() const = 0;

    /*!
     * \brief Default construct an object of the particular type
     * \param address The memory location to construct the object at
     */
    virtual void constructAt(void* address) = 0;

}; // class TypeFactory

/*!
 * \brief Unique identifier for a type registered with the type system
 */
using TypeId = uint64_t;

/*!
 * \brief Invalid TypeId value
 */
constexpr static TypeId INVALID_TYPE_ID = 0;

/*!
 * \brief Register the type
 * \param name The name of the type
 * \param byteSize The size of an object of type in bytes
 * \param factory The factory for constructing objects of the type or nullptr if the type is 
 *                abstract
 * \param parentTypeId The id of the parent type or INVALID_TYPE_ID if the type has no parent type
 * \return The id of the type
 * \throws Throws std::runtime_error if a type with the given name is already registered with the
 *         type system.
 */
TypeId REEF_API registerType(std::string_view name, size_t byteSize, 
                             std::unique_ptr<TypeFactory>&& factory, TypeId parentTypeId);

/*!
 * \brief Register the type
 * \tparam T The type to register
 * \param parentTypeId The id of the parent type
 * \return The id of the type
 * \throws Throws std::runtime_error if T is already registered with the type system.
 */
template<typename T>
TypeId registerType(TypeId parentTypeId)
{
    std::unique_ptr<TypeFactory> factory;
    if constexpr (!std::is_abstract_v<T>)
    {
        class TypeFactoryImpl final : public TypeFactory
        {
        public:

            size_t objectSize() const override
            {
                return sizeof(T);
            }

            void constructAt(void* address) override
            {
                std::construct_at(static_cast<T*>(address));
            }

        }; // class TypeFactoryImpl

        factory = std::make_unique<TypeFactoryImpl>();
    }

    return registerType(Reef::Util::typeName<T>(), sizeof(T), std::move(factory), parentTypeId);
}

/*!
 * \brief Register the type
 * \tparam T The type to register
 * \return The id of the type
 * \throws Throws std::runtime_error if T is already registered with the type system.
 */
template<typename T>
TypeId registerType()
{
    return registerType<T>(INVALID_TYPE_ID);
}

/*!
 * \brief Holds information about a type
 */
class REEF_API TypeInfo
{
public:

    virtual ~TypeInfo() = default;

    /*!
     * \brief Get the name of the type
     * \return String containing the name of the type. The string is valid for the entire duration
     *         of the program.
     */
    virtual std::string_view name() const = 0;

    /*!
     * \brief Get the unique identifier of the type
     * \return The unique identifier of the type
     */
    virtual TypeId id() const = 0;

    /*!
     * \brief Get the size of an object of this type
     * \brief The size of an object of this type in bytes
     */
    virtual size_t size() const = 0;

    /*!
     * \brief Check if this type is a subclass of the other type
     * \param other The id of the type to check against
     * \return True if this type is a subclass of the given type, false otherwise.
     */
    virtual bool subclassOf(TypeId other) const = 0;

    /*!
     * \brief Get the factory to construct objects of the given type
     * \return A pointer to the factory or nullptr if the type is abstract. The pointer is valid for
     *         the entire duration of the program
     */
    virtual TypeFactory* factory() const = 0;

}; // class TypeInfo

/*!
 * \brief Get the type info for the given id
 * \param id The id of the type
 * \return The TypeInfo object for the given id
 * \throws Throws std::runtime_error if no type with the given id is registered with the type
 *         system.
 */
const TypeInfo& REEF_API typeInfo(TypeId id);

} // namespace Reef

#endif // !REEF_CORE_TYPEINFO_HPP
