module;

#include <glm/glm.hpp>

#include <span>

export module Engine.Rendering.UniformBufferFactory;



import RenderLib.RAII;

namespace Reef
{

namespace Rendering
{

class UniformBufferFactory
{
public:

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, float value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::vec2& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::vec3& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::vec4& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, int value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::ivec2& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::ivec3& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::ivec4& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, unsigned int value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::uvec2& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::uvec3& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::uvec4& value);


	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::mat2& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::mat3& value);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const glm::mat4& value);



	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, std::span<float> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec2> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec3> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec4> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, std::span<int> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec2> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec3> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec4> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, std::span<unsigned int> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec2> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec3> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec4> values);


	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat2> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat3> values);

	static RenderLib::RAII::UniformBufferPtr createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat4> values);

};

} // Rendering

} // Engine
