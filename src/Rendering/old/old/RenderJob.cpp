module Engine.Rendering.SceneRenderer;

import Engine.Component.CameraComponent;
import Engine.Component.MeshComponent;
import Engine.Component.SkyLightComponent;
import Engine.Component.DirectionalLightComponent;

import Engine.Rendering.ShaderRegistry;
import Engine.GameObject;
import Engine.Transform;
import Engine.Mesh;

import Engine.Rendering.RenderData;

import Math.Matrix;
import Engine.Rendering.SceneView;

import Rendering;

import <vector>;


using namespace Reef::Rendering;

namespace
{

void
addRenderObjects(Engine::GameObject& entity, 
				 const Math::Mat4& viewMatrix,
				 const Math::Mat4& projectionMatrix,
				 const Math::Mat4& viewProjectionMatrix, 
				 std::vector<Engine::Rendering::RenderObject>& results)
{
	auto localToWorlMatrix = entity.transform().localToWorldMatrix();
	auto worldToLocalMatrix = entity.transform().worldToLocalMatrix();
	Math::Mat3 normalMatrix = Math::inverse(Math::transpose(localToWorlMatrix));

	for (auto mc : entity.getComponents<Engine::MeshComponent>())
	{
		if (auto mesh = mc->mesh())
		{
			for (uint32_t i = 0; i < mesh->getNumPrimitives(); ++i)
			{
				auto primitive = mesh->getPrimitive(i);
				auto& ro = results.emplace_back();
				ro.primitive = primitive;
				ro.material = primitive->material();
				if (auto material = mc->material(i))
				{
					ro.material = material;
				}
				ro.localToWorldMatrix = localToWorlMatrix;
				ro.worldToLocalMatrix = worldToLocalMatrix;
				ro.normalMatrix		  = normalMatrix;
			}
		}
	}

	for (auto child : entity.children())
	{
		addRenderObjects(*child, viewMatrix, projectionMatrix, viewProjectionMatrix, results);
	}
}

} // namespace


bool
SceneRenderer::initialize(std::shared_ptr<::Rendering::Context> context, uint32_t width, uint32_t height)
{
	mContext = context;
	mQueue = ::Rendering::createCommandQueue(context, {});

	return Engine::Rendering::ShaderRegistry::initializeDefaultShaders(mContext) &&
		   mGeometryPipeline.initialize(mContext, width, height) &&
		   mLightingPass.initialize(mContext, mGeometryPipeline.gBuffer()) &&
		   mTonemappingTechnique.initialize(mContext, mLightingPass.framebuffer()->colorAttachment(0)) &&
		   mGammaCorrectionTechnique.initialize(mContext, mTonemappingTechnique.framebuffer()->colorAttachment(0)) &&
		   mFXAATechnique.initialize(mContext, mGammaCorrectionTechnique.framebuffer()->colorAttachment(0));
}


void
SceneRenderer::render(Scene& scene, std::shared_ptr<::Rendering::Framebuffer> framebuffer)
{
	SceneView view;

	view.gBuffer = mGeometryPipeline.gBuffer();
	auto cameraComponent = scene.findComponent<Engine::CameraComponent>();

	if (!cameraComponent)
	{
		return;
	}

	view.framebuffer = framebuffer;

	view.viewMatrix		= cameraComponent->viewMatrix();
	view.camera			= cameraComponent->camera();
	view.cameraPosition = cameraComponent->entity().transform().worldPosition();
	
	view.viewProjectionMatrix			= view.camera.projectionMatrix * view.viewMatrix;
	view.inverseViewProjectionMatrix	= Math::inverse(view.viewProjectionMatrix);

	for (auto light : scene.findComponents<Engine::DirectionalLightComponent>())
	{
		view.directionalLights.push_back(std::static_pointer_cast<DirectionalLight>(light->light()));
	}

	for (auto light : scene.findComponents<Engine::SkyLightComponent>())
	{
		view.skyLights.push_back(std::static_pointer_cast<SkyLight>(light->light()));
	}

	// Traverse the scene graph to collect all meshes
	// This performs view-frustum culling
	for (auto child : scene.entitys())
	{
		addRenderObjects(*child, view.viewMatrix, view.camera.projectionMatrix, view.viewProjectionMatrix, view.renderObjects);
	}

	render(view);
}


void 
SceneRenderer::updateRenderData(SceneView& view)
{
	std::vector<RenderData*> renderData;
	for (auto& ro : view.renderObjects)
	{
		renderData.push_back(&ro.primitive->RenderData());

		for (auto& [_, uniform] : ro.material->uniforms())
		{
			if (auto texture = std::get_if<std::shared_ptr<Texture>>(&uniform))
			{
				renderData.push_back(&(*texture)->RenderData());
			}
		}
	}

	for (auto& light : view.skyLights)
	{
		auto skyLightTexture = light->skyLightTexture();
		auto irradianceTexture = light->irradianceTexture();

		renderData.push_back(&(skyLightTexture->RenderData()));
		renderData.push_back(&(irradianceTexture->RenderData()));
	}


	for (auto& rd : renderData)
	{
		rd->update(mContext);
	}
}


void
SceneRenderer::render(SceneView& view)
{
	mContext->beginFrame();

	updateRenderData(view);

	mGeometryPipeline.submitCommandBuffer(view, *mQueue);
	mLightingPass.recordCommandBuffer(view, *mQueue);
	mTonemappingTechnique.recordCommandBuffer(view, *mQueue);
	mGammaCorrectionTechnique.recordCommandBuffer(view, *mQueue);
	mFXAATechnique.recordCommandBuffer(view, *mQueue);

	auto source = mLightingPass.framebuffer();
	auto target = view.framebuffer;

	auto presentCommandBuffer = ::Rendering::createCommandBuffer(mContext, { "Present command" });
	presentCommandBuffer->begin();

	presentCommandBuffer->blitFramebufferCommand(source,
												 target,
												 { 0, 0, source->width(), source->height() },
												 { 0, 0, target->width(), target->height() },
												 ::Rendering::BlitAttachment::COLOR);
	presentCommandBuffer->end();
	mQueue->submit(presentCommandBuffer);

	mQueue->execute();

	mContext->endFrame(nullptr);
}


void
SceneRenderer::resize(uint32_t width, uint32_t height)
{
	mGeometryPipeline.initialize(mContext, width, height);
	mLightingPass.initialize(mContext, mGeometryPipeline.gBuffer());
	mTonemappingTechnique.initialize(mContext, mLightingPass.framebuffer()->colorAttachment(0));
	mGammaCorrectionTechnique.initialize(mContext, mTonemappingTechnique.framebuffer()->colorAttachment(0));
	mFXAATechnique.initialize(mContext, mGammaCorrectionTechnique.framebuffer()->colorAttachment(0));
}