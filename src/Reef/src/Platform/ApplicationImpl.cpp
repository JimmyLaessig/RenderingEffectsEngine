#include "ApplicationImpl.hpp"

#include <Reef/Util/Constants.hpp>

using namespace Reef;


ApplicationImpl::ApplicationImpl(const CommandLineArguments& args)
    : mCommandLineArguments(args)
    , mSceneManager(*this)
    , mWindowManager(*this)
{
}


ApplicationPtr
Reef::createApplication(const CommandLineArguments& args)
{
    return ApplicationPtr{ new ApplicationImpl(args) };
}


void
Reef::destroy(Application* application)
{
    delete application;
}


const SceneManager&
ApplicationImpl::sceneManager() const
{
    return mSceneManager;
}


SceneManager&
ApplicationImpl::sceneManager()
{
    return mSceneManager;
}


const WindowManager&
ApplicationImpl::windowManager() const
{
    return mWindowManager;
}

WindowManager&
ApplicationImpl::windowManager()
{
    return mWindowManager;
}


ReturnCode
ApplicationImpl::run()
{
    Timestamp previous = std::chrono::high_resolution_clock::now();

    while (!mReturnCode.has_value())
    {
        auto now       = std::chrono::high_resolution_clock::now();
        auto deltaTime = static_cast<double>((now - previous).count()) * Reef::Util::Constants<double>::NANOSECONDS_TO_SECONDS;
        FrameTime frameTime{ now, previous, deltaTime };

        mWindowManager.processEvents();
        mSceneManager.tick(frameTime);

        previous = now;
    }

    return mReturnCode.value();
}

 
void
ApplicationImpl::quit(ReturnCode returnCode)
{
    mReturnCode = returnCode;
}


bool
ApplicationImpl::isQuitting() const
{
    return mReturnCode.has_value();
}


void
ApplicationImpl::addUserData(std::shared_ptr<UserData> userData)
{
    mUserData.push_back(userData);
}


void
ApplicationImpl::removeUserData(UserData* userData)
{
    std::erase_if(mUserData, [&](const std::shared_ptr<UserData>& data)
    {
        return data.get() == userData;
    });
}


const CommandLineArguments&
ApplicationImpl::commandLineArguments() const
{
    return mCommandLineArguments;
}
