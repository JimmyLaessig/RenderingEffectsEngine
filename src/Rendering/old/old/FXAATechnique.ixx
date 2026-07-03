module;

#include <memory>

export module Engine.Rendering.FXAATechnique;

import Engine.Rendering.FullscreenTechnique;
import Engine.Rendering.SceneView;

import RenderLib;

namespace Reef
{

namespace Rendering
{

class FXAATechnique : public FullscreenTechnique
{
public:

	bool initialize(RenderLib::Context& context, 
					std::shared_ptr<RenderLib::Texture2D> inputTexture);

	std::shared_ptr<RenderLib::CommandBuffer> recordRenderCommands(SceneView& view);

private:

	RenderLib::Sampler* mInputTexture;
};

} // namespace Rendering

} // namespace Reef