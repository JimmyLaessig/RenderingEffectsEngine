#ifndef ENGINE_RENDERING_TEXTURERESOURCE_HPP
#define ENGINE_RENDERING_TEXTURERESOURCE_HPP

#include <memory>

#include <Engine/Rendering/RenderResource.hpp>

//import Engine.Rendering.RenderResource;

#include <Engine/Core/TextureImpl.hpp>

#include <Coral/Coral.hpp>

namespace Reef::Rendering
{

class ResourceManager;

class TextureResource : public RenderResource
{
public:

	TextureResource(ResourceManager& resourceManager);

	Coral::Sampler* sampler();

	Coral::Image* texture();

	bool update(const Reef::TextureImpl& texture, Coral::Context& context);

private:

	Coral::ImagePtr mTexture{ nullptr };
	Coral::SamplerPtr mSampler{ nullptr };
};

} // Reef::Rendering 

#endif //! ENGINE_RENDERING_TEXTURERESOURCE_HPP
