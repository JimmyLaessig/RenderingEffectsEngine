#ifndef REEF_UTIL_TYPENAME_HPP
#define REEF_UTIL_TYPENAME_HPP

#include <Reef/Util/Export.hpp>
#include <string_view>
#include <string>

namespace Reef::Util
{

namespace Detail
{

template<typename T>
struct TypeNameImpl
{
    constexpr std::string_view operator()()
    {
#ifdef  _MSC_VER
        // MSVC predefines the '__FUNCSIG__' preprocessor definition, which, for the templated
        // function, contains the name of the template argument.

        constexpr std::string_view functionName{ __FUNCSIG__ };
        constexpr std::string_view prefix{ "Detail::TypeNameImpl<" };
        constexpr std::string_view suffix{ ">::operator ()(void)" };

        constexpr auto left = functionName.find(prefix) + prefix.size();
        constexpr auto right = functionName.rfind(suffix);

        static_assert(left < right);

        constexpr auto name = functionName.substr(left, right - left);

        constexpr std::string_view classPrefix{ "class " };
        if (name.starts_with(classPrefix))
        {
            return name.substr(classPrefix.size());
        }

        constexpr std::string_view structPrefix{ "struct " };
        if (name.starts_with(structPrefix))
        {
            return name.substr(structPrefix.size());
        }

        return name;

#else //  _MSC_VER
        static_assert(false && "Unsupported compiler");
#endif
    }
};


template<>
struct TypeNameImpl<std::string>
{
    constexpr std::string_view operator()()
    {
        return "std::string";
    }
};


template<template<typename, typename...> class T, typename U, typename... Rest>
struct TypeNameImpl<T<U, Rest...>>
{
    constexpr std::string_view operator()()
    {
        static_assert(false && "templated types are not supported");
        return "";
    }
};

} // namespace Detail

/*!
 * \brief Get the name of the type T
 * \note Templated types are not supported. 
 * \note This function does not work for aliased types and will return the non-aliased type name
 *       instead.
 * \tparam T The type for which to get the name
 * \return String view containing the name of the type. The string is valid for the entire duration
 *         of the program.
 */
template<typename T>
constexpr std::string_view typeName()
{
    return Detail::TypeNameImpl<T>()();
}

} // namespace Reef

#endif // !REEF_UTIL_TYPENAME_HPP