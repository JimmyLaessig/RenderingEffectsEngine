#ifndef REEF_EDITOR_EDITORAPPLICATION_HPP
#define REEF_EDITOR_EDITORAPPLICATION_HPP

#include <Editor/System.hpp>

#include <Engine/Core/Engine.hpp>

#include <Engine/Application/Application.hpp>

#include <Editor/SceneInspector.hpp>

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

class EDITOR_API EditorApplication : public Reef::Application
{
public:

	static std::unique_ptr<EditorApplication> create(const CommandLineArguments& arguments);

	void quit(ReturnCode exitCode) override;

	IWindow* window() override;

	ReturnCode run() override;

	bool isQuitting() const override;

	Engine& engine() override;

private:

	EditorApplication();

	void gameLoop();

	void updateGUI();

	CommandLineArguments mCommandLineArguments;

	std::unique_ptr<IWindow> mWindow;

	std::unique_ptr<Engine> mEngine;

	bool mIsRunning{ false };

	std::optional<ReturnCode> mReturnCode;

	SceneInspector mSceneInspector;

};

} // namespace Reef

#endif // !REEF_EDITOR_EDITORAPPLICATION_HPP