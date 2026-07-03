#include <Engine/Core/MaterialFunctionImpl.hpp>


using namespace Reef;


std::unique_ptr<MaterialFunction>
MaterialFunction::create()
{
	return std::make_unique<MaterialFunctionImpl>();
}


void
MaterialFunctionImpl::setWorldPosition(const csl::float3& worldPosition)
{
	mWorldPosition = worldPosition;
	markOutdated();
}


void
MaterialFunctionImpl::setWorldNormal(const csl::float3& worldNormal)
{
	mWorldNormal = worldNormal;
	markOutdated();
}


void
MaterialFunctionImpl::setBaseColor(const csl::float3& baseColor)
{
	mBaseColor = baseColor;
	markOutdated();
}


void
MaterialFunctionImpl::setOpacity(const csl::Float& opacity)
{
	mOpacity = opacity;
	markOutdated();
}


void
MaterialFunctionImpl::setMask(const csl::Bool& mask)
{
	mMask = mask;
	markOutdated();
}


const csl::float3* 
MaterialFunctionImpl::worldPosition() const
{
	return mWorldPosition.transform([](const auto& v) { return &v; }).value_or(nullptr);
} 


const csl::float3*
MaterialFunctionImpl::worldNormal() const
{
	return mWorldNormal.transform([](const auto& v) { return &v; }).value_or(nullptr);
}


const csl::float3*
MaterialFunctionImpl::baseColor() const
{
	return mBaseColor.transform([](const auto& v) { return &v; }).value_or(nullptr);
}


const csl::Float*
MaterialFunctionImpl::opacity() const
{
	return mOpacity.transform([](const auto& v) { return &v; }).value_or(nullptr);
}


const csl::Bool*
MaterialFunctionImpl::mask() const
{
	return mMask.transform([](const auto& v) { return &v; }).value_or(nullptr);
}

