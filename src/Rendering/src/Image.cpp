#include <Common/Image.hpp>

#include <cassert>
#include <cmath>
#include <vector>
#include <memory>

using namespace Reef::Util;

namespace
{

uint32_t
alignmentInBytes(Image::Alignment alignment)
{
    switch (alignment)
    {
        case Image::Alignment::BYTE:        return 1;
        case Image::Alignment::TWO_BYTES:    return 2;
        case Image::Alignment::FOUR_BYTES:    return 4;
        case Image::Alignment::EIGHT_BYTES:    return 8;
    }

    assert(false);
    return 1;
}


uint32_t
nextMultipleOf(uint32_t value, uint32_t alignment)
{
    return ((value + alignment - 1) / alignment) * alignment;
}

} // namespace

Image::Image()
    : Image(0, 0, Image::PixelFormat::RGBA_8)
{
}


Image::Image(uint32_t width, uint32_t height, Image::PixelFormat pixelFormat)
    : Image(width, height, pixelFormat, Image::Alignment::BYTE)
{
}


Image::Image(uint32_t width, uint32_t height, PixelFormat format, Alignment alignment)
    : mWidth(width)
    , mHeight(height)
    , mPixelFormat(format)
    , mAlignment(alignment)
{
    auto bufferSize = rowStride() * height;
    mData.resize(bufferSize, std::byte{ 0 });
}


Image::Image(uint32_t width, uint32_t height, Image::PixelFormat pixelFormat, Image::Alignment alignment, std::span<const std::byte> data)
    : mWidth(width)
    , mHeight(height)
    , mPixelFormat(pixelFormat)
    , mAlignment(alignment)
    , mData(data.begin(), data.end())
{
 auto expectedBufferSize = rowStride() * mHeight;

 assert(mData.size() == expectedBufferSize);
}


uint32_t
Image::width() const 
{
    return mWidth;
}


uint32_t 
Image::height() const 
{
    return mHeight; 
}


uint32_t
Image::rowStride() const
{
    return nextMultipleOf(mWidth * sizeInBytes(mPixelFormat), alignmentInBytes(mAlignment));
}


Image::Alignment 
Image::alignment() const
{
    return mAlignment; 
}


Image::PixelFormat 
Image::pixelFormat() const 
{
    return mPixelFormat; 
}


std::span<const std::byte>
Image::data() const
{ 
    return mData;
}


std::span<std::byte>
Image::data()
{
    return mData;
}


const std::byte*
Image::at(uint32_t x, uint32_t y) const
{
    return mData.data() + y * rowStride() + x * sizeInBytes(mPixelFormat);
}


std::byte*
Image::at(uint32_t x, uint32_t y)
{
    return mData.data() + y * rowStride() + x * sizeInBytes(mPixelFormat);
}


const std::byte*
Image::operator()(uint32_t x, uint32_t y) const
{
    return at(x, y);
}


std::byte*
Image::operator()(uint32_t x, uint32_t y)
{
    return at(x, y);
}
