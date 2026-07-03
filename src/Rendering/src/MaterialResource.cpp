#include <Engine/Rendering/MaterialResource.hpp>

#include <Engine/Rendering/ShaderImpl.hpp>
#include <Engine/Rendering/DefaultUniforms.hpp>
#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Core/Visitor.hpp>

#include <glm/glm.hpp>

#include <map>
#include <memory>
#include <ranges>
#include <span>
#include <vector>


using namespace Reef::Rendering;


MaterialResource::MaterialResource(ResourceManager& resourceManager)
	: RenderResource(resourceManager)
{
}


bool
MaterialResource::createDescriptorSet(const Reef::MaterialImpl& material, Coral::Context& context)
{
	auto materialFun = std::static_pointer_cast<const MaterialFunctionImpl>(material.materialFunction());
	if (!materialFun)
	{
		return false;
	}

	auto materialFunctionResource = resourceManager().getResource(*materialFun);

	if (!materialFunctionResource)
	{
		return false;
	}

	auto definitions = std::array{ &materialFunctionResource->vertexShader(), &materialFunctionResource->fragmentShader() }
		| std::views::filter([](auto shader) { return shader != nullptr; })
		| std::views::transform([](auto shader) { return shader->descriptorLayout(); })
		| std::views::join
		| std::views::filter([](const auto& descriptor) { return descriptor.binding > 1; });

	std::map<uint32_t, Coral::DescriptorBindingInfo> bindings;

	for (const auto& binding : definitions)
	{
		mNameToBindingLookUp[binding.name] = binding.binding;

		visit(binding.definition, Visitor{
			[&](const Coral::UniformBlockDefinition& uniformBlockDefinition)
			{
				mUniformBuffer = UniformBuffer::create(uniformBlockDefinition, context);
				updateUniformBuffer(material, context);
				mUniformBufferBinding = binding.binding;
			},
			[&](Coral::SamplerDefinition)
			{
				//if (auto texture = material.getTextureParameter(definition.name))
				//{
				//	if (auto textureResource = resourceManager().getResource(*texture))
				//	{
				//		descriptors.push_back(Coral::DescriptorBinding{ binding, textureResource->sampler() });
				//	}
				//}
			},
			[&](Coral::TextureDefinition)
			{
				//if (auto texture = material.getTextureParameter(definition.name))
				//{
				//	if (auto textureResource = resourceManager().getResource(*texture))
				//	{
				//		descriptors.push_back(Coral::DescriptorBinding{ binding, textureResource->texture() });
				//	}
				//}
			},
			[&](Coral::CombinedTextureSamplerDefinition)
			{
				if (auto texture = std::static_pointer_cast<TextureImpl>(material.getTextureParameter(binding.name)))
				{
					if (auto textureResource = resourceManager().getResource(*texture))
					{
						mNameToBindingLookUp[std::string(binding.name)] = binding.binding;
						mTextureBindings[binding.binding] = texture;
					}
				}
			}});
	}

	return true;
}


bool
MaterialResource::updateUniformBuffer(const Reef::MaterialImpl& material, Coral::Context& context)
{
	if (!mUniformBuffer)
	{
		return true;
	}

	for (const auto& [type, name, count, size, paddedSize] : mUniformBuffer->getBlockDefinition().members)
	{
		auto value = material.getParameter(name).value();

		visit(value, Visitor{
			[&](float v)		    { mUniformBuffer->setScalar(name, v); },
			[&](const glm::vec2& v) { mUniformBuffer->setVec2F(name, v); },
			[&](const glm::vec3& v) { mUniformBuffer->setVec3F(name, v); },
			[&](const glm::vec4& v) { mUniformBuffer->setVec4F(name, v); },

			[&](int v)			     { mUniformBuffer->setScalar(name, v); },
			[&](const glm::ivec2& v) { /*mUniformBuffer->setVec2I(name, v);*/ },
			[&](const glm::ivec3& v) { /*mUniformBuffer->setVec3I(name, v);*/ },
			[&](const glm::ivec4& v) { /*mUniformBuffer->setVec4I(name, v);*/ },
			//[&](bool v) { uniformData.block.setValue(i, v); },
			[&](const glm::mat3& m) { mUniformBuffer->setMat33F(name, m); },
			[&](const glm::mat4& m) { mUniformBuffer->setMat44F(name, m); },
			[&](std::shared_ptr<Texture>) { assert(false); },
		});
	}

	mUniformBuffer->flush();

	return true;
}


bool
MaterialResource::update(const Reef::MaterialImpl& material, Coral::Context& context)
{
	if (!shouldUpdate(material.version()))
	{
		return true;
	}

	if (auto l = material.tryLock())
	{
		return createDescriptorSet(material, context);
	}

	return false;
}


bool
MaterialResource::bind(Coral::CommandBuffer& commandBuffer)
{
	if (mUniformBuffer)
	{
		commandBuffer.cmdBindDescriptor(mUniformBuffer->buffer(), mUniformBufferBinding);
	}

	for (const auto& [binding, texture] : mTextureBindings)
	{
		if (auto textureResource = resourceManager().getResource(*texture))
		{
			commandBuffer.cmdBindDescriptor(textureResource->texture(), textureResource->sampler(), binding);
		}
	}

	return true;
}
