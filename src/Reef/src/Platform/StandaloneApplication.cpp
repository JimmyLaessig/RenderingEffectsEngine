#include <Engine/Application/StandaloneApplication.hpp>

#include <Engine/Application/Application.hpp>

#include <Engine/Core/EngineImpl.hpp>
#include <ranges>
#include <vector>

using namespace Reef;


StandaloneApplication::StandaloneApplication()
{

}


std::unique_ptr<StandaloneApplication>
StandaloneApplication::create(const CommandLineArguments& arguments)
{
	std::unique_ptr<StandaloneApplication> app(new StandaloneApplication);

	app->mWindow = createWindow("", 1024, 768, false, false);
	app->mEngine = std::make_unique<EngineImpl>(*app->mWindow);

	return app;
}


void
StandaloneApplication::quit(ReturnCode returnCode)
{
	mReturnCode = returnCode;
}


bool
StandaloneApplication::isQuitting() const
{
	return mReturnCode.has_value();
}


Engine&
StandaloneApplication::engine()
{
	return *mEngine;
}


IWindow*
StandaloneApplication::window()
{
	return mWindow.get();
}


ReturnCode
StandaloneApplication::run()
{
	if (mIsRunning)
	{
		return ReturnCode::FAILURE;
	}

	mIsRunning = true;

	gameLoop();

	return mReturnCode.value_or(ReturnCode::FAILURE);
}


void
StandaloneApplication::gameLoop()
{
	while (true)
	{
		if (mWindow->shouldClose())
		{
			quit(ReturnCode::SUCCESS);
		}

		if (isQuitting())
		{
			break;
		}

		mEngine->updateFrame();
	}
}
