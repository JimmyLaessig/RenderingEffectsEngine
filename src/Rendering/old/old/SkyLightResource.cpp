module;

#include <glm/glm.hpp>

module Engine.Rendering.SkyLightData;

using namespace Reef::Rendering;


SkyLightData::SkyLightData(Engine::SkyLight& light)
	: mLight(light)
{
}


RenderLib::Texture*
SkyLightData::skyLightTexture()
{
	return mSkyLightTexture.get();
}


RenderLib::Texture*
SkyLightData::irradianceTexture()
{
	return mIrradianceTexture.get();
}


const glm::vec3&
SkyLightData::color()
{
	return mColor;
}
	

bool
SkyLightData::updateInternal(RenderLib::Context& context)
{
	mColor = mLight.color();

	//mSkyLightTexture = 
	return true;
}
