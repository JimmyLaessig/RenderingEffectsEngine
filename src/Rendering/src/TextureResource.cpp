#include <Engine/Rendering/TextureResource.hpp>

#include <glm/glm.hpp>

#include <cassert>
#include <vector>
#include <memory>
#include <span>

using namespace Reef::Rendering;

namespace
{

Coral::PixelFormat
convert(Reef::TextureFormat format)
{
	switch (format)
	{
		case Reef::TextureFormat::R_8U:		 return Coral::PixelFormat::R8_UI;
		case Reef::TextureFormat::RG_8U:	 return Coral::PixelFormat::RG8_UI;
		case Reef::TextureFormat::RGB_8U:	 return Coral::PixelFormat::RGB8_UI;
		case Reef::TextureFormat::RGBA_8U:	 return Coral::PixelFormat::RGBA8_UI;
		case Reef::TextureFormat::R_16F:	 return Coral::PixelFormat::R16_F;
		case Reef::TextureFormat::RG_16F:	 return Coral::PixelFormat::RG16_F;
		case Reef::TextureFormat::RGB_16F:	 return Coral::PixelFormat::RGB16_F;
		case Reef::TextureFormat::RGBA_16F:	 return Coral::PixelFormat::RGBA16_F;
		case Reef::TextureFormat::R_32F:	 return Coral::PixelFormat::R32_F;
		case Reef::TextureFormat::RG_32F:	 return Coral::PixelFormat::RG32_F;
		case Reef::TextureFormat::RGB_32F:	 return Coral::PixelFormat::RGB32_F;
		case Reef::TextureFormat::RGBA_32F:	 return Coral::PixelFormat::RGBA32_F;
		case Reef::TextureFormat::DEPTH_32F: return Coral::PixelFormat::DEPTH32_F;
	}

	assert(false);
	return Coral::PixelFormat::RGBA8_UI;
}

} // namespace


TextureResource::TextureResource(ResourceManager& resourceManager)
	: RenderResource(resourceManager)
{}


Coral::Sampler*
TextureResource::sampler()
{
	return mSampler.get();
}


Coral::Image*
TextureResource::texture()
{
	return mTexture.get();
}


bool
TextureResource::update(const Reef::TextureImpl& texture, Coral::Context& context)
{
	if (!shouldUpdate(texture.version()))
	{
		return true;
	}

	Coral::ImageCreateConfig imageConfig{};
	imageConfig.format     = convert(texture.format());
	imageConfig.width      = texture.width();
	imageConfig.height     = texture.height();
	imageConfig.hasMipMaps = texture.hasMipmaps();
	mTexture = context.createImage(imageConfig).value();
	
	if (!mTexture)
	{
		return false;
	}

	Coral::SamplerCreateConfig samplerConfig{};
	mSampler = context.createSampler(samplerConfig).value();

	if (!mSampler)
	{
		return false;
	}

	auto queue = context.getTransferQueue();

	Coral::CommandBufferCreateConfig commandBufferConfig{};
	commandBufferConfig.name = "Update texture resource";

	auto commandBuffer = queue->createCommandBuffer(commandBufferConfig).value();
	auto comamndBufferPtr = commandBuffer.get();

	commandBuffer->begin();

	Coral::UpdateImageDataInfo info{};
	info.data		= texture.pixelData();
	info.image		= mTexture.get();

	commandBuffer->cmdUpdateImageData(info);
	commandBuffer->cmdGenerateMipMaps(mTexture.get());
	commandBuffer->end();
	auto fence = context.createFence().value();

	Coral::CommandBufferSubmitInfo submitInfo{};
	submitInfo.commandBuffers = { &comamndBufferPtr , 1 };
	queue->submit(submitInfo, fence.get());
	fence->wait();

	return true;
}
