#include <Reef/Rendering/IndexBuffer.hpp>

#include <Reef/Util/Visitor.hpp>

using namespace Reef::Rendering;

IndexBuffer::IndexBuffer(IndexFormat format, size_t capacity)
{
    switch (format)
    {
        case IndexFormat::UNSIGNED_SHORT:
            mIndices.emplace<std::vector<uint16_t>>();
            break;
        case IndexFormat::UNSIGNED_INT:
            mIndices.emplace<std::vector<uint32_t>>();
            break;
    }
    reserve(capacity);
}


void
IndexBuffer::append(std::span<uint32_t> indices)
{
    auto newIndexCount = size() + indices.size();
    Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](std::vector<uint32_t>& indexBuffer)
        {
            indexBuffer.append_range(indices);
        },
        [&](const std::vector<uint16_t>& indexBuffer)
        {
            std::vector<uint32_t> indices32;
            indices32.reserve(newIndexCount);
            indices32.append_range(indexBuffer);
            indices32.append_range(indices);
            mIndices = std::move(indices32);
        }
    });
}


void
IndexBuffer::append(std::span<uint16_t> indices)
{
    Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](auto& indexBuffer)
        {
            indexBuffer.append_range(indices);
        }
    });
}


void
IndexBuffer::reserve(size_t count)
{
    Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](auto& indices)
        {
            indices.reserve(count);
        }
    });
}


IndexFormat
IndexBuffer::format() const
{
    return Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](const std::vector<uint16_t>&)
        {
            return IndexFormat::UNSIGNED_SHORT;
        },
        [&](const std::vector<uint32_t>&)
        {
            return IndexFormat::UNSIGNED_INT;
        }
    });
}


size_t
IndexBuffer::size() const
{
    return Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](const auto& indices)
        {
            return indices.size(); 
        }
    });
}


size_t 
IndexBuffer::byteSize() const
{
    return data().size();
}


std::span<const std::byte>
IndexBuffer::data() const
{
    return Reef::Util::visit(mIndices, Reef::Util::Visitor{
        [&](const auto& indices)
        {
            return std::as_bytes(std::span(indices));
        }
    });
}
