module Engine.Application.Input;

//#include <Engine/System.hpp>

using namespace Reef;


class NullInputSystem : public InputSystem
{
public:

	KeyState getKeyState(Key key) const override
	{
		return KeyState::RELEASED;
	}

	KeyState getKeyState(const InputChord& chord) const override
	{
		return KeyState::RELEASED;
	}

	KeyState getMouseButtonState(MouseButton button) const  override
	{
		return KeyState::RELEASED;
	}

	Vec2 getMousePosition() const  override
	{
		return { 0, 0 };
	}

	void setMousePosition(const Vec2& normalizedPosition) override
	{

	}

	static NullInputSystem& instance()
	{
		static NullInputSystem sInstance;

		return sInstance;
	}
};


InputSystem* Input::sCurrentInputSystem = &NullInputSystem::instance();


KeyState
Input::getKeyState(Key key)
{
	return sCurrentInputSystem->getKeyState(key);
}


KeyState
Input::getKeyState(const InputChord& chord)
{
	return sCurrentInputSystem->getKeyState(chord);
}


KeyState
Input::getMouseButtonState(MouseButton button)
{
	return sCurrentInputSystem->getMouseButtonState(button);
}


Vec2
Input::getMousePosition()
{
	return sCurrentInputSystem->getMousePosition();
}


void
Input::setInputSystem(InputSystem& inputSystem)
{
	sCurrentInputSystem = &inputSystem;
}


void
Input::resetInputSystem()
{
	sCurrentInputSystem = &NullInputSystem::instance();
}


void
Input::setMousePosition(const Vec2& normalizedPosition)
{
	sCurrentInputSystem->setMousePosition(normalizedPosition);
}