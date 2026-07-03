#include <Common/Image.hpp>
#include <string>
#include <memory>
#include <span>
#include <optional>
#include <filesystem>

namespace Reef::Util
{

std::optional<Image> loadImage(const std::filesystem::path& path);

std::optional<Image> loadImage(std::span<const std::byte> data);

} // namespace Reef
