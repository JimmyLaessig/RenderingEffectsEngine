#ifndef REEF_CORE_MATERIALIMPL_HPP
#define REEF_CORE_MATERIALIMPL_HPP

#include <Reef/Core/Material.hpp>

//#include <Reef/Core/Resource.hpp>
#include <Reef/Util/StringMap.hpp>

namespace Reef
{

class  MaterialImpl : public Material
	                  //public Reef::SubclassOf<MaterialImpl, Resource>
{
public:

	const std::string& name() const override;

	void setName(std::string_view name) override;

	//void setMaterialFunction(std::shared_ptr<MaterialFunction> materialFunction) override;

	//std::shared_ptr<MaterialFunction> materialFunction() override;

	//std::shared_ptr<const MaterialFunction> materialFunction() const override;

	bool setParameter(std::string_view name, float value) override;

	bool setParameter(std::string_view name, const glm::vec2& value) override;

	bool setParameter(std::string_view name, const glm::vec3& value) override;

	bool setParameter(std::string_view name, const glm::vec4& value) override;

	bool setParameter(std::string_view name, int value) override;

	bool setParameter(std::string_view name, const glm::ivec2& value) override;

	bool setParameter(std::string_view name, const glm::ivec3& value) override;

	bool setParameter(std::string_view name, const glm::ivec4& value) override;

	bool setParameter(std::string_view name, const glm::mat3& value) override;

	bool setParameter(std::string_view name, const glm::mat4& value) override;

	bool setParameter(std::string_view name, std::shared_ptr<Reef::Texture> texture) override;

	std::optional<ParameterValue> getParameter(std::string_view name) const override;

	std::shared_ptr<Reef::Texture> getTextureParameter(std::string_view name) const override;

private:

	bool setParameterImpl(std::string_view name, ParameterValue value);

	Reef::Util::UnorderedStringMap<ParameterValue> mParameters;

	//std::shared_ptr<MaterialFunction> mMaterialFunction;

	std::string mName;

}; // class MaterialImpl

} // namespace Reef

#endif // !REEF_CORE_MATERIALIMPL_HPP