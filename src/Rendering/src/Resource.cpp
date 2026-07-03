#include <Reef/Rendering/Resource.hpp>

using namespace Reef::Rendering;

Resource::Resource()
{
    static uint64_t sIdCounter = 0;
    mId = sIdCounter++;
}


uint64_t
Resource::id() const
{
    return mId;
}


void
Resource::setName(std::string_view name)
{
    mName = name;
}


const std::string&
Resource::name() const
{
    return mName;
}


size_t
Resource::version() const
{
    mVersion += mOutdated;
    mOutdated = false;
    return mVersion;
}


void
Resource::markOutdated()
{
    mOutdated = true;
}


std::scoped_lock<std::mutex>
Resource::lock() const
{
    return std::scoped_lock<std::mutex>(mResourceProtection);
}


std::unique_lock<std::mutex>
Resource::tryLock() const
{
    return std::unique_lock<std::mutex>(mResourceProtection, std::try_to_lock);
}
