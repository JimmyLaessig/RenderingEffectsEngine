#ifndef REEF_UTIL_MATERIAL_HPP
#define REEF_UTIL_MATERIAL_HPP

//#include <Common/MaterialFunction.hpp>
#include <Common/Texture.hpp>
#include <Common/StringMap.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace Reef::Util
{

class Material : public Resource
{

public:

 static std::unique_ptr<Material> create();

 using ParameterValue = std::variant<float, glm::vec2, glm::vec3, glm::vec4,
                                     int, glm::ivec2, glm::ivec3, glm::ivec4,
                                     glm::mat3, glm::mat4,
                                     std::shared_ptr<const Texture>>;

 //virtual void setMaterialFunction(std::shared_ptr<MaterialFunction> materialFunction) = 0;

 //virtual std::shared_ptr<MaterialFunction> materialFunction() = 0;

 //virtual std::shared_ptr<const MaterialFunction> materialFunction() const = 0;

 bool setParameter(std::string_view name, float value);

 bool setParameter(std::string_view name, const glm::vec2& value);

 bool setParameter(std::string_view name, const glm::vec3& value);

 bool setParameter(std::string_view name, const glm::vec4& value);

 bool setParameter(std::string_view name, int value);

 bool setParameter(std::string_view name, const glm::ivec2& value);

 bool setParameter(std::string_view name, const glm::ivec3& value);

 bool setParameter(std::string_view name, const glm::ivec4& value);

 bool setParameter(std::string_view name, const glm::mat3& value);

 bool setParameter(std::string_view name, const glm::mat4& value);

 bool setParameter(std::string_view name, std::shared_ptr<Texture> texture);

 std::optional<ParameterValue> getParameter(std::string_view name) const;

 std::shared_ptr<Texture> getTextureParameter(std::string_view name) const;

private:

 bool setParameterImpl(std::string_view name, ParameterValue value);

 UnorderedStringMap<ParameterValue> mParameters;

 //std::shared_ptr<MaterialFunction> mMaterialFunction;

}; // class Material

} // namespace Reef::Util

#endif // !REEF_UTIL_MATERIAL_HPP
