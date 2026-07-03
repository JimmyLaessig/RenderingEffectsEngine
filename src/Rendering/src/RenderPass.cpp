#include <Engine/Rendering/RenderPass.hpp>

#include <Engine/Rendering/DefaultRenderer.hpp>

using namespace Reef::Rendering;

RenderPass::RenderPass(std::string_view name, DefaultRenderer& renderer)
	: mName(name)
	, mRenderer(renderer)
	, mRenderPassFinishedSemaphore(mRenderer.context().createSemaphore().value())
{
	mCommandBuffers.resize(mRenderer.canvas()->swapchain()->swapchainImageCount());
}


const std::string&
RenderPass::name()
{
	return mName;
}


void
RenderPass::onResolutionChanged(const glm::uvec2& resolution)
{
}


void
RenderPass::render(const SceneView& sceneView)
{
	auto& context = mRenderer.context();
	auto queue    = context.getGraphicsQueue();
	auto index    = mRenderer.canvas()->swapchain()->currentSwapchainImageIndex();

	Coral::CommandBufferCreateConfig config{};
	config.name            = name();
	mCommandBuffers[index] = queue->createCommandBuffer(config).value();
	auto commandBuffer     = mCommandBuffers[index].get();

	commandBuffer->begin();

	recordCommandBuffer(sceneView, *commandBuffer);

	commandBuffer->end();

	auto signalSemaphore = renderPassFinishedSemaphore();
	auto waitSemaphores  = renderPassReadySemaphores();

	Coral::CommandBufferSubmitInfo submitInfo{};
	submitInfo.signalSemaphores = std::span(&signalSemaphore, 1);
	submitInfo.waitSemaphores   = std::span(waitSemaphores);
	submitInfo.commandBuffers   = std::span(&commandBuffer, 1);
	queue->submit(submitInfo, nullptr);
}


DefaultRenderer&
RenderPass::renderer()
{
	return mRenderer;
}


Coral::Context&
RenderPass::context()
{
	return mRenderer.context();
}


Coral::Semaphore*
RenderPass::renderPassFinishedSemaphore()
{
	return mRenderPassFinishedSemaphore.get();
}


std::vector<Coral::Semaphore*>
RenderPass::renderPassReadySemaphores()
{
	std::vector<Coral::Semaphore*> semaphores;
	semaphores.reserve(mDependencies.size());

	for (auto& dependency : mDependencies)
	{
		semaphores.push_back(dependency->renderPassFinishedSemaphore());
	}

	return semaphores;
}


std::vector<RenderPass*>
RenderPass::dependencies()
{
	std::vector<RenderPass*> result;

	for (auto d : mDependencies)
	{
		result.push_back(d.get());
	}

	return result;
}