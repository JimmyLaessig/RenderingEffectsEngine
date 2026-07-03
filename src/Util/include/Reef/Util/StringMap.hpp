#ifndef REEF_CORE_STRINGMAP_HPP
#define REEF_CORE_STRINGMAP_HPP

#include <string>
#include <string_view>
#include <unordered_map>

namespace Reef::Util
{

struct StringHash
{
    using is_transparent = void;
    [[nodiscard]] size_t operator()(const char* txt) const
    {
        return std::hash<std::string_view>{}(txt);
    }


    [[nodiscard]] size_t operator()(std::string_view txt) const
    {
        return std::hash<std::string_view>{}(txt);
    }


    [[nodiscard]] size_t operator()(const std::string& txt) const
    {
        return std::hash<std::string>{}(txt);
    }
};

template<typename Value>
using UnorderedStringMap = std::unordered_map<std::string, Value, StringHash, std::equal_to<>>;

} // namespace Reef

#endif // !REEF_CORE_STRINGMAP_HPP
