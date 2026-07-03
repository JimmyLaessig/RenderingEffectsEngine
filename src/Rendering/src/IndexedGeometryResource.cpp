#include "IndexedGeometryResource.hpp"

#include <glm/glm.hpp>

#include <cassert>
#include <vector>
#include <memory>
#include <span>

using namespace Reef::Rendering;

namespace
{

Coral::BufferPtr
createBuffer(CoContext context, uint32_t size, CoBufferType bufferType)
{
	CoBufferCreateConfig bufferConfig{};
	bufferConfig.size = size;
	bufferConfig.type = bufferType;

	Coral::BufferPtr buffer;
	if (!coContextCreateBuffer(context, &bufferConfig, std::out_ptr(buffer)) != CO_SUCCESS)
	{
		return nullptr;
	}

	return buffer;
}


CoIndexFormat
convert(Reef::Rendering::IndexFormat format)
{
	switch (format)
	{
		case Reef::Rendering::IndexFormat::UNSIGNED_SHORT: return CO_INDEX_FORMAT_UINT16;
		case Reef::Rendering::IndexFormat::UNSIGNED_INT: return CO_INDEX_FORMAT_UINT32;
	}

	std::unreachable();
}

} // namespace


IndexedGeometryResource::IndexedGeometryResource(ResourceManager& resourceManager)
	: RenderResource(resourceManager)
{}


CoBuffer
IndexedGeometryResource::indices()
{
	return mIndices.get();
}


CoBuffer
IndexedGeometryResource::positions()
{
	return mPositions.get();
}


CoBuffer
IndexedGeometryResource::normals()
{
	return mNormals.get();
}


CoBuffer
IndexedGeometryResource::tangents()
{
	return mTangents.get();
}


CoBuffer
IndexedGeometryResource::texcoords()
{
	return mTexcoords.get();
}


uint32_t
IndexedGeometryResource::indexCount()
{
	return mIndexCount;
}


void
IndexedGeometryResource::bind(CoCommandBuffer commandBuffer)
{
	coCommandBufferBindIndexBuffer(commandBuffer, indices(), mIndexFormat, 0);

	uint32_t binding{ 0 };

	coCommandBufferBindVertexBuffer(commandBuffer, positions(), binding++, 0, coAttributeFormatGetSizeInBytes(CO_ATTRIBUTE_FORMAT_VEC3F));
	coCommandBufferBindVertexBuffer(commandBuffer, normals(),   binding++, 0, coAttributeFormatGetSizeInBytes(CO_ATTRIBUTE_FORMAT_VEC3F));
	// coCommandBufferBindVertexBuffer(commandBuffer, tangents(),  binding++, 0, coAttributeFormatGetSizeInBytes(CO_ATTRIBUTE_FORMAT_VEC3F));
	coCommandBufferBindVertexBuffer(commandBuffer, texcoords(), binding++, 0, coAttributeFormatGetSizeInBytes(CO_ATTRIBUTE_FORMAT_VEC2F));
}


bool
IndexedGeometryResource::update(const IndexedGeometry& geom, CoContext context)
{
	if (!shouldUpdate(geom.version()))
	{
		return true;
	}

	// The resource is currently locked for CPU updates. Skip update for this frame
	auto locked = geom.tryLock();
	if (!locked)
	{
		return false;
	}

	auto indices = geom.indices();
	geom.indexCount();

	mIndexCount  = geom.indexCount();
	mIndices     = createBuffer(context, static_cast<uint32_t>(indices.size()), CO_BUFFER_TYPE_INDEX);
	mIndexFormat = convert(geom.indexFormat());

	mPositions = createBuffer(context, static_cast<uint32_t>(geom.positions().size()), CO_BUFFER_TYPE_VERTEX);
	mNormals   = createBuffer(context, static_cast<uint32_t>(geom.normals().size()),   CO_BUFFER_TYPE_VERTEX);
	mTangents  = createBuffer(context, static_cast<uint32_t>(geom.tangents().size()),  CO_BUFFER_TYPE_VERTEX);
	mTexcoords = createBuffer(context, static_cast<uint32_t>(geom.texcoords().size()), CO_BUFFER_TYPE_VERTEX);

	CoCommandQueue queue;
	if (coContextGetTransferQueue(context, &queue) != CO_SUCCESS)
	{
		return false;
	}

	CoCommandBufferCreateConfig commandBufferConfig{};
	commandBufferConfig.name = "Update primitive resource";

	Coral::CommandBufferPtr commandBuffer;
	if (!coCommandQueueCreateCommandBuffer(queue, &commandBufferConfig, std::out_ptr(commandBuffer)) != CO_SUCCESS)
	{
		return false;
	}

	coCommandBufferBegin(commandBuffer.get());
	
	CoUpdateBufferDataInfo updateBufferDataInfo{};
	updateBufferDataInfo.offset = 0;
	{
		updateBufferDataInfo.buffer    = mIndices.get();
		updateBufferDataInfo.pData     = reinterpret_cast<const CoByte*>(geom.indices().data());
		updateBufferDataInfo.dataCount = static_cast<uint32_t>(geom.indices().size());
		coCommandBufferUpdateBufferData(commandBuffer.get(), &updateBufferDataInfo);
	}

	{
		updateBufferDataInfo.buffer    = mPositions.get();
		updateBufferDataInfo.pData     = reinterpret_cast<const CoByte*>(geom.positions().data());
		updateBufferDataInfo.dataCount = static_cast<uint32_t>(geom.positions().size());
		coCommandBufferUpdateBufferData(commandBuffer.get(), &updateBufferDataInfo);
	}

	{
		updateBufferDataInfo.buffer    = mNormals.get();
		updateBufferDataInfo.pData     = reinterpret_cast<const CoByte*>(geom.normals().data());
		updateBufferDataInfo.dataCount = static_cast<uint32_t>(geom.normals().size());
		coCommandBufferUpdateBufferData(commandBuffer.get(), &updateBufferDataInfo);
	}

	//{
	//	updateBufferDataInfo.buffer = mTangentBuffer.get();
	//	updateBufferDataInfo.data = std::as_bytes(primitive.tangents());
	//	commandBuffer->cmdUpdateBufferData(updateBufferDataInfo);
	//}

	{
		updateBufferDataInfo.buffer = mTexcoords.get();
		updateBufferDataInfo.pData = reinterpret_cast<const CoByte*>(geom.texcoords().data());
		updateBufferDataInfo.dataCount = static_cast<uint32_t>(geom.texcoords().size());
		coCommandBufferUpdateBufferData(commandBuffer.get(), &updateBufferDataInfo);
	}

	coCommandBufferEnd(commandBuffer.get());

	Coral::FencePtr fence;
	CoFenceCreateConfig fenceConfig;
	if (coContextCreateFence(context, &fenceConfig, std::out_ptr(fence)) != CO_SUCCESS)
	{
		return false;
	}

	
	CoCommandBuffer cb;
	CoCommandBufferSubmitInfo submitInfo{};
	submitInfo.commandBufferCount   = 1;
	submitInfo.pCommandBuffers      = &cb;
	submitInfo.signalSemaphoreCount = 0;
	submitInfo.waitSemaphoreCount   = 0;

	coCommandQueueSubmit(queue, &submitInfo, fence.get());

	coFenceWait(fence.get());

	return true;
}
