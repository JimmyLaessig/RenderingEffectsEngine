#ifndef REEF_MATERIAL_HPP
#define REEF_MATERIAL_HPP

#include <Reef/Export.hpp>

//#include <Engine/Core/MaterialFunction.hpp>
#include <Reef/Core/Texture.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace Reef
{

class REEF_API Material
{

public:

	static std::unique_ptr<Material> create();

	using ParameterValue = std::variant<float, glm::vec2, glm::vec3, glm::vec4,
										int, glm::ivec2, glm::ivec3, glm::ivec4,
										glm::mat3, glm::mat4,
										std::shared_ptr<Texture>>;

	virtual ~Material() = default;

	virtual void setName(std::string_view name) = 0;

	virtual const std::string& name() const = 0;

	//virtual void setMaterialFunction(std::shared_ptr<MaterialFunction> materialFunction) = 0;

	//virtual std::shared_ptr<MaterialFunction> materialFunction() = 0;

	//virtual std::shared_ptr<const MaterialFunction> materialFunction() const = 0;

	virtual bool setParameter(std::string_view name, float value) = 0;

	virtual bool setParameter(std::string_view name, const glm::vec2& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::vec3& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::vec4& value) = 0;

	virtual bool setParameter(std::string_view name, int value) = 0;

	virtual bool setParameter(std::string_view name, const glm::ivec2& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::ivec3& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::ivec4& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::mat3& value) = 0;

	virtual bool setParameter(std::string_view name, const glm::mat4& value) = 0;

	virtual bool setParameter(std::string_view name, std::shared_ptr<Reef::Texture> texture) = 0;

	virtual std::optional<ParameterValue> getParameter(std::string_view name) const = 0;

	virtual std::shared_ptr<Reef::Texture> getTextureParameter(std::string_view name) const = 0;
}; // class Material

} // namespace Reef

#endif // !#define ENGINE_CORE_MATERIAL_HPP
