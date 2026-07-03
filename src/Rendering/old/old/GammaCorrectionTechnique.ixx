export module Engine.Rendering.GammaCorrectionTechnique;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SceneView;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class GammaCorrectionTechnique : public FullscreenTechnique
{
public:

	bool initialize(RenderLib::Context& context,
					std::shared_ptr<RenderLib::Texture2D> inputTexture);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

private:

	float mGamma{ 2.2 };

	RenderLib::Sampler* mInputTexture;
};

} // namespace Rendering

} // namespace Reef