#include "MaterialImpl.hpp"

#include <Reef/Util/Visitor.hpp>

#include <string>

using namespace Reef;


std::unique_ptr<Material>
Material::create()
{
	return std::make_unique<MaterialImpl>();
}


void
MaterialImpl::setName(std::string_view name)
{
	mName = name;
}


const std::string&
MaterialImpl::name() const
{
	return mName;
}


//void
//MaterialImpl::setMaterialFunction(std::shared_ptr<MaterialFunction> materialFunction)
//{
//	mMaterialFunction = materialFunction;
//	markOutdated();
//}
//
//
//std::shared_ptr<MaterialFunction>
//MaterialImpl::materialFunction()
//{
//	return mMaterialFunction;
//}
//
//
//std::shared_ptr<const MaterialFunction>
//MaterialImpl::materialFunction() const
//{
//	return mMaterialFunction;
//}


bool
MaterialImpl::setParameter(std::string_view name, float value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::vec2& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::vec3& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::vec4& value)
{
	return setParameterImpl(name, value);
}

bool
MaterialImpl::setParameter(std::string_view name, int value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::ivec2& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::ivec3& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::ivec4& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::mat3& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, const glm::mat4& value)
{
	return setParameterImpl(name, value);
}


bool
MaterialImpl::setParameter(std::string_view name, std::shared_ptr<Texture> value)
{
	return setParameterImpl(name, value);
}


std::optional<MaterialImpl::ParameterValue>
MaterialImpl::getParameter(std::string_view name) const
{
	auto iter = mParameters.find(name);
	if (iter == mParameters.end())
	{
		return {};
	}

	return iter->second;
}


std::shared_ptr<Reef::Texture>
MaterialImpl::getTextureParameter(std::string_view name) const
{
	//if (auto parameter = getParameter(name))
	//{
	//	return visit(*parameter, Visitor
	//	{
	//		[](std::shared_ptr<Reef::Texture> tex) { return tex; },
	//		[](auto) -> std::shared_ptr<Reef::Texture> { return nullptr; },
	//	});
	//}

	return nullptr;
}


bool
MaterialImpl::setParameterImpl(std::string_view name, MaterialImpl::ParameterValue value)
{
	mParameters[std::string{ name }] = value;
	/*auto iter = mParameters.find(name);

	if (iter == mParameters.end())
	{
		return false;
	}

	if (iter->second.index() != value.index())
	{
		return false;
	}

	iter->second = value;*/

	//markOutdated();
	return true;
}
