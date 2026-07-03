#ifndef REEF_APPLICATIONIMPL_HPP
#define REEF_APPLICATIONIMPL_HPP

#include <Reef/Platform/Application.hpp>

#include "WindowManagerImpl.hpp"

#include "Core/SceneManagerImpl.hpp"

#include <memory>
#include <optional>

namespace Reef
{

class ApplicationImpl : public Application
{
public:

    ApplicationImpl(const CommandLineArguments& args);

    const SceneManager& sceneManager() const override;

    SceneManager& sceneManager() override;

    const WindowManager& windowManager() const override;

    WindowManager& windowManager() override;

    ReturnCode run() override;

    void quit(ReturnCode returnCode) override;

    bool isQuitting() const override;

    void addUserData(std::shared_ptr<UserData> userData) override;

    void removeUserData(UserData* userData) override;

    const CommandLineArguments& commandLineArguments() const override;

    void tick();

private:

    WindowManagerImpl mWindowManager;
     
    SceneManagerImpl mSceneManager;

    std::optional<ReturnCode> mReturnCode;

    bool mQuitAfterLastWindowClosed = true;

    std::vector<std::shared_ptr<UserData>> mUserData;

    CommandLineArguments mCommandLineArguments;

}; // class Application

} // namespace Reef

#endif // !REEF_APPLICATIONIMPL_HPP
