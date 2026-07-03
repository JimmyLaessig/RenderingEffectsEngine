#ifndef REEF_RENDERING_RENDERRESOURCE_HPP
#define REEF_RENDERING_RENDERRESOURCE_HPP

#include <memory>

#include <Coral/Coral.h>

namespace Reef::Rendering
{

class ResourceManager;

/*!
 * Base class for a managing one or more GPU resources
 */
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

#endif //! REEF_RENDERING_RENDERRESOURCE_HPP
