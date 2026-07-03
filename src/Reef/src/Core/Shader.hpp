#ifndef ENGINE_CORE_MATERIALFUNCTIONIMPL_HPP
#define ENGINE_CORE_MATERIALFUNCTIONIMPL_HPP

#include <Engine/Core/MaterialFunction.hpp>

#include <Engine/Core/Resource.hpp>
#include <Engine/Core/SubclassOf.hpp>

#include <Coral/ShaderLanguage.hpp>

namespace Reef
{

class ENGINE_API MaterialFunctionImpl: public MaterialFunction,
	                                   public SubclassOf<MaterialFunctionImpl, Resource>
{

public:

	void setWorldPosition(const csl::float3& worldPosition) override;

	void setWorldNormal(const csl::float3& worldPosition) override;

	void setBaseColor(const csl::float3& baseColor) override;

	void setOpacity(const csl::Float& opacity) override;

	void setMask(const csl::Bool& mask) override;

	const csl::float3* worldPosition() const override;

	const csl::float3* worldNormal() const override;

	const csl::float3* baseColor() const override;

	const csl::Float* opacity() const override;

	const csl::Bool* mask() const override;

private:

	std::optional<csl::float3> mWorldPosition;

	std::optional<csl::float3> mWorldNormal;

	std::optional<csl::float3> mBaseColor;

	std::optional<csl::Float> mOpacity;

	std::optional<csl::Bool> mMask;
};

} // namespace Reef

#endif // !ENGINE_CORE_MATERIALFUNCTIONIMPL_HPP
