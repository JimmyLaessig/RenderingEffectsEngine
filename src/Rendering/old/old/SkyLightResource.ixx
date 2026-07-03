module;

#include <glm/glm.hpp>

#include <memory>

export module Engine.Rendering.SkyLightData;

import Engine.Rendering.RenderResource;

import Engine.SkyLight;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class SkyLightData
{
public:

	SkyLightData(Engine::SkyLight& light);

	bool updateInternal(RenderLib::Context& context);

	RenderLib::Texture* skyLightTexture();

	RenderLib::Texture* irradianceTexture();

	const glm::vec3& color();

private:

	Engine::SkyLight& mLight;

	glm::vec3 mColor;

	std::shared_ptr<RenderLib::Texture> mSkyLightTexture;

	std::shared_ptr<RenderLib::Texture> mIrradianceTexture;
};

} // Rendering

} // Engine
