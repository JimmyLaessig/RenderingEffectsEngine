export module Engine.Rendering.SceneRenderer;

import Engine.Rendering.GBuffer;
import Engine.Rendering.GeometryPass;
import Engine.Rendering.SceneView;
import Engine.Rendering.FXAATechnique;
import Engine.Rendering.ToneMappingTechnique;
import Engine.Rendering.GammaCorrectionTechnique;
import Engine.Rendering.LightingPass;

import Engine.Camera;
import Engine.Material;
import Engine.Mesh;
import Engine.Scene;

import Singleton;

import Rendering;

import <memory>;
import <vector>;

namespace Reef
{

namespace Rendering
{

class RenderJob
{
public:

	virtual bool initialize(std::shared_ptr<::Rendering::Context> context) = 0;

	virtual void enqueueRenderCommands(::Rendering::CommandQueue& commandQueue) = 0;

	std::shared_ptr<::Rendering::Context> context() { return mContext; }

private:

	std::shared_ptr<::Rendering::Context> mContext;
};

class Renderer : public Base::Singleton<Renderer>
{
public:

	bool initialize(std::shared_ptr<::Rendering::Context> mContext);

	bool isInitialized();

	void enqueueRenderJob(std::shared_ptr<RenderJob> job);

	void execute();

private:

	bool mIsInitialized{ false };

	std::shared_ptr<::Rendering::Context> mContext;

	std::shared_ptr<::Rendering::CommandQueue> mQueue;

	std::vector<std::shared_ptr<RenderJob>> mRenderJobs;
};


class SceneRenderJob : public RenderJob
{
public:

	SceneRenderJob(Scene& scene);

	bool initialize(std::shared_ptr<::Rendering::Context> mContext) override;

	void enqueueRenderCommands(::Rendering::CommandQueue& commandQueue) override;

	void render(Engine::Scene& scene, std::shared_ptr<::Rendering::Framebuffer> framebuffer);

	void resize(uint32_t width, uint32_t height);

private:

	void updateRenderData(SceneView& view);

	void render(SceneView& view);

	Scene& mScene;

	GeometryPass mGeometryPipeline;

	LightingPass mLightingPass;

	ToneMappingTechnique mTonemappingTechnique;

	GammaCorrectionTechnique mGammaCorrectionTechnique;

	FXAATechnique mFXAATechnique;

	std::shared_ptr<::Rendering::CommandBuffer> mPresentCommandBuffer;
};

} // namespace Rendering

} // namespace Reef