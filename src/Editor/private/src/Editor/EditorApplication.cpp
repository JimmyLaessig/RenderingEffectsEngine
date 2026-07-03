#include <Editor/EditorApplication.hpp>

#include <Engine/SceneGraph/Scene.hpp>
#include <Engine/SceneGraph/Entity.hpp>
#include <Engine/Component/ScriptableComponent.hpp>

#include <Editor/Inspector.hpp>

#include <ranges>
#include <vector>

#include <imgui.h>
#include <iostream>

using namespace Reef;


constexpr std::string_view toString(Reef::Key key)
{
    switch (key)
    {
		case Key::SPACE:  return "SPACE";
		case Key::MINUS:  return "-";
		case Key::PERIOD: return ".";
		case Key::COMMA:  return ",";

		case Key::ZERO:   return "0";
		case Key::ONE:    return "1";
		case Key::TWO:    return "2";
		case Key::THREE:  return "3";
		case Key::FOUR:   return "4";
		case Key::FIVE:   return "5";
		case Key::SIX:    return "6";
		case Key::SEVEN:  return "7";
		case Key::EIGHT:  return "8";
		case Key::NINE:   return "9";

		case Key::A: return "A";
		case Key::B: return "B";
		case Key::C: return "C";
		case Key::D: return "D";
		case Key::E: return "E";
		case Key::F: return "F";
		case Key::G: return "G";
		case Key::H: return "H";
		case Key::I: return "I";
		case Key::J: return "J";
		case Key::K: return "K";
		case Key::L: return "L";
		case Key::M: return "M";
		case Key::N: return "N";
		case Key::O: return "O";
		case Key::P: return "P";
		case Key::Q: return "Q";
		case Key::R: return "R";
		case Key::S: return "S";
		case Key::T: return "T";
		case Key::U: return "U";
		case Key::V: return "V";
		case Key::W: return "W";
		case Key::X: return "X";
		case Key::Y: return "Y";
		case Key::Z: return "Z";

		case Key::ESCAPE:       return "ESC";
		case Key::RETURN:       return "ENTER";
		case Key::TAB:          return "TAB";
		case Key::BACKSPACE:    return "BACKSPACE";
		case Key::INSERT:       return "INSERT";
		case Key::DELETE:       return "DELETE";
		case Key::RIGHT:        return "RIGHT";
		case Key::LEFT:         return "LEFT";
		case Key::DOWN:         return "DOWN";
		case Key::UP:           return "UP";
		case Key::PAGE_UP:      return "PAGE_UP";
		case Key::PAGE_DOWN:    return "PAGE_DOWN";
		case Key::HOME:         return "HOME";
		case Key::END:          return "END";
		case Key::CAPS_LOCK:    return "CAPS_LOCK";
		case Key::SCROLL_LOCK:  return "SCROLL_LOCK";
		case Key::NUM_LOCK:     return "NUM_LOCK";
		case Key::PRINT_SCREEN: return "PRINT";
		case Key::PAUSE:        return "PAUSE";

		case Key::F1:  return "F1";
		case Key::F2:  return "F2";
		case Key::F3:  return "F3";
		case Key::F4:  return "F4";
		case Key::F5:  return "F5";
		case Key::F6:  return "F6";
		case Key::F7:  return "F7";
		case Key::F8:  return "F8";
		case Key::F9:  return "F9";
		case Key::F10: return "F10";
		case Key::F11: return "F11";
		case Key::F12: return "F12";
		case Key::F13: return "F13";
		case Key::F14: return "F14";
		case Key::F15: return "F15";
		case Key::F16: return "F16";
		case Key::F17: return "F17";
		case Key::F18: return "F18";
		case Key::F19: return "F19";
		case Key::F20: return "F20";
		case Key::F21: return "F21";
		case Key::F22: return "F22";
		case Key::F23: return "F23";
		case Key::F24: return "F24";

		case Key::NUMPAD_ZERO:  return "NUMPAD_0";
		case Key::NUMPAD_ONE:   return "NUMPAD_1";
		case Key::NUMPAD_TWO:   return "NUMPAD_2";
		case Key::NUMPAD_THREE: return "NUMPAD_3";
		case Key::NUMPAD_FOUR:  return "NUMPAD_4";
		case Key::NUMPAD_FIVE:  return "NUMPAD_5";
		case Key::NUMPAD_SIX:   return "NUMPAD_6";
		case Key::NUMPAD_SEVEN: return "NUMPAD_7";
		case Key::NUMPAD_EIGHT: return "NUMPAD_8";
		case Key::NUMPAD_NINE:  return "NUMPAD_9";

		case Key::NUMPAD_DECIMAL:  return "NUMPAD_DECIMAL"; 
		case Key::NUMPAD_DIVIDE:   return "NUMPAD_DIVIDE";  
		case Key::NUMPAD_MULTIPLY: return "NUMPAD_MULTIPLY";
		case Key::NUMPAD_SUBTRACT: return "NUMPAD_SUBTRACT";
		case Key::NUMPAD_ADD:      return "NUMPAD_ADD";     

		case Key::LEFT_SHIFT:    return "LSHIFT";
		case Key::LEFT_CONTROL:  return "LCTRL";
		case Key::LEFT_ALT:      return "LALT";
		case Key::LEFT_SUPER:    return "LSUPER";
		case Key::RIGHT_SHIFT:   return "RSHIFT";
		case Key::RIGHT_CONTROL: return "RCTRL";
		case Key::RIGHT_ALT:     return "RALT";
		case Key::RIGHT_SUPER:   return "RSUPER";

		case Key::CARET:        return "^";
		case Key::ESZETT:       return "SZ";
		case Key::ACUTE_ACCENT: return "ACUTE_ACCENT";
		case Key::UE:           return "UE";
		case Key::PLUS:         return "+";
		case Key::OE:           return "OE";
		case Key::AE:           return "AE";
		case Key::HASH:         return "#";
		case Key::LESS_THAN:    return "<";

		case Key::LEFT_BRACKET:  return "[";
		case Key::RIGHT_BRACKET: return "]";
		case Key::GRAVE_ACCENT:  return "GRAVE_ACCENT";
		case Key::BACKSLASH:     return "\\";
		case Key::SLASH:         return "/";
		case Key::SEMICOLON:     return ";";
		case Key::EQUAL:         return "=";
		case Key::APOSTROPHE:    return "`";
    }

    assert(false);
    return "unknown";
}


EditorApplication::EditorApplication()
{

}


std::unique_ptr<EditorApplication>
EditorApplication::create(const CommandLineArguments& arguments)
{
	std::unique_ptr<EditorApplication> app(new EditorApplication);

	app->mWindow = createWindow("", 1024, 768, false, false);
	app->mEngine = Engine::createEngine(*app->mWindow);

	return app;
}


void
EditorApplication::quit(ReturnCode returnCode)
{
	mReturnCode = returnCode;
}


bool
EditorApplication::isQuitting() const
{
	return mReturnCode.has_value();
}


Engine&
EditorApplication::engine()
{
	return *mEngine;
}


IWindow*
EditorApplication::window()
{
	return mWindow.get();
}


ReturnCode
EditorApplication::run()
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
EditorApplication::gameLoop()
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
		updateGUI();

	}
}


void
EditorApplication::updateGUI()
{
	//auto scene = mEngine->activeScene();

	//if (!scene)
	//{
	//	return;
	//}


	//if (ImGui::Begin("SceneInspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	//{
	//	mSceneInspector.inspect(*scene);
	//}

	//ImGui::End();
}
