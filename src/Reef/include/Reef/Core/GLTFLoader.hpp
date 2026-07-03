#ifndef ENGINE_CORE_GLTFLOADER_HPP
#define ENGINE_CORE_GLTFLOADER_HPP

#include <Engine/SceneGraph/Scene.hpp>
#include <Engine/SceneGraph/Entity.hpp>

#include <filesystem>
#include <vector>

namespace Reef
{

class ENGINE_API GLTFLoader
{
public:

	static Entity* load(Scene& scene, const std::filesystem::path& path);

};

} // namespace Reef

#endif // !ENGINE_CORE_GLTFLOADER_HPP
