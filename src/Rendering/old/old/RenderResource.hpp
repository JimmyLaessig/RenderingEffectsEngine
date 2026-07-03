#ifndef ENGINE_RENDERING_RENDERRESOURCE_HPP
#define ENGINE_RENDERING_RENDERRESOURCE_HPP

#include <memory>

#include <Engine/System.hpp>

#include <Coral/Coral.hpp>

namespace Reef::Rendering
{

class ResourceManager;

class RenderResource
{
public:

	RenderResource(ResourceManager& resourceManager);

	virtual ~RenderResource();

	size_t version() const;

protected:

	bool shouldUpdate(size_t version);

	ResourceManager& resourceManager();

private:

	ResourceManager& mResourceManager;

	size_t mVersion{ 0 };
};

} // Reef::Rendering 

#endif //! ENGINE_RENDERING_RENDERRESOURCE_HPP
