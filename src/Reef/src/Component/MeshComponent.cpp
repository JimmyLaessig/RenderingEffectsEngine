#include <Reef/Component/MeshComponent.hpp>

#include <memory>

#include "../Core/EntityImpl.hpp"
#include "../Core/SceneImpl.hpp"

using namespace Reef;


std::shared_ptr<Mesh> 
MeshComponent::mesh()
{
	return mMesh;
}


std::shared_ptr<const Mesh>
MeshComponent::mesh() const
{
	return mMesh;
}


void
MeshComponent::setMesh(std::shared_ptr<Mesh> mesh)
{
	mMesh = mesh;

    static_cast<SceneImpl&>(owner().scene()).sendComponentPropertyChanged(*this);

	//mMaterialOverride.clear();
	//if (mMesh)
	//{
	//	mMaterialOverride.resize(mMesh->primitiveCount());
	//}
}
//
//
//bool 
//MeshComponent::setMaterial(std::shared_ptr<Material> material, uint32_t primitiveIndex)
//{
//	if (primitiveIndex >= mMaterialOverride.size())
//	{
//		return false;
//	}
//
//	mMaterialOverride[primitiveIndex] = material;
//
//	return true;
//}
//
//
//std::shared_ptr<Material> 
//MeshComponent::material(uint32_t index)
//{
//	if (index >= mMaterialOverride.size())
//	{
//		return nullptr;
//	}
//
//	auto material = mMaterialOverride[index];
//	if (!material)
//	{
//		if (auto primitive = mMesh->getPrimitive(index))
//		{
//			material = primitive->material();
//		}
//	}
//
//	return material;
//}
//
