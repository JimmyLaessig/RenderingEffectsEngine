#ifndef ENGINE_CORE_TEXTUREFORMAT_HPP
#define ENGINE_CORE_TEXTUREFORMAT_HPP

#include <cassert>
#include <cstdint>

namespace Reef::Util
{

enum class TextureFormat
{
    R_8,
    RG_8,
    RGB_8,
    RGBA_8,

    R_16,
    RG_16,
    RGB_16,
    RGBA_16,

    R_32F,
    RGBA_32F,

    DEPTH_16,
    DEPTH_32,
    DEPTH_24_STENCIL_8,
};


constexpr uint32_t
sizeInBytes(TextureFormat format)
{
    switch (format)
    {
        case TextureFormat::R_8:                return 1;
        case TextureFormat::RG_8:               return 2;
        case TextureFormat::RGB_8:              return 3;
        case TextureFormat::RGBA_8:             return 4;
            
        case TextureFormat::R_16:               return 2;
        case TextureFormat::RG_16:              return 4;
        case TextureFormat::RGB_16:             return 6;
        case TextureFormat::RGBA_16:            return 8;

        case TextureFormat::R_32F:              return 4;
        case TextureFormat::RGBA_32F:           return 16;

        case TextureFormat::DEPTH_16:           return 2;
        case TextureFormat::DEPTH_24_STENCIL_8: return 4;
        case TextureFormat::DEPTH_32:           return 4;
    }

    assert(false);
    return 0;
}

} // namespace Reef

#endif // !ENGINE_CORE_TEXTUREFORMAT_HPP
