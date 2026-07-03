#include <Common/ImageIO.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>
#include <string>

namespace
{

std::optional<Reef::Util::Image::PixelFormat>
convert(int c, int depth)
{
 using PixelFormat = Reef::Util::Image::PixelFormat;
    switch (c)
    {
        case 1:
            switch (depth)
            {
                case 1: return PixelFormat::R_8;
                case 2: return PixelFormat::R_16;
                case 4: return PixelFormat::R_32F;
                default: return {};
            }
            break;
        case 2:
            switch (depth)
            {
                case 1: return PixelFormat::RG_8;
                case 2: return PixelFormat::RG_16;
                default: return {};
    }
        case 3:
        {
            switch (depth)
            {
                case 1: return PixelFormat::RGB_8;
                case 2: return PixelFormat::RGB_16;
                default: return {};
            }
    }

        case 4:
        {
            switch (depth)
            {
                case 1: return PixelFormat::RGBA_8;
                case 2: return PixelFormat::RGBA_16;
                case 4: return PixelFormat::RGBA_32F;
                default: return {};
            }
    }
        default: return {};
    }
}

} // namespace

template<typename T>
struct Deleter
{
    void operator()(T* data) const
    {
        stbi_image_free(data);
    }
};

namespace Reef::Util
{

std::optional<Image>
loadImage(const std::filesystem::path& path)
{
    std::fstream file(path, std::ios::binary | std::ios::ate);
    if (!file)
    {
        return std::nullopt;
    }

    std::vector<char> buffer(file.tellg());
    file.seekg(0);
    file.read(buffer.data(), buffer.size());

    return loadImage(std::as_bytes(std::span{ buffer }));
}

std::optional<Image>
loadImage(std::span<const std::byte> memory)
{
    auto buffer = reinterpret_cast<const stbi_uc*>(memory.data());
    auto len    = static_cast<int>(memory.size());

    int x, y, c;
    std::unique_ptr<stbi_uc, Deleter<stbi_uc>> data(stbi_load_from_memory(buffer, len, &x, &y, &c, 0));

    if (data)
    {
        std::span<const std::byte> pixels(reinterpret_cast<const std::byte*>(data.get()), static_cast<size_t>(x * y * c));

        auto pixelFormat = convert(c, 1);
        if (!pixelFormat)
        {
            return std::nullopt;
        }

        std::optional<Image> result;

        result.emplace(static_cast<uint32_t>(x),
                       static_cast<uint32_t>(y),
                       *pixelFormat,
                       Image::Alignment::BYTE,
                       pixels);

        return result;
    }

    return std::nullopt;
}

} // namespace Reef
