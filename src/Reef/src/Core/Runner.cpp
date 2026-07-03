module;

#include <ranges>
#include <vector>
#include <memory>

module Engine.Runner;

import Log20;
import Engine.TypeRegistry;

import Common.SmartPointer;
//import Engine.ObjectFactory;

using namespace Reef;

bool
Application::run()
{
	//if (mIsRunning)
	//{
	//	return false;
	//}

	//mIsRunning = true;

	//while (!mShouldStop)
	//{
	//	std::ranges::reverse_view rv { mLayers };

	//	/*for (auto& layer : rv)
	//	{
	//		layer->beginFrame();
	//	}

	//	for (auto& layer : rv)
	//	{
	//		layer->update();
	//	}

	//	for (auto& layer : rv)
	//	{
	//		layer->endFrame();
	//	}

	//	for (auto& layer : rv)
	//	{
	//		layer->render();
	//	}*/
	//}

	//std::ranges::reverse_view rv { mLayers };

	////for (auto& layer : rv)
	////{
	////	layer->stop();
	////}

	//for (auto& layer : rv)
	//{
	//	layer->deinitialize();
	//}

	//mIsRunning = false;
	return true;
}





bool
Application::shouldStop()
{
	return mShouldStop;
}


ILayer*
Application::addLayer(const Type& type)
{
	if (!type.isSubclassOf(ILayer::classType()))
	{
		return nullptr;
	}

	auto ctor = TypeRegistry::constructor(type);

	if (!ctor)
	{
		return nullptr;
	}

	auto object = ctor();

	auto layer = Reef::Util::staticPointerCast<ILayer>(std::move(object));

	if (!layer)
	{
		return nullptr;
	}

	if (!layer->initialize(*this))
	{
		return nullptr;
	}

	auto& storedLayer = mLayers.emplace_back(std::move(layer));
	return storedLayer.get();
}


void 
Application::removeLayer(ILayer* layer)
{
	std::erase_if(mLayers, [=](const auto& l) { return l.get() == layer; });
}


ILayer*
Application::getLayer(const Type& type)
{
	for (auto& layer : mLayers)
	{
		if (layer->type().isSubclassOf(type))
		{
			return layer.get();
		}
	}

	return nullptr;
}
