#ifndef REEF_APPLICATION_STANDALONEAPPLICATION_HPP
#define REEF_APPLICATION_STANDALONEAPPLICATION_HPP

#include <Engine/System.hpp>
#include <Engine/Application/Application.hpp>

#include <Engine/Core/Engine.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <optional>
#include <vector>
#include <unordered_map>

namespace Reef
{

class ENGINE_API StandaloneApplication : public Application
{
public:

	static std::unique_ptr<StandaloneApplication> create(const CommandLineArguments& arguments);

	void quit(ReturnCode exitCode) override;

	IWindow* window() override;

	ReturnCode run() override;

	bool isQuitting() const override;

	Engine& engine() override;

private:

	StandaloneApplication();

	void gameLoop();

	CommandLineArguments mCommandLineArguments;

	std::unique_ptr<IWindow> mWindow;

	std::unique_ptr<Engine> mEngine;

	bool mIsRunning{ false };

	std::optional<ReturnCode> mReturnCode;

};

} // namespace Reef

#endif // !REEF_APPLICATION_STANDALONEAPPLICATION_HPP