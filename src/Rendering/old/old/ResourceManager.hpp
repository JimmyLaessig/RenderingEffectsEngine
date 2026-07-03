
#ifndef ENGINE_RENDERING_RESOURCEMANAGER_H
#define ENGINE_RENDERING_RESOURCEMANAGER_H

#include <Engine/Rendering/ResourceManager.hpp>

#include <Engine/Rendering/MaterialFunctionResource.hpp>
#include <Engine/Rendering/MaterialResource.hpp>
#include <Engine/Rendering/PrimitiveResource.hpp>
#include <Engine/Rendering/TextureResource.hpp>
#include <Engine/Rendering/TransformResource.hpp>

#include <Engine/Rendering/SceneView.hpp>

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <variant>


namespace Reef::Rendering
{
class IRenderer;


struct RenderObjectResolved
{

};


class ENGINE_API ResourceManager
{
public:

	ResourceManager(IRenderer& renderer);

	PrimitiveResource* getResource(const Reef::PrimitiveImpl& primitive);

	MaterialResource* getResource(const Reef::MaterialImpl& material);

	TransformResource* getResource(const Transform& transform);

	TextureResource* getResource(const Reef::TextureImpl& texture);

	MaterialFunctionResource* getResource(const Reef::MaterialFunctionImpl& materialFunction);

private:

	IRenderer& mRenderer;

	using Resource = std::variant<std::unique_ptr<PrimitiveResource>,
								  std::unique_ptr<MaterialResource>,
								  std::unique_ptr<TransformResource>,
								  std::unique_ptr<TextureResource>, 
								   std::unique_ptr<MaterialFunctionResource>>;

	std::unordered_map<size_t, Resource> mResources;
};

} // namespace Reef::Rendering

#endif // !ENGINE_RENDERING_RESOURCEMANAGER_H

