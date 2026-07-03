#include <Engine/Core/GLTFLoader.hpp>

#include <Engine/Application/Application.hpp>

#include <Engine/Component/MeshComponent.hpp>

#include <Engine/Core/Mesh.hpp>
#include <Engine/Core/Texture.hpp>
#include <Engine/Core/Visitor.hpp>

#include <Engine/Rendering/Renderer.hpp>
#include <Engine/SceneGraph/Entity.hpp>
#include <Engine/SceneGraph/Scene.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <tiny_gltf.h>

#include <execution>
#include <filesystem>
#include <ranges>
#include <unordered_set>
#include <utility>

#undef OPAQUE

using namespace Reef;

namespace
{

struct TRS
{
	glm::vec3 translation{ 0.f, 0.f, 0.f };
	glm::quat rotation;
	glm::vec3 scale{ 1.f, 1.f, 1.f };
};


TRS
getTransform(const tinygltf::Node& node)
{
	glm::vec3 translation(0.f, 0.f, 0.f);

	glm::vec3 scale(1.f, 1.f, 1.f);

	glm::quat rotation = glm::quat::wxyz(1.f, 0.f, 0.f, 0.f);

	if (node.matrix.size() == 16)
	{
		glm::mat4 mat = glm::make_mat4(node.matrix.data());
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(mat, scale, rotation, translation, skew, perspective);
	}
	else
	{
		if (node.translation.size() == 3)
		{
			translation = glm::make_vec3(node.translation.data());
		}

		if (node.scale.size() == 3)
		{
			scale = glm::make_vec3(node.scale.data());
		}

		if (node.rotation.size() == 4)
		{
			rotation = glm::quat::wxyz(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]);
		}
	}
	return { translation , rotation, scale };
}


template<size_t L>
glm::vec<L, float>
convert(const std::vector<double>& v, const glm::vec<L, float>& defaultValue)
{
	glm::vec<L, float> vec = defaultValue;

	for (size_t i = 0; i < std::min(v.size(), L); ++i)
	{
		vec[i] = v[i];
	}

	return vec;
}


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
	const auto& bufferView = model.bufferViews[accessor.bufferView];
	const auto& buffer = model.buffers[bufferView.buffer];

	auto [componentType, type] = getType<T>();


	auto dataPtr = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;

	std::vector<T> attribute(accessor.count);

	auto byteSize = tinygltf::GetComponentSizeInBytes(componentType) * tinygltf::GetNumComponentsInType(type);

	assert(accessor.type == type);
	assert(accessor.componentType == componentType);
	assert(byteSize == sizeof(T));

	// The attributes are tightly packed
	if (bufferView.byteStride == 0 || bufferView.byteStride == sizeof(T))
	{
		std::memcpy(attribute.data(), dataPtr, attribute.size() * byteSize);
	}
	// The attributes are in an interleaved buffer und must be deinterleaved
	else
	{
		for (size_t i = 0; i < accessor.count; ++i)
		{
			std::memcpy(&attribute[i], dataPtr + i * bufferView.byteStride, byteSize);
		}
	}

	return attribute;
}


bool
createPrimitive(const tinygltf::Primitive& gltfPrimitive, 
				const tinygltf::Model& model, Reef::Primitive& primitive, 
				const std::vector<std::shared_ptr<Reef::Material>>& materials)
{
	std::variant<std::vector<uint32_t>, std::vector<uint16_t>> indices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> texcoords;

	auto attribute = gltfPrimitive.attributes.find("POSITION");
	if (attribute != gltfPrimitive.attributes.end())
	{
		positions = getAttribute<glm::vec3>(model.accessors[attribute->second], model);
	}

	attribute = gltfPrimitive.attributes.find("NORMAL");
	if (attribute != gltfPrimitive.attributes.end())
	{
		normals = getAttribute<glm::vec3>(model.accessors[attribute->second], model);
	}

	attribute = gltfPrimitive.attributes.find("TEXCOORD_0");
	if (attribute != gltfPrimitive.attributes.end())
	{
		texcoords = getAttribute<glm::vec2>(model.accessors[attribute->second], model);
	}

	attribute = gltfPrimitive.attributes.find("TANGENT");
	if (attribute != gltfPrimitive.attributes.end())
	{
		//tangentAttribute = getAttribute<glm::vec4>(model.accessors[tangent->second], model);
	}

	if (gltfPrimitive.indices >= 0)
	{
		auto& accessor = model.accessors[gltfPrimitive.indices];

		switch (accessor.componentType)
		{
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
			{
				auto indices8 = getAttribute<uint8_t>(accessor, model);
				indices = std::vector<uint16_t>(indices8.begin(), indices8.end());
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
			{
				indices = getAttribute<uint16_t>(accessor, model);
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
			{
				indices = getAttribute<uint32_t>(accessor, model);
				break;
			}
			default:
				break;
		}
	}

	auto success = visit(indices, Visitor{
		[&](const auto& i) { return primitive.set(i, positions, normals, tangents, texcoords); }
		});
	
	if (!success)
	{
		return false;
	}

	primitive.setMaterial(materials[static_cast<size_t>(gltfPrimitive.material)]);
	return true;
}


std::optional<TextureFormat>
getTextureFormat(const tinygltf::Image& image)
{
	auto pixelCount = image.width * image.height;
	auto componentSize = image.bits / 8;

	auto channelCount = image.image.size() / pixelCount / componentSize;

	std::pair<int, size_t> pixelFormat{ image.pixel_type, channelCount };

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, 1 })
	{
		return TextureFormat::R_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, 2 })
	{
		return TextureFormat::RG_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, 3 })
	{
		return TextureFormat::RGB_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, 4 })
	{
		return TextureFormat::RGBA_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, 1 })
	{
		return TextureFormat::R_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, 2 })
	{
		return TextureFormat::RG_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, 3 })
	{
		return TextureFormat::RGB_8U;
	}

	if (pixelFormat == std::pair<int, int>{ TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, 4 })
	{
		return TextureFormat::RGBA_8U;
	}


	assert(false && "Unsupported texture format");

	return {};
}


std::shared_ptr<Reef::Texture>
createTexture(const tinygltf::Texture& texture, const tinygltf::Model& model)
{
	const auto& image = model.images[texture.source];

	auto textureFormat = getTextureFormat(image);

	if (!textureFormat)
	{
		return nullptr;
	}

	return Reef::Texture::create(static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height),
								 *textureFormat, std::as_bytes(std::span{ image.image }), texture.name);
}


std::optional<glm::vec4>
convert(const std::vector<double>& v)
{
	if (v.size() != 4)
	{
		return {};
	}

	return glm::vec4(static_cast<float>(v[0]), static_cast<float>(v[1]), static_cast<float>(v[2]), static_cast<float>(v[3]));
}


enum class AlphaMode
{
	OPAQUE,
	MASKED
};


std::shared_ptr<MaterialFunction>
createGLTFMaterialFunction(AlphaMode alphaMode)
{
	auto materialFunction = MaterialFunction::create();

	csl::Input<csl::float2> texCoords("Texcoord0");

	auto baseColorFactor  = csl::Parameter<csl::float4>("baseColorFactor");
	auto baseColorTexture = csl::Parameter<csl::Sampler2D>("baseColorTexture");

	csl::Float opacity(1.f);

	if (alphaMode == AlphaMode::MASKED)
	{
		auto alphaCutoff = csl::Parameter<csl::Float>("alphaCutoff");
		auto opacity     = baseColorTexture.sample(texCoords).w();
		materialFunction->setMask(opacity >= alphaCutoff);
	}

	auto baseColor = baseColorFactor.xyz() * baseColorTexture.sample(texCoords).xyz();

	materialFunction->setBaseColor(baseColor.xyz());

	return materialFunction;
}


static std::shared_ptr<MaterialFunction> sOpaqueMaterialFunction = createGLTFMaterialFunction(AlphaMode::OPAQUE);
static std::shared_ptr<MaterialFunction> sMaskedMaterialFunction = createGLTFMaterialFunction(AlphaMode::MASKED);

std::shared_ptr<Reef::Material>
createMaterial(const tinygltf::Material& material, 
			   const tinygltf::Model& model, 
			   const std::vector<std::shared_ptr<Texture>>& textures)
{
	auto convert = [&](int i) -> std::optional<std::shared_ptr<Texture>>
	{
		if (i < 0)
		{
			return {};
		}

		return textures[static_cast<size_t>(i)];
	};

	auto result = Reef::Material::create();
	result->setName(material.name);

	if (material.alphaMode == "MASK")
	{
		result->setMaterialFunction(sMaskedMaterialFunction);
		result->setParameter("alphaCutoff", static_cast<float>(material.alphaCutoff));
	}
	else if (material.alphaMode == "OPAQUE")
	{
		result->setMaterialFunction(sOpaqueMaterialFunction);
	}
	
	result->setParameter("baseColorFactor", ::convert(material.pbrMetallicRoughness.baseColorFactor).value_or(glm::vec4(1.f)));
	result->setParameter("baseColorTexture", convert(material.pbrMetallicRoughness.baseColorTexture.index).value_or(Texture::White));
	
	// PBR parameters
	// result->setParameter("baseColor",				 convert(material.pbrMetallicRoughness.baseColorFactor, glm::vec3{ 1.f, 1.f, 1.f }));
	//result->setParameter("roughness",				 static_cast<float>(material.pbrMetallicRoughness.roughnessFactor));
	//result->setParameter("metallic",				 static_cast<float>(material.pbrMetallicRoughness.metallicFactor));
	//result->setParameter("metallicRoughnessTexture", getTextureOrDefault(material.pbrMetallicRoughness.metallicRoughnessTexture.index, Reef::Texture::White));
	//// Emissive
	//result->setParameter("emissiveColor",			 convert(material.emissiveFactor, glm::vec3{ 0.f, 0.f, 0.f }));
	//result->setParameter("emissiveTexture",			 getTextureOrDefault(material.pbrMetallicRoughness.metallicRoughnessTexture.index, Reef::Texture::White));
	//// Occlusion
	//result->setParameter("occlusionTexture",		 getTextureOrDefault(material.occlusionTexture.index, Reef::Texture::White));
	//// Normal mapping
	//result->setParameter("normalTexture",			 getTextureOrDefault(material.normalTexture.index, Reef::Texture::Normal));

	return result;
}


std::shared_ptr<Reef::Mesh>
createMesh(const tinygltf::Mesh& gltfMesh, const tinygltf::Model& model, const std::vector<std::shared_ptr<Material>>& materials)
{
	auto result = Reef::Mesh::create();
	result->setName(gltfMesh.name);

	for (auto& gltfPrimitive : gltfMesh.primitives)
	{
		if (!createPrimitive(gltfPrimitive, model, result->addPrimitive(), materials))
		{
			return nullptr;
		}
	}

	return result;
}


void
createSceneGraphRecursive(const tinygltf::Node& node, const tinygltf::Model& model, Entity& parent, Scene& scene,
						  const std::vector<std::shared_ptr<Mesh>>& meshes)
{
	auto trs = getTransform(node);
	auto entity = scene.createEntity();

	entity->setParent(&parent);
	entity->setName(node.name);
	entity->transform().setLocalPose(trs.translation, trs.rotation, trs.scale);

	if (node.mesh >= 0)
	{
		auto meshComponent = entity->addComponent<MeshComponent>();
		meshComponent->setMesh(meshes.at(static_cast<size_t>(node.mesh)));
	}

	for (auto nodeIndex : node.children)
	{
		createSceneGraphRecursive(model.nodes[nodeIndex], model, *entity, scene, meshes);
	}
}


Entity*
createSceneGraph(const tinygltf::Scene& gltfScene, const tinygltf::Model& model, Scene& scene,
				 const std::vector<std::shared_ptr<Mesh>>& meshes)
{
	Entity* entity = scene.createEntity();
	entity->setName(gltfScene.name);
	for (auto nodeIndex : gltfScene.nodes)
	{
		createSceneGraphRecursive(model.nodes[nodeIndex], model, *entity, scene, meshes);
	}

	return entity;
}


Entity*
loadModel(Scene& scene, const tinygltf::Model& model, const std::optional<size_t>& sceneIndex)
{
	if (sceneIndex && sceneIndex >= model.scenes.size())
	{
		return {};
	}

	auto textures = model.textures |
		std::views::transform([&](const auto& texture) { return createTexture(texture, model); }) |
		std::ranges::to<std::vector>();

	auto materials = model.materials |
		std::views::transform([&](const auto& material) { return createMaterial(material, model, textures); }) |
		std::ranges::to<std::vector>();

	auto meshes = model.meshes |
		std::views::transform([&](const auto& mesh) { return createMesh(mesh, model, materials); }) |
		std::ranges::to<std::vector>();

	Entity* root = scene.createEntity();

	// Finally, create the scene graph
	auto scenes = model.scenes
		| std::views::transform([&](const tinygltf::Scene& gltfScene) { return createSceneGraph(gltfScene, model, scene, meshes); });
	
	for (auto scene : scenes)
	{
		scene->setParent(root);
	}

	return root;
}

} // namespace


Entity*
GLTFLoader::load(Scene& scene, const std::filesystem::path& path)
{
	tinygltf::Model model;
	std::string err;
	std::string warn;
	tinygltf::TinyGLTF loader;

	auto extension = path.extension();
	if (extension == ".glb")
	{
		if (!loader.LoadBinaryFromFile(&model, &err, &warn, path.string()))
		{
			return {};
		}
	}
	else if (extension == ".gltf")
	{
		if (!loader.LoadASCIIFromFile(&model, &err, &warn, path.string()))
		{
			return {};
		}
	}
	else
	{
		return {};
	}

	return loadModel(scene, model, {});
}
