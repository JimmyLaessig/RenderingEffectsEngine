module;

#include <glm/glm.hpp>

module Engine.Rendering.DirectionalLightData;

using namespace Reef::Rendering;


DirectionalLightData::DirectionalLightData(Engine::DirectionalLight& light)
	: mLight(light)
{
}


const glm::vec3&
DirectionalLightData::color() const
{
	return mColor;
}


const glm::vec3&
DirectionalLightData::direction() const
{
	return mDirection;
}


bool
DirectionalLightData::updateInternal(RenderLib::Context& context)
{
	//if (!mShadowMapTexture)
	//{
	//	mShadowMapTexture = ::Engine::Rendering::createTexture();

	//}

	mColor = mLight.color();
	mDirection = mLight.direction();

	return true;
}