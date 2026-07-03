#include "TextureImpl.hpp"

#include <array>

using namespace Reef;

std::shared_ptr<Texture>
Texture::create(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data)
{
    auto texture = std::make_shared<TextureImpl>();
    //texture->setName(name);
    texture->set(width, height, format, data);
    return texture;
}


//std::shared_ptr<Texture> Texture::White = Texture::create(1u, 1u, TextureFormat::RGBA_8, std::array<std::byte, 4>{ (std::byte)255u, (std::byte)255u, (std::byte)255u, (std::byte)255u }, "1x1 White");
//
//
//std::shared_ptr<Texture> Texture::Black = Texture::create(1u, 1u, TextureFormat::RGBA_8, std::array<std::byte, 4>{ (std::byte)0u, (std::byte)0u, (std::byte)0u, (std::byte)0u }, "1x1 Black");
//
//
//std::shared_ptr<Texture> Texture::Normal = Texture::create(1u, 1u, TextureFormat::RGBA_8, std::array<std::byte, 3>{ (std::byte)128, (std::byte)128, (std::byte)255 }, "1x1 Normal");


bool
TextureImpl::set(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data)
{
    mWidth         = width;
    mHeight        = height;
    mTextureFormat = format;
    mPixelData.assign(data.begin(), data.end());

    //markOutdated();

    return true;
}


void
TextureImpl::setName(std::string_view name)
{
    mName = name;
}


const std::string&
TextureImpl::name() const
{
    return mName;
}


TextureFormat
TextureImpl::format() const  
{ 
    return mTextureFormat;
}


uint32_t
TextureImpl::width() const 
{ 
    return mWidth;
}


uint32_t
TextureImpl::height() const 
{ 
    return mHeight;
}


std::span<const std::byte>
TextureImpl::pixelData() const
{ 
    return mPixelData;
}


Tiling
TextureImpl::tiling() const
{ 
    return mTiling;
}


void
TextureImpl::setTiling(Tiling tiling)
{ 
    mTiling = tiling;
}


Filter 
TextureImpl::filter() const 
{ 
    return mFilter;
}


void
TextureImpl::setFilter(Filter filter)
{
    mFilter = filter;
}


bool
TextureImpl::hasMipmaps() const
{ 
    return mHasMips;
}


void
TextureImpl::setMipmaps(bool hasMipmaps)
{
    mHasMips = hasMipmaps;
}
