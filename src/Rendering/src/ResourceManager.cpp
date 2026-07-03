#include "ResourceManager.hpp"

#include "IndexedGeometryResource.hpp"
#include "TransformResource.hpp"
#include <Reef/Rendering/Renderer.hpp>

#include <Reef/Util/Visitor.hpp>

#include <memory>
#include <variant>



using namespace Reef::Rendering;


ResourceManager::ResourceManager(Renderer& renderer)
	: mRenderer(renderer)
{
}


IndexedGeometryResource*
ResourceManager::getResource(const IndexedGeometry& geom)
{
	auto id = reinterpret_cast<size_t>(&geom);
	auto iter = mResources.find(id);
	if (iter == mResources.end())
	{
		mResources[id] = std::make_unique<IndexedGeometryResource>(*this);
		iter           = mResources.find(id);
	}

	return Reef::Util::visit(iter->second, Reef::Util::Visitor{
		[](const auto&) -> IndexedGeometryResource* { return nullptr; },
		[&](const std::unique_ptr<IndexedGeometryResource>& ptr) -> IndexedGeometryResource*
		{
			return ptr->update(geom, mRenderer.context()) ? ptr.get() : nullptr;
		}
	});
}


//MaterialResource*
//ResourceManager::getResource(const Reef::MaterialImpl& material)
//{
//	auto id = reinterpret_cast<size_t>(&material);
//	auto iter = mResources.find(id);
//	if (iter == mResources.end())
//	{
//		mResources[id] = std::make_unique<MaterialResource>(*this);
//		iter = mResources.find(id);
//	}
//
//	return visit(iter->second, Visitor{ 
//		[](const auto& ptr) -> MaterialResource* {  return nullptr; },
//		[&](const std::unique_ptr<MaterialResource>& ptr) -> MaterialResource*
//		{
//			return ptr->update(material, mRenderer.context()) ? ptr.get() : nullptr;
//		}
//	});
//}


//TransformResource*
//ResourceManager::getResource(const Transform& transform)
//{
//	auto id = transform.objectId;
//	auto iter = mResources.find(id);
//	if (iter == mResources.end())
//	{
//		mResources[id] = std::make_unique<TransformResource>(*this);
//		iter = mResources.find(id);
//	}
//
//	return visit(iter->second, Visitor{
//		[](const auto& ptr) -> TransformResource* { return nullptr; },
//		[&](const std::unique_ptr<TransformResource>& ptr) -> TransformResource*
//		{
//			return ptr->update(transform, mRenderer.context()) ? ptr.get() : nullptr;
//		} });
//}


//TextureResource*
//ResourceManager::getResource(const Reef::TextureImpl& texture)
//{
//	auto id = reinterpret_cast<size_t>(&texture);
//	auto iter = mResources.find(id);
//	if (iter == mResources.end())
//	{
//		mResources[id] = std::make_unique<TextureResource>(*this);
//		iter = mResources.find(id);
//	}
//
//	return visit(iter->second, Visitor{
//		[](const auto& ptr) -> TextureResource* {  return nullptr; },
//		[&](const std::unique_ptr<TextureResource>& ptr) -> TextureResource*
//		{
//			return ptr->update(texture, mRenderer.context()) ? ptr.get() : nullptr;
//		}
//		});
//}


//MaterialFunctionResource*
//ResourceManager::getResource(const Reef::MaterialFunctionImpl& materialFunction)
//{
//	auto id = reinterpret_cast<size_t>(&materialFunction);
//	auto iter = mResources.find(id);
//	if (iter == mResources.end())
//	{
//		mResources[id] = std::make_unique<MaterialFunctionResource>(*this);
//		iter = mResources.find(id);
//	}
//
//	return visit(iter->second, Visitor{
//		[](const auto& ptr) -> MaterialFunctionResource* {  return nullptr; },
//		[&](const std::unique_ptr<MaterialFunctionResource>& ptr) -> MaterialFunctionResource*
//		{
//			return ptr->update(materialFunction, mRenderer.context()) ? ptr.get() : nullptr;
//		}
//		});
//}

