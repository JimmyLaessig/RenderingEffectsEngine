#ifndef REEF_CORE_TEXTUREIMPL_HPP
#define REEF_CORE_TEXTUREIMPL_HPP

#include <Reef/Core/Texture.hpp>

#include <string>
#include <vector>

namespace Reef
{

class TextureImpl : public Texture
{
public:

    TextureImpl() = default;

    bool set(uint32_t width, uint32_t height, TextureFormat format, std::span<const std::byte> data = {}) override;

    void setName(std::string_view name) override;

    const std::string& name() const override;

    TextureFormat format() const override;

    uint32_t width() const override;

    uint32_t height() const override;

    std::span<const std::byte> pixelData() const override;

    Tiling tiling() const  override;

    void setTiling(Tiling tiling)  override;

    Filter filter() const  override;

    void setFilter(Filter filter)  override;

    bool hasMipmaps() const  override;

    void setMipmaps(bool hasMipmaps)  override;

private:

    std::string mName;

    TextureFormat mTextureFormat{ TextureFormat::RGBA_8 };

    uint32_t mWidth{ 0 };

    uint32_t mHeight{ 0 };

    std::vector<std::byte> mPixelData;

    Tiling mTiling{ Tiling::WRAP };

    Filter mFilter{ Filter::TRILINAR };

    bool mHasMips{ true };

}; // class TextureImpl

} // namespace Reef

#endif // !REEF_CORE_TEXTUREIMPL_HPP