#ifndef REEF_UTIL_HIVE_HPP
#define REEF_UTIL_HIVE_HPP

#include <Reef/Util/Export.hpp>
#include <Reef/Util/MemoryBlock.hpp>

#include <memory>
#include <optional>
#include <set>
#include <list>
#include <ranges>

namespace Reef::Util
{

/*!
 * \brief 
 */
template<typename BaseClass>
class Hive
{
public:

    /*!
     * \brief Factory interface to create an object 
     */
    class Factory
    {
    public:

        /*!
         * \brief Get the size of an object created by this factory.
         * \return Returns the size in bytes
         */
        virtual size_t objectSize() const = 0;

        /*!
         * \brief Construct a new object at the given address
         * \param address The memory address of the object
         */
        virtual void constructAt(void* address) = 0;

    }; // class Factory

    /*!
     * \brief Construct a new Hive with the provided factory
     * \param factory A unique pointer to the factory that will be used to create objects of the
     *        provided type.
     */
    Hive(std::unique_ptr<Factory>&& factory);

    /*!
     * \brief Create a new instance of the provided type
     * \return A pointer to the created object
     */
    BaseClass* emplace();

    /*!
     * \brief Delete the objects from the hive and free the memory for future use
     * \param A pointer to the object to erase
     */
    void erase(BaseClass* obj);

    /*!
     *
     * \return true if the hive is empty, false otherwise
     */
    bool empty() const;

    /*!
     * \return The number of objects currently stored in the hive
     */
    size_t size() const;

    /*!
     * \return The distance between the start of two consecutive objects
     */
    size_t stride() const;

    struct Block;

    struct Iterator
    {
        using BlockIterator = typename std::list<Block>::iterator;
        using IndexIterator = typename std::set<size_t>::iterator;

        Iterator() = default;

        Iterator(BlockIterator b, IndexIterator i, Hive* h);

        BaseClass* operator*() const;

        Iterator& operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

        BlockIterator mBlockIterator;
        IndexIterator mIndexIterator;
        Hive* mHive{ nullptr };
    };

    Iterator begin();

    Iterator end();

private:

    /*!
     *
     */
    struct Block
    {
        /*!
         * \brief Create a new block
         * \param capacity The number of objects that can be stored in the block
         * \param hive The owning hive
         */
        Block(size_t capacity, Hive& hive);

        ~Block();

        /*!
         * \brief Try emplace a new object in the block
         * \return Returns the pointer to the construct object, or nullptr if the block is at
         *         capacity.
         */
        BaseClass* emplace();

        /*!
         * \brief Try destroy the object
         * \param obj The object to destroy
         * \return Returns true if the object belongs to this block and was destroyed, otherwise
         *         false.
         */
        bool erase(BaseClass* obj);

        /*!
         * \return True if the block is empty, false otherwise.
         */
        bool empty() const;

        /*!
         * \return The number of objects stored in the block.
         */
        size_t size() const;

        /*!
         * \return The total number of objects that can be stored in the block.
         */
        size_t capacity() const;

        /*!
         * \brief Unchecked access to the object at the given index
         * \param index The index of the object
         * \return Pointer to the object stored at the given index
         */
        BaseClass* at(size_t index);

        /*!
         * \brief Get the index of the object in the hive
         * \param obj The object for which to get the index
         * \return Returns the index of the object or std::nullopt if the object is not stored in
         *         this block.
         */
        std::optional<size_t> indexOf(const BaseClass* obj);

        // The owning hive
        Hive& mHive;

        // Data storage
        MemoryBlock<> mStorage;

        // Contain all non-occupied indices
        std::set<size_t> mFreeIndices;

        // Contain all occupied indices
        std::set<size_t> mOccupiedIndices;
    };

    std::unique_ptr<Factory> mFactory;

    std::list<Block> mBlocks;

    size_t mSize{ 0 };

    uint32_t mGrowFactor{ 2 };

    uint32_t mInitialBlockSize{ 2 };

}; // class Hive


template<typename BaseClass>
Hive<BaseClass>::Hive(std::unique_ptr<Hive::Factory>&& factory)
    : mFactory(std::move(factory))
{}


template<typename BaseClass>
BaseClass*
Hive<BaseClass>::emplace()
{
    // Find the first block with free indices
    for (auto& block : mBlocks)
    {
        if (auto obj = block.emplace())
        {
            mSize++;
            return obj;
        }
    }

    auto capacity = mBlocks.empty() ? 2 : mBlocks.back().capacity() * mGrowFactor;
    auto& block   = mBlocks.emplace_back(capacity, *this);

    if (auto obj = block.emplace())
    {
        mSize++;
        return obj;
    }

    return nullptr;
}


template<typename BaseClass>
void
Hive<BaseClass>::erase(BaseClass* obj)
{
    for (auto block = mBlocks.begin(); block != mBlocks.end(); ++block)
    {
        if (block->erase(obj))
        {
            mSize--;

            if (block->empty())
            {
                mBlocks.erase(block);
            }
            return;
        }
    }
}


template<typename BaseClass>
bool
Hive<BaseClass>::empty() const
{
    return size() == 0;
}


template<typename BaseClass>
size_t
Hive<BaseClass>::size() const
{
    return mSize;
}


template<typename BaseClass>
size_t
Hive<BaseClass>::stride() const
{
    return mFactory->objectSize();
}


template<typename BaseClass>
Hive<BaseClass>::Block::Block(size_t capacity, Hive& hive)
    : mHive(hive)
    , mStorage(capacity * mHive.stride(), std::byte(0))
{
    mFreeIndices.insert_range(std::views::iota(size_t(0), capacity));
}


template<typename BaseClass>
typename Hive<BaseClass>::Iterator
Hive<BaseClass>::begin()
{
    for (auto it = mBlocks.begin(); it != mBlocks.end(); ++it)
    {
        if (!it->mOccupiedIndices.empty())
        {
            return Iterator(it, it->mOccupiedIndices.begin(), this);
        }
    }

    return end();
}


template<typename BaseClass>
typename Hive<BaseClass>::Iterator
Hive<BaseClass>::end()
{
    return Iterator(mBlocks.end(), {}, this);
}


template<typename BaseClass>
Hive<BaseClass>::Block::~Block()
{
    for (auto index: mOccupiedIndices)
    {
        if (auto address = at(index))
        {
            std::destroy_at(address);
        }
    }
}


template<typename BaseClass>
BaseClass*
Hive<BaseClass>::Block::emplace()
{
    if (mFreeIndices.empty())
    {
        return nullptr;
    }
    auto index = *mFreeIndices.begin();
    auto idx   = mFreeIndices.extract(mFreeIndices.begin());
    mOccupiedIndices.insert(std::move(idx));

    auto obj = at(index);
    mHive.mFactory->constructAt(obj);
    return obj;
}


template<typename BaseClass>
bool
Hive<BaseClass>::Block::erase(BaseClass* obj)
{
    if (auto index = indexOf(obj))
    {
        std::destroy_at(obj);
        std::memset(obj, 0, mHive.stride());

        auto idx = mOccupiedIndices.extract(*index);
        mFreeIndices.insert(std::move(idx));
        return true;
    }

    return false;
}


template<typename BaseClass>
bool
Hive<BaseClass>::Block::empty() const
{
    return mOccupiedIndices.empty();
}


template<typename BaseClass>
size_t
Hive<BaseClass>::Block::size() const
{
    return mOccupiedIndices.size();
}


template<typename BaseClass>
size_t
Hive<BaseClass>::Block::capacity() const
{
    return mFreeIndices.size() + mOccupiedIndices.size();
}


template<typename BaseClass>
BaseClass*
Hive<BaseClass>::Block::at(size_t index)
{
    return reinterpret_cast<BaseClass*>(mStorage.data() + index * mHive.stride());
}


template<typename BaseClass>
std::optional<size_t>
Hive<BaseClass>::Block::indexOf(const BaseClass* instance)
{
    auto address = reinterpret_cast<const std::byte*>(instance);

    // Out of bounds
    if (address < mStorage.data())
    {
        return std::nullopt;
    }

    auto offset = address - mStorage.data();
    // Not a valid instance
    if (offset % mHive.stride() != 0)
    {
        return std::nullopt;
    }

    size_t index = offset / mHive.stride();
    // Out of bounds
    if (index >= capacity())
    {
        return std::nullopt;
    }
    return index;
}


template<typename BaseClass>
Hive<BaseClass>::Iterator::Iterator(BlockIterator b, IndexIterator i, Hive* h)
    : mBlockIterator(b)
    , mIndexIterator(i)
    , mHive(h)
{}


template<typename BaseClass>
BaseClass*
Hive<BaseClass>::Iterator::operator*() const
{
    return mBlockIterator->at(*mIndexIterator);
}


template<typename BaseClass>
Hive<BaseClass>::Iterator&
Hive<BaseClass>::Iterator::operator++()
{
    // Advance index inside current block
    ++mIndexIterator;

    // Easy case: We've not reached the end of the current block
    if (mIndexIterator != mBlockIterator->mOccupiedIndices.end())
    {
        return *this;
    }

    // We've reached the end of the current block so we go to the next block
    ++mBlockIterator;

    // Check if the next block is not empty. If so, set the index iterator to
    // the beginning of it's occupied list, otherwise advance to the next block
    for (;mBlockIterator != mHive->mBlocks.end(); ++mBlockIterator)
    {
        if (!mBlockIterator->mOccupiedIndices.empty())
        {
            mIndexIterator = mBlockIterator->mOccupiedIndices.begin();
            return *this;
        }
    }
 
    // If no empty block is found, return end
    *this = mHive->end();
    return *this;
}

template<typename BaseClass>
Hive<BaseClass>::Iterator
Hive<BaseClass>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}


template<typename BaseClass>
bool
Hive<BaseClass>::Iterator::operator==(const Hive<BaseClass>::Iterator& other) const
{
    return mHive == other.mHive &&
           mBlockIterator == other.mBlockIterator &&
           mIndexIterator == other.mIndexIterator;
}


template<typename BaseClass>
bool
Hive<BaseClass>::Iterator::operator!=(const Hive<BaseClass>::Iterator& other) const
{
    return !(*this == other);
}

} // namespace Reef

#endif // !REEF_CORE_HIVE_HPP
