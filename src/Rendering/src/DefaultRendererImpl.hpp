#ifndef REEF_RENDERING_DEFAULTRENDERERIMPL_HPP
#define REEF_RENDERING_DEFAULTRENDERERIMPL_HPP

#include <Reef/Rendering/Renderer.hpp>

#include "ResourceManager.hpp"

#include "RenderObjectImpl.hpp"

#include "ShaderRegistry.hpp"

#include <Coral/Util/RAII.hpp>

#include <Reef/Util/Hive.hpp>

#include <unordered_map>

namespace Reef::Rendering
{

class DefaultRendererImpl : public Renderer
{
public:

	DefaultRendererImpl(void* nativeWindowHandle);

	RenderObject* createRenderObject() override;

	void destroyRenderObject(RenderObject* renderObject) override;

	void render(const CameraInfo& camera) override;

	ResourceManager& resourceManager();

	const ResourceManager& resourceManager() const;

	CoContext context() override;

	const CoContext context() const override;

private:

	Coral::ContextPtr mContext;
    Coral::SwapchainPtr mSwapchain;

	ResourceManager mResourceManager;

	ShaderManager mShaderManager;

	Reef::Util::Hive<RenderObjectImpl> mRenderObjects;

}; // class DefaultRendererImpl

} // namespace Reef::Rendering

#endif // !ENGINE_RENDERING_DEFAULTRENDERER_HPP
