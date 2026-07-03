#ifndef ENGINE_RENDERING_PRIMITIVERESOURCE_HPP
#define ENGINE_RENDERING_PRIMITIVERESOURCE_HPP

#include <memory>

#include <Engine/Core/PrimitiveImpl.hpp>

#include <Engine/Rendering/RenderResource.hpp>

#include <Coral/Coral.hpp>

namespace Reef::Rendering
{

class ResourceManager;

class PrimitiveResource : public RenderResource
{
public:
	
	PrimitiveResource(ResourceManager& resourceManager);

	Coral::Buffer* indices();

	Coral::Buffer* positions();

	Coral::Buffer* normals();

	Coral::Buffer* tangents();
	
	Coral::Buffer* texcoords();

	uint32_t indexCount();

	void bind(Coral::CommandBuffer& commandBuffer);

	bool update(const Reef::PrimitiveImpl& primitive, Coral::Context& context);

private:

	Coral::BufferPtr mIndices;
	Coral::BufferPtr mPositions;
	Coral::BufferPtr mNormals;
	Coral::BufferPtr mTangents;
	Coral::BufferPtr mTexcoords;

	uint32_t mIndexCount{ 0 };

	Coral::IndexFormat mIndexFormat{ Coral::IndexFormat::UINT32 };
};

} // Reef::Rendering 

#endif //! ENGINE_RENDERING_PRIMITIVERESOURCE_HPP
