#include <Reef/Core/Object.hpp>

#include <uuid.h>

using namespace Reef;

Object::Object()
{
    auto uuid = uuids::uuid_system_generator()();
    mId       = std::hash<uuids::uuid>()(uuid);
}


uint64_t
Object::id() const
{
    return mId;
}
