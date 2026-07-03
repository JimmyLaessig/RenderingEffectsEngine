module;

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <tiny_gltf.h>

#include <cassert>
#include <cstdint>
#include <span>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <concepts>

module Engine.MeshFactory;

import Engine.Mesh;
import Engine.Primitive;

using namespace Reef;

namespace 
{

template<typename T> std::pair<int, int> getType() { return {}; }

template<> std::pair<int, int> getType<uint8_t>() { return { TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, TINYGLTF_TYPE_SCALAR }; }
template<> std::pair<int, int> getType<uint16_t>() { return { TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, TINYGLTF_TYPE_SCALAR }; }
template<> std::pair<int, int> getType<uint32_t>() { return { TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, TINYGLTF_TYPE_SCALAR }; }

template<> std::pair<int, int> getType<int8_t>() { return { TINYGLTF_COMPONENT_TYPE_BYTE, TINYGLTF_TYPE_SCALAR }; }
template<> std::pair<int, int> getType<int16_t>() { return { TINYGLTF_COMPONENT_TYPE_SHORT, TINYGLTF_TYPE_SCALAR }; }
template<> std::pair<int, int> getType<int32_t>() { return { TINYGLTF_COMPONENT_TYPE_INT, TINYGLTF_TYPE_SCALAR }; }

template<> std::pair<int, int> getType<float>() { return { TINYGLTF_COMPONENT_TYPE_FLOAT, TINYGLTF_TYPE_SCALAR }; }
template<> std::pair<int, int> getType<double>() { return { TINYGLTF_COMPONENT_TYPE_DOUBLE, TINYGLTF_TYPE_SCALAR }; }

template<> std::pair<int, int> getType<glm::vec2>() { return { TINYGLTF_COMPONENT_TYPE_FLOAT, TINYGLTF_TYPE_VEC2 }; }
template<> std::pair<int, int> getType<glm::vec3>() { return { TINYGLTF_COMPONENT_TYPE_FLOAT, TINYGLTF_TYPE_VEC3 }; }
template<> std::pair<int, int> getType<glm::vec4>() { return { TINYGLTF_COMPONENT_TYPE_FLOAT, TINYGLTF_TYPE_VEC4 }; }


template<typename T>
std::vector<T>
getAttribute(const tinygltf::Accessor& accessor, const tinygltf::Model& model)
{
	auto [componentType, type] = getType<T>();

	const auto& bufferView = model.bufferViews[accessor.bufferView];
	const auto& buffer	   = model.buffers[bufferView.buffer];

	auto dataPtr = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;

	std::vector<T> attribute(accessor.count);

	auto byteSize = tinygltf::GetComponentSizeInBytes(componentType) * tinygltf::GetNumComponentsInType(type);

	assert(accessor.type == type);
	assert(accessor.componentType == componentType);
	assert(byteSize == sizeof(T));

	if (bufferView.byteStride > 0 &&
		bufferView.byteStride != sizeof(T))
	{
		for (size_t i = 0; i < accessor.count; ++i)
		{
			std::memcpy(&attribute[i], dataPtr + i * bufferView.byteStride, byteSize);
		}
	}
	else
	{
		std::memcpy(attribute.data(), dataPtr, attribute.size() * byteSize);
	}

	return attribute;
}


bool
createPrimitive(const tinygltf::Primitive& gltfPrimitive, const tinygltf::Model& model, Reef::Primitive& primitive)
{
	if (gltfPrimitive.indices >= 0)
	{
		auto& accessor		= model.accessors[gltfPrimitive.indices];
		auto& bufferView	= model.bufferViews[accessor.bufferView];
		auto& buffer		= model.buffers[bufferView.buffer];

		auto dataPtr = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;
		
		switch (accessor.componentType)
		{
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
			{
				auto indices8 = getAttribute<uint8_t>(accessor, model);
				std::vector<uint16_t> indices16(indices8.size());

				indices16.assign(indices8.begin(), indices8.end());

				primitive.setIndices(indices16);
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
			{
				auto indices = getAttribute<uint16_t>(accessor, model);
				primitive.setIndices(indices);
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
			{
				auto indices = getAttribute<uint32_t>(accessor, model);
				primitive.setIndices(indices);
				break;
			}

			default:
				break;
		}
	}

	auto positions = gltfPrimitive.attributes.find("POSITION");
	if (positions != gltfPrimitive.attributes.end())
	{
		auto attribute = getAttribute<glm::vec3>(model.accessors[positions->second], model);
		primitive.setPositions(attribute);
	}
	else
	{
		return false;
	}

	auto normals = gltfPrimitive.attributes.find("NORMAL");
	if (normals != gltfPrimitive.attributes.end())
	{
		auto attribute = getAttribute<glm::vec3>(model.accessors[normals->second], model);
		primitive.setNormals(attribute);
	}
	else
	{
		// TODO: Compute normals
		return false;
	}

	auto uvs = gltfPrimitive.attributes.find("TEXCOORD_0");
	if (uvs != gltfPrimitive.attributes.end())
	{
		auto attribute = getAttribute<glm::vec2>(model.accessors[uvs->second], model);
		primitive.setTexcoords(attribute);
	}

	auto tangent = gltfPrimitive.attributes.find("TANGENT");
	if (tangent != gltfPrimitive.attributes.end())
	{
		//auto attribute = getAttribute<glm::vec4>(model.accessors[tangent->second], model);
		//primitive.setTangents(attribute);
	}
	else
	{
		primitive.recalculateTangents();
	}
	
	return true;
}

} // namespace


std::shared_ptr<Reef::Mesh>
MeshFactory::createMesh(const tinygltf::Mesh& gltfMesh, const tinygltf::Model& model)
{
	auto result = std::make_shared<Reef::Mesh>();

	for (auto& gltfPrimitive : gltfMesh.primitives)
	{
		if (!createPrimitive(gltfPrimitive, model, result->addPrimitive()))
		{
			return nullptr;
		}
	}

	return result;
}
