module;

#include <stb_image.h>

#include <cassert>
#include <filesystem>
#include <span>

module Engine.TextureFactory;

namespace
{

template<typename T>
Reef::TextureFormat
getTextureFormat(uint32_t numChannels)
{
	//static_assert(false);
	return {};
}


template<>
Reef::TextureFormat
getTextureFormat<uint8_t>(uint32_t numChannels)
{
	switch (numChannels)
	{
		case 1:	return Reef::TextureFormat::R_8U;
		case 2:	return Reef::TextureFormat::RG_8U;
		case 3:	return Reef::TextureFormat::RGB_8U;
		case 4:	return Reef::TextureFormat::RGBA_8U;
		default:
			break;
	}

	assert(false);
	return Reef::TextureFormat::RGBA_8U;
}


template<>
Reef::TextureFormat
getTextureFormat<float>(uint32_t numChannels)
{
	switch (numChannels)
	{
		case 1:	return Reef::TextureFormat::R_32F;
		case 2:	return Reef::TextureFormat::RG_32F;
		case 3:	return Reef::TextureFormat::RGB_32F;
		case 4:	return Reef::TextureFormat::RGBA_32F;
		default:
			break;
	}

	assert(false);
	return Reef::TextureFormat::RGBA_8U;
}

} // namespace


using namespace Reef;


std::shared_ptr<Texture>
TextureFactory::createTexture(std::string_view path, bool flipVertically)
{
	if (!std::filesystem::exists(path))
	{
		return nullptr;
	}

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::string pathString(path.begin(), path.end());

	stbi_set_flip_vertically_on_load_thread(flipVertically);
	if (stbi_is_hdr(pathString.c_str()) == 0)
	{
		int x, y, c;
		auto data = stbi_load(pathString.c_str(), &x, &y, &c, 0);

		if (data == nullptr)
		{
			return nullptr;
		}
		
		auto textureFormat = getTextureFormat<uint8_t>(c);
		texture->set(x, y, textureFormat, { (std::byte*)data, x * y * Reef::sizeInBytes(textureFormat) });

		stbi_image_free(data);
	}
	else
	{
		int x, y, c;
		auto data = stbi_loadf(pathString.c_str(), &x, &y, &c, 0);
		
		if (data == nullptr)
		{
			return nullptr;
		}

		auto textureFormat = getTextureFormat<float>(c);
		texture->set(x, y, textureFormat, { (std::byte*)data, x * y * Reef::sizeInBytes(textureFormat) });

		stbi_image_free(data);
	}

	return texture;
}
