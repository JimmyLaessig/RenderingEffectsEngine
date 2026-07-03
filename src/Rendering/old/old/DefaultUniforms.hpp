#ifndef ENGINE_RENDERING_DEFAULTUNIFORMS_HPP
#define ENGINE_RENDERING_DEFAULTUNIFORMS_HPP

#include <Coral/UniformBlockBuilder.hpp>

#include <Coral/Context.hpp>

namespace Reef::Rendering
{

class UniformBuffer : public Coral::UniformBlockBuilder
{
public:
 
	static std::unique_ptr<UniformBuffer> create(const Coral::UniformBlockDefinition& definition, Coral::Context& context)
	{
		std::unique_ptr<UniformBuffer> result(new UniformBuffer(definition));

		Coral::BufferCreateConfig config{};
		config.cpuVisible = true;
		config.size		  = result->data().size();
		config.type		  = Coral::BufferType::UNIFORM_BUFFER;

		auto buffer = context.createBuffer(config);
		if (!buffer)
		{
			return nullptr;
		}

		result->mBuffer = std::move(buffer.value());

		return result;
	}


	void flush()
	{
		if (auto dest = mBuffer->map())
		{
			auto source = this->data();
			std::memcpy(dest, source.data(), source.size_bytes());
			mBuffer->unmap();
		}
	}

	Coral::Buffer* buffer()
	{
		return mBuffer.get();}
	
private:

	UniformBuffer(const Coral::UniformBlockDefinition& definition)
		: Coral::UniformBlockBuilder(definition)
	{}

	Coral::BufferPtr mBuffer{ nullptr };

};


namespace FrameData
{
constexpr const uint32_t Binding = 0;

constexpr const std::string_view Name = "FrameData";

inline Coral::UniformBlockDefinition UniformBlockDefinition = {
	{
		{ Coral::UniformFormat::MAT44F, "viewMatrix" },
		{ Coral::UniformFormat::MAT44F, "projectionMatrix" },
		{ Coral::UniformFormat::MAT44F, "viewProjectionMatrix" },
	} 
};

} // namespace FrameData

namespace TransformData
{
constexpr const uint32_t Binding = 1;

constexpr const std::string_view Name = "TransformData";

inline Coral::UniformBlockDefinition UniformBlockDefinition = {
	{
		{ Coral::UniformFormat::MAT44F, "modelMatrix" },
		{ Coral::UniformFormat::MAT33F, "normalMatrix" },
	}
};

} // namespace TransformData


namespace MaterialData
{
	constexpr const uint32_t Binding = 2;

	constexpr const std::string_view Name = "MaterialData";
} // namespace MaterialData


} // namespace Reef::Rendering

#endif // !ENGINE_RENDERING_DEFAULTUNIFORMS_HPP
