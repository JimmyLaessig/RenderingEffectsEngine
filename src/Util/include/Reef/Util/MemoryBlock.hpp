#ifndef REEF_UTIL_MEMORYBLOCK_HPP
#define REEF_UTIL_MEMORYBLOCK_HPP

#include <Reef/Util/Export.hpp>

#include <cstddef>
#include <memory>

namespace Reef::Util
{

/*!
 * Allocate a contiguous chunk of memory
 */
template<typename Allocator = std::allocator<std::byte>>
class UTIL_API MemoryBlock
{
public:

    explicit MemoryBlock(const Allocator& alloc = Allocator());

    explicit MemoryBlock(size_t byteSize, 
                         std::byte fillValue = std::byte(0), 
                         const Allocator& alloc = Allocator());

    ~MemoryBlock();

    /*!
     * \brief Get a pointer to the beginning of the underlying data
     */
    std::byte* data();

    /*!
     * \brief Get a pointer to the beginning of the underlying data
     */
    const std::byte* data() const;

    /*!
     * \brief Get the size of the memory block in bytes
     */
    size_t size() const;

    /*!
     * \brief Fill the memory with the given value
     * \param value The value to fill the memory with
     */
    void fill(std::byte value);

private:

    Allocator mAllocator;

    size_t mByteSize{ 0 };

    std::byte* mData{ nullptr };

}; // class MemoryBlock


template<typename Allocator>
MemoryBlock< Allocator>::MemoryBlock(const Allocator& alloc)
    : MemoryBlock(0, std::byte(0), alloc)
{
}


template<typename Allocator>
MemoryBlock<Allocator>::MemoryBlock(size_t byteSize, std::byte fillValue, const Allocator& alloc)
    : mAllocator(alloc)
    , mByteSize(byteSize)
{
    if (byteSize > 0)
    {
        mData = mAllocator.allocate(byteSize);
        fill(fillValue);
    }
}


template<typename Allocator>
MemoryBlock<Allocator>::~MemoryBlock()
{
    if (mData)
    {
        mAllocator.deallocate(mData, mByteSize);
    }
}


template<typename Allocator>
void
MemoryBlock<Allocator>::fill(std::byte value)
{
    std::memset(mData, static_cast<int>(value), mByteSize);
}


template<typename Allocator>
std::byte*
MemoryBlock<Allocator>::data()
{
    return mData;
}


template<typename Allocator>
const std::byte*
MemoryBlock<Allocator>::data() const
{
    return mData;
}


template<typename Allocator>
size_t
MemoryBlock<Allocator>::size() const
{
    return mByteSize;
}

} // namespace Reef

#endif // !ENGINE_CORE_MEMORYBLOCK_HPP
