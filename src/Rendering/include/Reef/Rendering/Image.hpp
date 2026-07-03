#include <Common/System.hpp>

#include <Reef/Util/MemoryBlock.hpp>

#include <cassert>

#include <string>
#include <memory>
#include <span>
#include <vector>


namespace Reef::Util
{

class UTIL_API Image
{
public:

    /// The alignment requirements for the start of each pixel row in memory
    /**
     * Each pixel row must be a multiple of the alignment value
     */
    enum class Alignment
    {
        // 1-byte alignment (no padding)
        BYTE,
        // Rows aligned to even-numbered bytes (maximum 1 byte padding)
        TWO_BYTES,
        // Rows aligned to 4 bytes (maximum 3 bytes padding)
        FOUR_BYTES,    
        // Rows aligned to 8 bytes (maximum 7 bytes padding
        EIGHT_BYTES
    }; // enum class Alignment

    enum class PixelFormat
    {
        // Uncompressed single channel (8-bit per channel)
        R_8,
        // Uncompressed two channels (8-bit per channel)
        RG_8,
        // Uncompressed three channels (8-bit per channel)
        RGB_8,
        // Uncompressed four channels (8-bit per channel)
        RGBA_8,

        // Uncompressed single channel (16-bit per channel)
        R_16,
        // Uncompressed two channels (16-bit per channel)
        RG_16,
        // Uncompressed three channels (16-bit per channel)
        RGB_16,
        // Uncompressed four channels (16-bit per channel)
        RGBA_16,

        // Uncompressed single channel floating point (32-bit per channel)
        R_32F,
        // Uncompressed single channel floating point (32-bit per channel)
        RGBA_32F,
    }; // enum class PixelFormat

    Image();

    Image(uint32_t width, uint32_t height, PixelFormat format);

    Image(uint32_t width, uint32_t height, PixelFormat format, Alignment alignment);

    Image(uint32_t width, uint32_t height, PixelFormat format, Alignment alignment, std::span<const std::byte> data);

    /// The width of the image (in pixel)
    uint32_t width() const;

    /// The height of the image (in pixel)
    uint32_t height() const;

    /// The stride of one row (in bytes)
    uint32_t rowStride() const;

    /// The alignment of one row
    Alignment alignment() const;

    /// The pixel format of the image
    PixelFormat pixelFormat() const;

    /// The buffer pointing to the first pixel in the image
    std::span<const std::byte> data() const;

    /// The buffer pointing to the first pixel in the image
    std::span<std::byte> data();

    /// Get the pointer to the pixel at the position (x, y)
    const std::byte* at(uint32_t x, uint32_t y) const;

    /// Get the pointer to the pixel at the position (x, y)
    std::byte* at(uint32_t x, uint32_t y);

    /// Get the pointer to the pixel at the position (x, y)
    const std::byte* operator()(uint32_t x, uint32_t y) const;

    /// Get the pointer to the pixel at the position (x, y)
    std::byte* operator()(uint32_t x, uint32_t y);

private:

    uint32_t mWidth;

    uint32_t mHeight;

    Alignment mAlignment;

    PixelFormat mPixelFormat;

    MemoryBlock mStorage;
};


constexpr inline uint32_t sizeInBytes(Image::PixelFormat format)
{
    switch (format)
    {
        case Image::PixelFormat::R_8:   return 1;
        case Image::PixelFormat::RG_8:  return 2;
        case Image::PixelFormat::RGB_8: return 3;
        case Image::PixelFormat::RGBA_8:   return 4;
        case Image::PixelFormat::R_16:  return 2;
        case Image::PixelFormat::RG_16: return 4;
        case Image::PixelFormat::RGB_16:   return 6;
        case Image::PixelFormat::RGBA_16:  return 8;
        case Image::PixelFormat::R_32F:     return 4;
        case Image::PixelFormat::RGBA_32F: return 16;
    }
    assert(false);
    return 1;
}

} // namespace Reef
