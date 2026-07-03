#ifndef REEF_RENDERING_INDEXEDGEOMETRYRESOURCE_HPP
#define REEF_RENDERING_INDEXEDGEOMETRYRESOURCE_HPP

#include "RenderResource.hpp"

#include <Reef/Rendering/IndexedGeometry.hpp>

#include <Coral/Util/RAII.hpp>

#include <memory>

namespace Reef::Rendering
{

class IndexedGeometryResource : public RenderResource
{
public:

	IndexedGeometryResource(ResourceManager& resourceManager);

	CoBuffer indices();

	CoBuffer positions();

	CoBuffer normals();

	CoBuffer tangents();

	CoBuffer texcoords();

	uint32_t indexCount();

	struct Section
	{
		uint32_t firstIndex;
		uint32_t count;
	};

	const std::vector<Section>& spans() const;

	void bind(CoCommandBuffer commandBuffer);

	bool update(const IndexedGeometry& geom, CoContext context);

private:

	std::vector<Section> mSpans;
	Coral::BufferPtr mIndices;
	Coral::BufferPtr mPositions;
	Coral::BufferPtr mNormals;
	Coral::BufferPtr mTangents;
	Coral::BufferPtr mTexcoords;

	uint32_t mIndexCount{ 0 };

	CoIndexFormat mIndexFormat{ CO_INDEX_FORMAT_UINT32 };

}; // class IndexedGeometryResource

} // namespace Reef::Rendering 

#endif //! REEF_RENDERING_INDEXEDGEOMETRYRESOURCE_HPP
