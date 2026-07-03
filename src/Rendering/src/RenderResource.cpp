#include "RenderResource.hpp"

#include "ResourceManager.hpp"

#include <glm/glm.hpp>

#include <cassert>
#include <vector>
#include <memory>
#include <span>

using namespace Reef::Rendering;


RenderResource::RenderResource(ResourceManager& resourceManager)
    : mResourceManager(resourceManager)
{
}


RenderResource::~RenderResource()
{}


size_t
RenderResource::version() const
{
    return mVersion;
}


bool
RenderResource::shouldUpdate(size_t version)
{
    bool result = version > mVersion || mVersion == std::numeric_limits<size_t>::max();

    mVersion = version;

    return result;
}


ResourceManager& 
RenderResource::resourceManager()
{
    return mResourceManager;
}
