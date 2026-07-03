#include <Common/Texture.hpp>

#include <array>

using namespace Reef::Util;

namespace
{

TextureFormat
convert(Image::PixelFormat pixelFormat)
{
    switch (pixelFormat)
    {
        case Image::PixelFormat::R_8:      return TextureFormat::R_8;
        case Image::PixelFormat::RG_8:     return TextureFormat::RG_8;
        case Image::PixelFormat::RGB_8:    return TextureFormat::RGB_8;
        case Image::PixelFormat::RGBA_8:   return TextureFormat::RGBA_8; 
        case Image::PixelFormat::R_16:     return TextureFormat::R_16;
        case Image::PixelFormat::RG_16:    return TextureFormat::RG_16;
        case Image::PixelFormat::RGB_16:   return TextureFormat::RGB_16;
        case Image::PixelFormat::RGBA_16:  return TextureFormat::RGBA_16;
        case Image::PixelFormat::R_32F:    return TextureFormat::R_32F;
        case Image::PixelFormat::RGBA_32F: return TextureFormat::RGBA_32F;
        default: assert(false);   return TextureFormat::RGBA_8;
    }
}

} // namespace

Texture::Texture(uint32_t width, uint32_t height, TextureFormat format, Tiling tiling, Filter filter, bool generateMipmaps)
    : mWidth(width)
    , mHeight(height)
    , mFormat(format)
    , mTiling(tiling)
    , mFilter(filter)
    , mHasMips(generateMipmaps)
{
}


Texture::Texture(Image&& image, Tiling tiling, Filter filter, bool generateMipmaps)
    : mImage(std::move(image))
    , mWidth(mImage.width())
    , mHeight(mImage.height())
    , mFormat(convert(mImage.pixelFormat()))
    , mTiling(tiling)
    , mFilter(filter)
    , mHasMips(generateMipmaps)
{
}


Texture::Texture(const Image& image, Tiling tiling, Filter filter, bool generateMipmaps)
    : mImage(image)
    , mWidth(mImage.width())
    , mHeight(mImage.height())
    , mFormat(convert(mImage.pixelFormat()))
    , mTiling(tiling)
    , mFilter(filter)
    , mHasMips(generateMipmaps)
{
}

//std::shared_ptr<Texture> Texture::White = Texture::create(1u, 1u, TextureFormat::RGBA_8U, std::array<std::byte, 4>{ (std::byte)255u, (std::byte)255u, (std::byte)255u, (std::byte)255u }, "1x1 White");
//
//
//std::shared_ptr<Texture> Texture::Black = Texture::create(1u, 1u, TextureFormat::RGBA_8U, std::array<std::byte, 4>{ (std::byte)0u, (std::byte)0u, (std::byte)0u, (std::byte)0u }, "1x1 Black");
//
//
//std::shared_ptr<Texture> Texture::Normal = Texture::create(1u, 1u, TextureFormat::RGBA_8U, std::array<std::byte, 3>{ (std::byte)128, (std::byte)128, (std::byte)255 }, "1x1 Normal");


//bool
//Texture::set(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data)
//{
// mWidth   = width;
// mHeight  = height;
// mTextureFormat = format;
// mPixelData.assign(data.begin(), data.end());
//
// markOutdated();
//
// return true;
//}


TextureFormat
Texture::format() const  
{ 
    return mFormat;
}


uint32_t
Texture::width() const
{ 
    return mWidth;
}


uint32_t
Texture::height() const
{ 
    return mHeight;
}


//std::span<const std::byte>
//Texture::data() const
//{ 
// return mData;
//}


Tiling
Texture::tiling() const
{ 
    return mTiling;
}


void
Texture::setTiling(Tiling tiling)
{ 
    if (tiling != mTiling)
    {
        markOutdated();
    }

    mTiling = tiling;
}


Filter 
Texture::filter() const
{ 
    return mFilter;
}


void
Texture::setFilter(Filter filter)
{
    if (filter != mFilter)
    {
        markOutdated();
    }
    mFilter = filter;
}


bool
Texture::hasMipmaps() const
{ 
    return mHasMips;
}


void
Texture::setMipmaps(bool hasMipmaps)
{
    if (hasMipmaps != mHasMips)
    {
        markOutdated();
    }
    mHasMips = hasMipmaps;
}
