#ifndef REEF_CORE_TEXTURE_HPP
#define REEF_CORE_TEXTURE_HPP

#include <Reef/Export.hpp>

#include <string>
#include <vector>
#include <span>
#include <memory>

namespace Reef
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

class REEF_API Texture
{
public:

    std::shared_ptr<Texture> create(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data = {});

	virtual ~Texture() = default;

	virtual bool set(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data = {}) = 0;

	virtual void setName(std::string_view name) = 0;

	virtual const std::string& name() const = 0;

    virtual TextureFormat format() const = 0;

    virtual uint32_t width() const = 0;

    virtual uint32_t height() const = 0;

    virtual std::span<const std::byte> pixelData() const = 0;

    virtual Tiling tiling() const = 0;

    virtual void setTiling(Tiling tiling) = 0;

    virtual Filter filter() const = 0;

    virtual void setFilter(Filter filter) = 0;

    virtual bool hasMipmaps() const = 0;

    virtual void setMipmaps(bool hasMipmaps) = 0;

}; // class Texture

} // namespace Reef

#endif // !REEF_CORE_TEXTURE_HPP