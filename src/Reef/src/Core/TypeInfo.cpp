/*
 * Copyright 2025 Bernhard Rainer.
 *
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Reef/Core/TypeInfo.hpp>

#include <Reef/Util/CRC32.hpp>
#include <Reef/Util/Singleton.hpp>

#include <stdexcept>
#include <unordered_map>

namespace
{

/*!
 * \brief Implementation of the TypeInfo interface
 */
class TypeInfoImpl : public Reef::TypeInfo
{
public:

    TypeInfoImpl(std::string_view name, 
                 Reef::TypeId id, 
                 size_t byteSize, 
                 std::unique_ptr<Reef::TypeFactory>&& factory, 
                 const TypeInfoImpl* parent)
        : mName(name)
        , mId(id)
        , mSize(byteSize)
        , mParent(parent)
        , mFactory(std::move(factory))
    {}

    std::string_view name() const override
    {
        return mName;
    }

    Reef::TypeId id() const override
    {
        return mId;
    }

    size_t size() const override
    {
        return mSize;
    }

    bool subclassOf(Reef::TypeId other) const override
    {
        for (auto current = this; current; current = current->mParent)
        {
            if (current->id() == other)
            {
                return true;
            }
        }

        return false;
    }

    Reef::TypeFactory* factory() const override
    {
        return mFactory.get();
    }

private:

    std::string mName;
    Reef::TypeId mId;
    size_t mSize;
    const TypeInfoImpl* mParent;
    std::unique_ptr<Reef::TypeFactory> mFactory;
};

/*!
 * \brief Implementation of the TypeRegistry interface
 */
class TypeRegistry : public Reef::Util::Singleton<TypeRegistry>
{
public:

    Reef::TypeId registerType(std::string_view name,
                              Reef::TypeId id,
                              size_t byteSize, 
                              std::unique_ptr<Reef::TypeFactory>&& factory,
                              Reef::TypeId parentTypeId)
    {
        if (mRegisteredTypes.find(id) != mRegisteredTypes.end())
        {
            throw std::runtime_error("Type already registered");
        }

        const TypeInfoImpl* parentTypeInfo = nullptr;
        if (parentTypeId != Reef::INVALID_TYPE_ID)
        {
            auto iter = mRegisteredTypes.find(parentTypeId);
            if (iter == mRegisteredTypes.end())
            {
                id = Reef::INVALID_TYPE_ID;
                throw std::runtime_error("Parent type not registered");
            }
           
            parentTypeInfo = &iter->second;
        }

        mRegisteredTypes.emplace(id, TypeInfoImpl(name, id, byteSize, std::move(factory), parentTypeInfo));

        return id;
    }

    const Reef::TypeInfo& typeInfo(Reef::TypeId id) const
    {
        auto iter = mRegisteredTypes.find(id);
        if (iter == mRegisteredTypes.end())
        {
            throw std::runtime_error("Type not registered");
        }
        return iter->second;
    }

private:

    std::unordered_map<Reef::TypeId, TypeInfoImpl> mRegisteredTypes;

}; // TypeRegistry

} // namespace

namespace Reef
{

TypeId
registerType(std::string_view name, size_t byteSize, std::unique_ptr<TypeFactory>&& factory, TypeId parentTypeId)
{
    auto id = Reef::Util::crc32(name);
    return TypeRegistry::instance().registerType(name, id, byteSize, std::move(factory), parentTypeId);
}


const TypeInfo&
typeInfo(TypeId id)
{
    return TypeRegistry::instance().typeInfo(id);
}

} // namespace Reef
