module;

#include <cstdint>
#include <vector>

export module Engine.Rendering.DebugRenderer;

import Engine.Rendering.GBuffer;
import Engine.Rendering.GeometryRenderer;
import Engine.Rendering.SceneView;
import Engine.Rendering.FXAATechnique;
import Engine.Rendering.ToneMappingTechnique;
import Engine.Rendering.GammaCorrectionTechnique;
import Engine.Rendering.LightingPass;
import Engine.Rendering.Renderer;

import Engine.Component.MeshComponent;

import Engine.Camera;
import Engine.Material;
import Engine.Mesh;
import Engine.Scene;

import Singleton;

import RenderLib;

import Engine.Rendering.Renderer;

namespace Reef
{

namespace Rendering
{

class DebugRenderer
{
public:

	bool initialize(RenderLib::Context& context,
					uint32_t width, uint32_t height,
					RenderLib::Framebuffer& framebuffer);

	bool resize(uint32_t width, uint32_t height);

	bool wireframeOverlayEnabled() const;

	bool setWireframeOverlay(bool enable);

	void setSceneView(const SceneView& sceneView);

	void setSelection(const std::vector<MeshComponent*> meshes);

	RenderLib::CommandBuffer* recordRenderCommands();

private:

	//SceneView mSceneView;
	// 
	//void updateRenderResource();

	//std::shared_ptr<RenderLib::CommandBuffer> renderWireframeOverlay();

	//std::shared_ptr<RenderLib::CommandBuffer> renderSelectionOverlay();

	//std::shared_ptr<RenderLib::Framebuffer> mFramebuffer;

	//std::shared_ptr<RenderLib::PipelineState> mPipelineState;

	//std::shared_ptr<RenderLib::PipelineState> mSelectionPipelineState;

	//RenderLib::Sampler* mSelectionTexture;

	//RenderLib::Sampler* mSelectionDepthTexture;

	//std::shared_ptr<RenderLib::Framebuffer> mSelectionFramebuffer;

	//uint32_t mWidth;

	//uint32_t mHeight;

	//bool mDrawWireframeOverlay{ true };

	//Math::Vec4 mWireframeColor{ 0.f, 1.f, 1.f, 1.f};

	//std::vector<MeshComponent*> mSelectedMeshes;

	//Math::Vec4 mSelectionColor{ 0.9f, 0.6f, 0.05f, 1.f };

	//float mSelectionOutlineThickness{ 0.002f };
};

} // namespace Rendering

} // namespace Reef