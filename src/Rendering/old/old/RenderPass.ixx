#ifndef ENGINE_RENDERING_ENVIRONMENTLIGHTPASS_H_
#define ENGINE_RENDERING_ENVIRONMENTLIGHTPASS_H_

#include <Engine/System.hpp>

#include "CalculateIrradiancePass.h"


#include <memory>
#include <optional>

namespace Rendering
{
	class Context;
	class Framebuffer;
	class CommandBuffer;
	class CommandQueue;
	class Texture2D;
} // namespace Rendering

namespace Reef
{

namespace Rendering
{

struct GBuffer;


class ENGINE_API EnvironmentLightPass: public FullscreenPass
{
public:

	bool init(std::shared_ptr<::Rendering::Context> mContext, 
			  GBuffer& gBuffer, 
			  std::shared_ptr<::Rendering::Texture2D> environmentTexture, 
			  uint32_t width, uint32_t height);

private:

	std::optional<CalculateIrradiancePass> mCalculateIrradiancePass;

	std::shared_ptr<::Rendering::Sampler> mIrradianceTexture;

	std::shared_ptr<::Rendering::Sampler> mEnvironmentTexture;

};

} // namespace Rendering

} // namespace Reef

#endif // !ENGINE_RENDERING_ENVIRONMENTLIGHTPASS_H_