#include <Engine/Rendering/GeometryPass.hpp>

#include <Engine/Rendering/DefaultRenderer.hpp>

#include <array>

using namespace Reef::Rendering;


GeometryPass::GeometryPass(DefaultRenderer& renderer)
	: RenderPass("GeometryPass", renderer)
{
}


GeometryPass::SceneViewResolved
GeometryPass::updateResources(const SceneView& sceneView)
{
	auto& context		  = renderer().context();
	auto& resourceManager = renderer().resourceManager();

	auto viewMatrix       = sceneView.viewMatrix;
	auto projectionMatrix = sceneView.camera.projectionMatrix();

	if (!mPerFrameDataUniformBuffer)
	{
		mPerFrameDataUniformBuffer = UniformBuffer::create(Reef::Rendering::FrameData::UniformBlockDefinition, context);
	}

	mPerFrameDataUniformBuffer->setMat44F("viewMatrix", viewMatrix);
	mPerFrameDataUniformBuffer->setMat44F("projectionMatrix", projectionMatrix);
	mPerFrameDataUniformBuffer->setMat44F("viewProjectionMatrix", projectionMatrix * viewMatrix);
	mPerFrameDataUniformBuffer->flush();

	SceneViewResolved res;

	auto resolveRenderObject = [&](const RenderObject& ro)
	{
		RenderObjectResolved res;
		res.materialFunctionResource = resourceManager.getResource(static_cast<const MaterialFunctionImpl&>(*ro.material->materialFunction()));
		res.materialResource         = resourceManager.getResource(*ro.material);
		res.primitive		         = resourceManager.getResource(*ro.primitive);
		res.transformResouce         = resourceManager.getResource(ro.transform);

		return res;
	};

	res.renderObjects.reserve(sceneView.renderObjects.size());

	for (const auto& ro : sceneView.renderObjects)
	{
		if (!ro.primitive || !ro.material)
		{
			continue;
		}

		res.renderObjects.push_back(resolveRenderObject(ro));
	}

	auto resolution = sceneView.camera.resolution();
	if (!mFramebuffer || mFramebuffer->width() != resolution.x || mFramebuffer->height() != resolution.y)
	{
		Coral::ImageCreateConfig config{};
		config.format     = Coral::PixelFormat::RGBA8_SRGB;
		config.width      = resolution.x;
		config.height     = resolution.y;;
		config.hasMipMaps = false;
		mColorImage       = context.createImage(config).value();

		config.format = Coral::PixelFormat::DEPTH24_STENCIL8;
		mDepthImage   = context.createImage(config).value();

		std::array<Coral::ColorAttachment, 1> colorAttachments = { Coral::ColorAttachment{ 0, mColorImage.get() } };

		Coral::FramebufferCreateConfig framebufferConfig{};
		framebufferConfig.colorAttachments = colorAttachments;
		framebufferConfig.depthAttachment = Coral::DepthAttachment{ mDepthImage.get() };

		mFramebuffer = context.createFramebuffer(framebufferConfig).value();
	}

	return res;
}


void
GeometryPass::recordCommandBuffer(const SceneView& view, 
	                              Coral::CommandBuffer& commandBuffer)
{
	auto resolution   = view.camera.resolution();
	auto viewResolved = updateResources(view);
	auto& context     = renderer().context();

	Coral::ClearColor clearColor = { 0, Coral::ClearOp::CLEAR, { view.clearColor.r, view.clearColor.g, view.clearColor.b, 1.f } };
	Coral::ClearDepth clearDepth = { Coral::ClearOp::CLEAR, 1.f, 0 };

	Coral::BeginRenderPassInfo beginRenderPassInfo{};
	beginRenderPassInfo.framebuffer = mFramebuffer.get();
	beginRenderPassInfo.clearColor  = { &clearColor, 1 };
	beginRenderPassInfo.clearDepth  = clearDepth;
	
	commandBuffer.cmdBeginRenderPass(beginRenderPassInfo);
	commandBuffer.cmdSetViewport({ 0, 0, mFramebuffer->width(), mFramebuffer->height(), 0.f, 1.f, Coral::ViewportMode::Y_UP });

	for (auto ro : viewResolved.renderObjects)
	{
		ro.materialFunctionResource->bind(commandBuffer);
		ro.materialResource->bind(commandBuffer);
		ro.transformResouce->bind(commandBuffer);
		
		commandBuffer.cmdBindDescriptor(mPerFrameDataUniformBuffer->buffer(), FrameData::Binding);

		ro.primitive->bind(commandBuffer);

		Coral::DrawIndexInfo drawInfo{};
		drawInfo.firstIndex = 0;
		drawInfo.indexCount = ro.primitive->indexCount();
		commandBuffer.cmdDrawIndexed(drawInfo);
	}

	commandBuffer.cmdEndRenderPass();
}
