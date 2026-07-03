#include "TransformResource.hpp"

#include <glm/glm.hpp>

#include <cassert>
#include <vector>
#include <memory>
#include <span>

using namespace Reef::Rendering;


TransformResource::TransformResource(ResourceManager& resourceManager)
	: RenderResource(resourceManager)
{}


CoBuffer
TransformResource::getUniformBuffer()
{
	return nullptr;
}


bool
TransformResource::update(const glm::mat4& localToWorldMatrix, CoContext context)
{
	/*if (!mUniformBuffer)
	{
		mUniformBuffer = UniformBuffer::create(Reef::Rendering::TransformData::UniformBlockDefinition, context);
	}

	if (!mUniformBuffer)
	{
		return false;
	}

	if (!mUniformBuffer->setMat44F("modelMatrix", transform.localToWorldMatrix))
	{
		assert(false);
		return false;
	}

	if (!mUniformBuffer->setMat33F("normalMatrix", transform.normalMatrix))
	{
		assert(false);
		return false;
	}

	mUniformBuffer->flush();*/

	return true;
}


bool
TransformResource::bind(CoCommandBuffer commandBuffer)
{
	//coCommandBufferBindUniformBuffer(commandBuffer, mUniformBuffer, 0);
	return true;
}
