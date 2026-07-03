#ifndef REEF_RENDERING_INDEXBUFFER_HPP
#define REEF_RENDERING_INDEXBUFFER_HPP

#include <Reef/Rendering/Export.hpp>

#include <span>
#include <vector>
#include <variant>

namespace Reef::Rendering
{

enum class IndexFormat
{
    // 16-bit unsigned integer index format
    UNSIGNED_SHORT,
    // 32-bit unsigned integer index format
    UNSIGNED_INT
};


class RENDERING_API IndexBuffer
{
public:
    IndexBuffer(IndexFormat format, size_t capacity);

    void append(std::span<uint32_t> indices);

    void append(std::span<uint16_t> indices);

    void reserve(size_t count);

    IndexFormat format() const;

    size_t size() const;

    size_t byteSize() const;

    std::span<const std::byte> data() const;

private:

    std::variant<std::vector<uint16_t>, std::vector<uint32_t>> mIndices;

}; // class IndexedGeometry

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_INDEXBUFFER_HPP
