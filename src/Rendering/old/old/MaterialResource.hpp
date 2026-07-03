#ifndef ENGINE_RENDERING_MATERIALRESOURCE_HPP
#define ENGINE_RENDERING_MATERIALRESOURCE_HPP

#include <Engine/Rendering/RenderResource.hpp>

#include <Engine/Core/MaterialImpl.hpp>
#include <Engine/Core/TextureImpl.hpp>

#include <Engine/Rendering/DefaultUniforms.hpp>

#include <Coral/Coral.hpp>

#include <memory>

namespace Reef::Rendering
{

class ENGINE_API MaterialResource : public RenderResource
{
public:

	MaterialResource(ResourceManager& resourceManager);

	/// Update the material's render resource
	bool update(const Reef::MaterialImpl& material, Coral::Context& context);

	/// Bind the material resource to the command buffer
	bool bind(Coral::CommandBuffer& commandBuffer);

private:

	bool createDescriptorSet(const Reef::MaterialImpl& material, Coral::Context& context);

	bool updateUniformBuffer(const Reef::MaterialImpl& material, Coral::Context& context);

	std::unordered_map<std::string, uint32_t> mNameToBindingLookUp;

	std::unique_ptr<Reef::Rendering::UniformBuffer> mUniformBuffer;

	std::unordered_map<uint32_t, std::shared_ptr<Reef::TextureImpl>> mTextureBindings;

	uint32_t mUniformBufferBinding{ 0 };
};

} // namespace Reef::Rendering

#endif //!ENGINE_RENDERING_MATERIALRESOURCE_HPP
