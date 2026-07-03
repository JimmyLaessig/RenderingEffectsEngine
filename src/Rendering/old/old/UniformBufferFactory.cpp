module;

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

module Engine.Rendering.UniformBufferFactory;

import RenderLib;
import RenderLib.Context;
import RenderLib.UniformBuffer;

using namespace Reef::Rendering;


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, float value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)&value, RenderLib::UniformType::FLOAT });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::vec2& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::VEC2F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::vec3& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::VEC3F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::vec4& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::VEC4F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, int value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)&value, RenderLib::UniformType::INT32 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::ivec2& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::INT32_2 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::ivec3& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::INT32_3 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::ivec4& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::INT32_4 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, unsigned int value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)&value, RenderLib::UniformType::UINT32 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::uvec2& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::UINT32_2 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::uvec3& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::UINT32_3 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::uvec4& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::UINT32_4 });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::mat2& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::MAT2X2F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::mat3& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::MAT3X3F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const glm::mat4& value)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (std::byte*)glm::value_ptr(value), RenderLib::UniformType::MAT4X4F });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, std::span<float> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::FLOAT, (uint32_t)values.size()});
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec2> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::VEC2F, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec3> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::VEC3F, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::vec4> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::VEC4F, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, std::span<int> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::INT32, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec2> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::INT32_2, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec3> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::INT32_3, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::ivec4> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::INT32_4, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, std::span<unsigned int> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::UINT32, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec2> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::UINT32_2, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec3> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::UINT32_3, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::uvec4> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::UINT32_4, (uint32_t)values.size() });
}



RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat2> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::MAT2X2F, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat3> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::MAT3X3F, (uint32_t)values.size() });
}


RenderLib::RAII::UniformBufferPtr
UniformBufferFactory::createUniformBuffer(RenderLib::Context& context, const std::span<glm::mat4> values)
{
	return RenderLib::RAII::createUniformBuffer(&context, { (const std::byte*)values.data(), RenderLib::UniformType::MAT4X4F, (uint32_t)values.size() });
}

