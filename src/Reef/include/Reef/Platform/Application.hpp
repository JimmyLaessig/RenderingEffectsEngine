#ifndef REEF_PLATFORM_APPLICATION_HPP
#define REEF_PLATFORM_APPLICATION_HPP

#include <Reef/Export.hpp>
#include <Reef/Core/SceneManager.hpp>
#include <Reef/Platform/WindowManager.hpp>
#include <Reef/Core/UserData.hpp>

#include <Reef/Platform/CommandLineArguments.hpp>

#include <memory>

#include <Reef/Core/Event.hpp>

namespace Reef
{

enum class ReturnCode
{
	SUCCESS = 0,
	FAILURE = 1,
};


class REEF_API Application
{
public:

	virtual ~Application() = default;

	virtual const SceneManager& sceneManager() const = 0;

	virtual SceneManager& sceneManager() = 0;

	virtual const WindowManager& windowManager() const = 0;

	virtual WindowManager& windowManager() = 0;

	virtual ReturnCode run() = 0;

	virtual void quit(ReturnCode returnCode) = 0;

	virtual bool isQuitting() const = 0;

	virtual void addUserData(std::shared_ptr<UserData> userData) = 0;

	virtual void removeUserData(UserData* userData) = 0;

	virtual const CommandLineArguments& commandLineArguments() const = 0;

}; // class Application

template<typename T>
struct Deleter
{
	void operator()(T* ptr) const
	{
		destroy(ptr);
    }

}; // Deleter

using ApplicationPtr = std::unique_ptr<Application, Deleter<Application>>;

ApplicationPtr createApplication(const CommandLineArguments& args);

void destroy(Application* application);

} // namespace Reef

#endif // !REEF_PLATFORM_APPLICATION_HPP
