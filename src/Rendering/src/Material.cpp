#include <Common/Material.hpp>

#include <Common/Visitor.hpp>

#include <string>

using namespace Reef::Util;


//void
//Material::setMaterialFunction(std::shared_ptr<MaterialFunction> materialFunction)
//{
// mMaterialFunction = materialFunction;
// markOutdated();
//}
//
//
//std::shared_ptr<MaterialFunction>
//Material::materialFunction()
//{
// return mMaterialFunction;
//}
//
//
//std::shared_ptr<const MaterialFunction>
//Material::materialFunction() const
//{
// return mMaterialFunction;
//}


bool
Material::setParameter(std::string_view name, float value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::vec2& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::vec3& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::vec4& value)
{
    return setParameterImpl(name, value);
}

bool
Material::setParameter(std::string_view name, int value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::ivec2& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::ivec3& value)
{
 return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::ivec4& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::mat3& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, const glm::mat4& value)
{
    return setParameterImpl(name, value);
}


bool
Material::setParameter(std::string_view name, std::shared_ptr<Texture> value)
{
    return setParameterImpl(name, value);
}


std::optional<Material::ParameterValue>
Material::getParameter(std::string_view name) const
{
    auto iter = mParameters.find(name);
    if (iter == mParameters.end())
    {
        return {};
    }

    return iter->second;
}


std::shared_ptr<Texture>
Material::getTextureParameter(std::string_view name) const
{
    if (auto parameter = getParameter(name))
    {
        return visit(*parameter, Visitor
        {
            [](std::shared_ptr<Texture> tex) { return tex; },
            [](auto) -> std::shared_ptr<Texture> { return nullptr; },
        });
    }

    return nullptr;
}


bool
Material::setParameterImpl(std::string_view name, Material::ParameterValue value)
{
    auto iter = mParameters.find(name);
    if (iter == mParameters.end())
    {
        return false;
    }

    if (iter->second.index() != value.index())
    {
        // TODO: Log warning here
    }

    iter->second = value;

    markOutdated();
    return true;
}
