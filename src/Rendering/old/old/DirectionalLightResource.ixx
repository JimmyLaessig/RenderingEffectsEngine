module;

#include <glm/glm.hpp>

export module Engine.Rendering.DirectionalLightData;

import Engine.Rendering.RenderResource;

import Engine.DirectionalLight;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class DirectionalLightData 
{
public:

	DirectionalLightData(Engine::DirectionalLight& light);

	const glm::vec3& color() const;

	const glm::vec3& direction() const;

protected:
		
	bool updateInternal(RenderLib::Context& context);

private:

	Engine::DirectionalLight& mLight;

	glm::vec3 mColor;

	glm::vec3 mDirection;

	//std::shared_ptr<Rendering::Texture> mShadowMapTexture;

};

} // Rendering

} // Engine
