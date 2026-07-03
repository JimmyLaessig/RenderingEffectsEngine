#include <Engine/Core/PrimitiveImpl.hpp>

using namespace Reef;

namespace
{

template<typename T>
void copy(const std::span<T> src, std::vector<std::byte>& target)
{
	target.resize(src.size_bytes());
	std::memcpy(target.data(), src.data(), target.size());
}


template<typename IndexType>
std::vector<glm::vec3>
computeTangents(const std::span<IndexType> indices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texcoords)
{
	std::vector<glm::vec3> tangents(positions.size());

	for (uint32_t i = 0; i < indices.size(); i += 3)
	{
		const auto& p0 = positions[indices[i    ]];
		const auto& p1 = positions[indices[i + 1]];
		const auto& p2 = positions[indices[i + 2]];

		const auto& uv0 = texcoords[indices[i    ]];
		const auto& uv1 = texcoords[indices[i + 1]];
		const auto& uv2 = texcoords[indices[i + 2]];

		auto& t0 = tangents[indices[i    ]];
		auto& t1 = tangents[indices[i + 1]];
		auto& t2 = tangents[indices[i + 2]];

		auto e01 = p1 - p0;
		auto e02 = p2 - p0;

		auto deltaUV01 = uv1 - uv0;
		auto deltaUV02 = uv2 - uv0;

		float f = 1.0f / (deltaUV01.x * deltaUV02.y - deltaUV02.x * deltaUV01.y);

		t0.x = f * (deltaUV02.y * e01.x - deltaUV01.y * e02.x);
		t0.y = f * (deltaUV02.y * e01.y - deltaUV01.y * e02.y);
		t0.z = f * (deltaUV02.y * e01.z - deltaUV01.y * e02.z);

		t0 = glm::normalize(t0);
		t1 = t0;
		t2 = t0;
	}

	return tangents;
}


std::vector<glm::vec3>
computeTangents(const std::vector<std::byte>& indices,
				IndexFormat indexType,
				const std::vector<glm::vec3>& positions,
				const std::vector<glm::vec2>& texcoords)
{
	switch (indexType)
	{
		case IndexFormat::UNSIGNED_INT:
			return computeTangents(std::span<uint32_t>((uint32_t*)indices.data(), indices.size() / 4), positions, texcoords);
		case IndexFormat::UNSIGNED_SHORT:
			return computeTangents(std::span<uint16_t>((uint16_t*)indices.data(), indices.size() / 2), positions, texcoords);
	}
	assert(false);
	return {};
}

} // namespace


PrimitiveImpl::PrimitiveImpl()
{

}


bool
PrimitiveImpl::set(std::span<const uint16_t> indices,
			       std::span<const glm::vec3> positions,
			       std::span<const glm::vec3> normals,
			       std::span<const glm::vec3> tangents,
			       std::span<const glm::vec2> texCoords)
{
	return set(std::as_bytes(indices), IndexFormat::UNSIGNED_SHORT, positions, normals, tangents, texCoords);
}


bool
PrimitiveImpl::set(std::span<const uint32_t> indices,
			       std::span<const glm::vec3> positions,
			       std::span<const glm::vec3> normals,
			       std::span<const glm::vec3> tangents,
			       std::span<const glm::vec2> texCoords)
{
	return set(std::as_bytes(indices), IndexFormat::UNSIGNED_INT, positions, normals, tangents, texCoords);
}


bool
PrimitiveImpl::set(std::span<const std::byte> indices,
			   IndexFormat indexFormat,
			   std::span<const glm::vec3> positions,
			   std::span<const glm::vec3> normals,
			   std::span<const glm::vec3> tangents,
			   std::span<const glm::vec2> texCoords)
{
	if (positions.empty())
	{
		return false;
	}

	if (!normals.empty() && normals.size() != positions.size())
	{
		return false;
	}

	if (!texCoords.empty() && texCoords.size() != positions.size())
	{
		return false;
	}

	if (!tangents.empty() && tangents.size() != positions.size())
	{
		return false;
	}

	if (!indices.empty())
	{
		mIndices.assign(indices.begin(), indices.end());
	}
	else
	{
		// TODO: create index buffer
		return false;
	}

	
	mIndexFormat = indexFormat;

	mPositions.assign(positions.begin(), positions.end());

	if (!normals.empty())
	{
		mNormals.assign(normals.begin(), normals.end());
	}
	else
	{
		recalculateNormals();
	}

	if (!texCoords.empty())
	{
		mTexCoords.assign(texCoords.begin(), texCoords.end());
	}
	else
	{
		mTexCoords.assign(mPositions.size(), glm::vec2(0.f, 0.f));
	}

	if (!tangents.empty())
	{
		mTangents.assign(tangents.begin(), tangents.end());
	}
	else
	{
		recalculateTangents();
	}

	markOutdated();

	return true;
}


std::span<const std::byte>
PrimitiveImpl::indices() const
{
	return mIndices;
}


IndexFormat
PrimitiveImpl::indexFormat() const
{
	return mIndexFormat;
}


std::span<const glm::vec3>
PrimitiveImpl::positions() const
{
	return mPositions;
}


std::span<const glm::vec3>
PrimitiveImpl::normals() const
{
	return mNormals;
}


std::span<const glm::vec3>
PrimitiveImpl::tangents() const
{
	return mTangents;
}


std::span<const glm::vec2>
PrimitiveImpl::texcoords() const
{
	return mTexCoords;
}


std::shared_ptr<Material>
PrimitiveImpl::material()
{
	return mMaterial;
}


std::shared_ptr<const Material>
PrimitiveImpl::material() const
{
	return mMaterial;
}


void
PrimitiveImpl::setMaterial(std::shared_ptr<Material> material)
{
	mMaterial = material;
}


const BoundingBox3D&
PrimitiveImpl::boundingBox() const
{
	return mBoundingBox;
}


void
PrimitiveImpl::recalculateBoundingBox()
{
	mBoundingBox = BoundingBox3D();

	for (auto& p : mPositions)
	{
		mBoundingBox += p;
	}
}


void
PrimitiveImpl::recalculateNormals()
{
	mNormals.assign(mPositions.size(), glm::vec3(1.f, 0.f, 0.f));
	assert(false);
}


void
PrimitiveImpl::recalculateTangents()
{
	switch (mIndexFormat)
	{
		case IndexFormat::UNSIGNED_INT:
			mTangents = computeTangents(std::span<uint32_t>((uint32_t*)mIndices.data(), mIndices.size() / 4), mPositions, mTexCoords);
			break;
		case IndexFormat::UNSIGNED_SHORT:
			mTangents = computeTangents(std::span<uint16_t>((uint16_t*)mIndices.data(), mIndices.size() / 2), mPositions, mTexCoords);
			break;
	}
}
