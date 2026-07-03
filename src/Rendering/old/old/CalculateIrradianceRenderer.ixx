module;

#include <memory>

export module Engine.Rendering.CalculateIrradiance;

import Engine.Rendering.FullscreenTechnique;

import RenderLib;

import Engine.Rendering.Renderer;
import Engine.Texture;

namespace Reef
{

namespace Rendering
{

class CalculateIrradiance : public Engine::Rendering::FullscreenTechnique
{
public:

	bool initialize(RenderLib::Context& context, 
					std::shared_ptr<Engine::Texture> sourceTexture,
					std::shared_ptr<Engine::Texture> targetTexture);
};

} // namespace Rendering

} // namespace Reef