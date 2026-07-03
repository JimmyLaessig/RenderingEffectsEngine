#ifndef REEF_UTIL_TEXTURE_HPP
#define REEF_UTIL_TEXTURE_HPP

#include <Common/Resource.hpp>

#include <Common/Image.hpp>

#include <Common/TextureFormat.hpp>

#include <span>

#include <cstdint>

namespace Reef::Util
{

enum class Tiling
{
    WRAP,
    CLAMP_TO_EDGE,
    MIRROR,
};


enum class Filter
{
    NEAREST,
    LINEAR,
    TRILINAR,
};


class Texture : public Resource
{
public:

    Texture(uint32_t width, uint32_t height, TextureFormat format, Tiling tiling, Filter filter, bool generateMipmaps);

    Texture(Image&& image, Tiling tiling, Filter filter, bool generateMipmaps);

    Texture(const Image& image, Tiling tiling, Filter filter, bool generateMipmaps);

    TextureFormat format() const;

    uint32_t width() const;

    uint32_t height() const;

    std::span<const std::byte> data() const;

    Tiling tiling() const;

    void setTiling(Tiling tiling);

    Filter filter() const;

    void setFilter(Filter filter);

    bool hasMipmaps() const;

    void setMipmaps(bool hasMipmaps);

private:

    Reef::Util::Image mImage;

    uint32_t mWidth{ 0 };

    uint32_t mHeight{ 0 };

    TextureFormat mFormat{ TextureFormat::RGBA_8 };

    Tiling mTiling{ Tiling::WRAP };

    Filter mFilter{ Filter::TRILINAR };

    bool mHasMips{ true };

}; // class Texture

} // namespace Reef::Util

#endif // !REEF_UTIL_TEXTURE_HPP
