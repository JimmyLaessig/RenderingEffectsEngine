#ifndef ENGINE_CORE_SHADER_HPP
#define ENGINE_CORE_SHADER_HPP

#include <Reef/Export.hpp>

#include <csl/csl.hpp>

namespace Reef
{

enum class ShaderType
{
	LIT
}; // enum class ShaderType


class REEF_API Shader
{

public:

	virtual ~Shader() = default;

	virtual ShaderType ShaderType() const = 0;

	
	virtual void SetBaseColor(const csl::Vec4F& baseColor) = 0;

	virtual void SetWorldPosition(const csl::Vec3F& worldPosition) = 0;

}; // class Shader



class REEF_API ShaderFunction
{

}; // class ShaderFunction

} // namespace Reef

#endif // !ENGINE_CORE_SHADER_HPP
