module;

#include <cassert>
#include <memory>
#include <string_view>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#pragma warning( push )
#pragma warning (disable: 4005)
#include <GLFW/glfw3native.h>
#pragma warning( pop )
#undef DELETE

module Engine.Application.WindowImpl;

namespace
{
//int convert(Key key)
//{
//	switch (key)
//	{
//		case Key::SPACE:			return GLFW_KEY_SPACE;
//		case Key::APOSTROPHE:		return GLFW_KEY_APOSTROPHE;
//		case Key::COMMA:			return GLFW_KEY_COMMA;
//		case Key::MINUS:			return GLFW_KEY_MINUS;
//		case Key::PERIOD:			return GLFW_KEY_PERIOD;
//		case Key::SLASH:			return GLFW_KEY_SLASH;
//		case Key::ZERO:				return GLFW_KEY_0;
//		case Key::ONE:				return GLFW_KEY_1;
//		case Key::TWO:				return GLFW_KEY_2;
//		case Key::THREE:			return GLFW_KEY_3;
//		case Key::FOUR:				return GLFW_KEY_4;
//		case Key::FIVE:				return GLFW_KEY_5;
//		case Key::SIX:				return GLFW_KEY_6;
//		case Key::SEVEN:			return GLFW_KEY_7;
//		case Key::EIGHT:			return GLFW_KEY_8;
//		case Key::NINE:				return GLFW_KEY_9;
//		case Key::SEMICOLON:		return GLFW_KEY_SEMICOLON;
//		case Key::EQUAL:			return GLFW_KEY_EQUAL;
//		case Key::A:				return GLFW_KEY_A;
//		case Key::B:				return GLFW_KEY_B;
//		case Key::C:				return GLFW_KEY_C;
//		case Key::D:				return GLFW_KEY_D;
//		case Key::E:				return GLFW_KEY_E;
//		case Key::F:				return GLFW_KEY_F;
//		case Key::G:				return GLFW_KEY_G;
//		case Key::H:				return GLFW_KEY_H;
//		case Key::I:				return GLFW_KEY_I;
//		case Key::J:				return GLFW_KEY_J;
//		case Key::K:				return GLFW_KEY_K;
//		case Key::L:				return GLFW_KEY_L;
//		case Key::M:				return GLFW_KEY_M;
//		case Key::N:				return GLFW_KEY_N;
//		case Key::O:				return GLFW_KEY_O;
//		case Key::P:				return GLFW_KEY_P;
//		case Key::Q:				return GLFW_KEY_Q;
//		case Key::R:				return GLFW_KEY_R;
//		case Key::S:				return GLFW_KEY_S;
//		case Key::T:				return GLFW_KEY_T;
//		case Key::U:				return GLFW_KEY_U;
//		case Key::V:				return GLFW_KEY_V;
//		case Key::W:				return GLFW_KEY_W;
//		case Key::X:				return GLFW_KEY_X;
//		case Key::Y:				return GLFW_KEY_Y;
//		case Key::Z:				return GLFW_KEY_Z;
//		case Key::LEFT_BRACKET:		return GLFW_KEY_LEFT_BRACKET;
//		case Key::BACKSLASH:		return GLFW_KEY_BACKSLASH;
//		case Key::RIGHT_BRACKET:	return GLFW_KEY_RIGHT_BRACKET;
//		case Key::GRAVE_ACCENT:		return GLFW_KEY_GRAVE_ACCENT;
//		case Key::WORLD_1:			return GLFW_KEY_WORLD_1;
//		case Key::WORLD_2:			return GLFW_KEY_WORLD_2;
//
//		case Key::ESCAPE:			return GLFW_KEY_ESCAPE;
//		case Key::ENTER:			return GLFW_KEY_ENTER;
//		case Key::TAB:				return GLFW_KEY_TAB;
//		case Key::BACKSPACE:		return GLFW_KEY_BACKSPACE;
//		case Key::INSERT:			return GLFW_KEY_INSERT;
//		case Key::DELETE:			return GLFW_KEY_DELETE;
//		case Key::RIGHT:			return GLFW_KEY_RIGHT;
//		case Key::LEFT:				return GLFW_KEY_LEFT;
//		case Key::DOWN:				return GLFW_KEY_DOWN;
//		case Key::UP:				return GLFW_KEY_UP;
//		case Key::PAGE_UP:			return GLFW_KEY_PAGE_UP;
//		case Key::PAGE_DOWN:		return GLFW_KEY_PAGE_DOWN;
//		case Key::HOME:				return GLFW_KEY_HOME;
//		case Key::END:				return GLFW_KEY_END;
//		case Key::CAPS_LOCK:		return GLFW_KEY_CAPS_LOCK;
//		case Key::SCROLL_LOCK:		return GLFW_KEY_SCROLL_LOCK;
//		case Key::NUM_LOCK:			return GLFW_KEY_NUM_LOCK;
//		case Key::PRINT_SCREEN:		return GLFW_KEY_PRINT_SCREEN;
//		case Key::PAUSE:			return GLFW_KEY_PAUSE;
//		case Key::F1:				return GLFW_KEY_F1;
//		case Key::F2:				return GLFW_KEY_F2;
//		case Key::F3:				return GLFW_KEY_F3;
//		case Key::F4:				return GLFW_KEY_F4;
//		case Key::F5:				return GLFW_KEY_F5;
//		case Key::F6:				return GLFW_KEY_F6;
//		case Key::F7:				return GLFW_KEY_F7;
//		case Key::F8:				return GLFW_KEY_F8;
//		case Key::F9:				return GLFW_KEY_F9;
//		case Key::F10:				return GLFW_KEY_F10;
//		case Key::F11:				return GLFW_KEY_F11;
//		case Key::F12:				return GLFW_KEY_F12;
//		case Key::F13:				return GLFW_KEY_F13;
//		case Key::F14:				return GLFW_KEY_F14;
//		case Key::F15:				return GLFW_KEY_F15;
//		case Key::F16:				return GLFW_KEY_F16;
//		case Key::F17:				return GLFW_KEY_F17;
//		case Key::F18:				return GLFW_KEY_F18;
//		case Key::F19:				return GLFW_KEY_F19;
//		case Key::F20:				return GLFW_KEY_F20;
//		case Key::F21:				return GLFW_KEY_F21;
//		case Key::F22:				return GLFW_KEY_F22;
//		case Key::F23:				return GLFW_KEY_F23;
//		case Key::F24:				return GLFW_KEY_F24;
//		case Key::F25:				return GLFW_KEY_F25;
//		case Key::KP_ZERO:			return GLFW_KEY_KP_0;
//		case Key::KP_ONE:			return GLFW_KEY_KP_1;
//		case Key::KP_TWO:			return GLFW_KEY_KP_2;
//		case Key::KP_THREE:			return GLFW_KEY_KP_3;
//		case Key::KP_FOUR:			return GLFW_KEY_KP_4;
//		case Key::KP_FIVE:			return GLFW_KEY_KP_5;
//		case Key::KP_SIX:			return GLFW_KEY_KP_6;
//		case Key::KP_SEVEN:			return GLFW_KEY_KP_7;
//		case Key::KP_EIGHT:			return GLFW_KEY_KP_8;
//		case Key::KP_NINE:			return GLFW_KEY_KP_9;
//		case Key::KP_DECIMAL:		return GLFW_KEY_KP_DECIMAL;
//		case Key::KP_DIVIDE:		return GLFW_KEY_KP_DIVIDE;
//		case Key::KP_MULTIPLY:		return GLFW_KEY_KP_MULTIPLY;
//		case Key::KP_SUBTRACT:		return GLFW_KEY_KP_SUBTRACT;
//		case Key::KP_ADD:			return GLFW_KEY_KP_ADD;
//		case Key::KP_ENTER:			return GLFW_KEY_KP_ENTER;
//		case Key::KP_EQUAL:			return GLFW_KEY_KP_EQUAL;
//		case Key::LEFT_SHIFT:		return GLFW_KEY_LEFT_SHIFT;
//		case Key::LEFT_CONTROL:		return GLFW_KEY_LEFT_CONTROL;
//		case Key::LEFT_ALT:			return GLFW_KEY_LEFT_ALT;
//		case Key::LEFT_SUPER:		return GLFW_KEY_LEFT_SUPER;
//		case Key::RIGHT_SHIFT:		return GLFW_KEY_RIGHT_SHIFT;
//		case Key::RIGHT_CONTROL:	return GLFW_KEY_RIGHT_CONTROL;
//		case Key::RIGHT_ALT:		return GLFW_KEY_RIGHT_ALT;
//		case Key::RIGHT_SUPER:		return GLFW_KEY_RIGHT_SUPER;
//		case Key::MENU:				return GLFW_KEY_MENU;
//		case Key::UNKNOWN:			return GLFW_KEY_UNKNOWN;
//	}
//
//	assert(false);
//	return 0;
//}


//int convert(MouseButton button)
//{
//	switch (button)
//	{
//		case MouseButton::BUTTON_1:	return GLFW_MOUSE_BUTTON_1;
//		case MouseButton::BUTTON_2:	return GLFW_MOUSE_BUTTON_2;
//		case MouseButton::BUTTON_3:	return GLFW_MOUSE_BUTTON_3;
//		case MouseButton::BUTTON_4:	return GLFW_MOUSE_BUTTON_4;
//		case MouseButton::BUTTON_5:	return GLFW_MOUSE_BUTTON_5;
//		case MouseButton::BUTTON_6:	return GLFW_MOUSE_BUTTON_6;
//		case MouseButton::BUTTON_7:	return GLFW_MOUSE_BUTTON_7;
//		case MouseButton::BUTTON_8:	return GLFW_MOUSE_BUTTON_8;
//	}
//
//	assert(false);
//	return 0;
//}
//
//
//KeyState toKeyState(int keyState)
//{
//	switch (keyState)
//	{
//		case GLFW_PRESS:	return KeyState::PRESSED;
//		case GLFW_RELEASE:	return KeyState::RELEASED;
//		case GLFW_REPEAT:	return KeyState::REPEAT;	
//	}
//	assert(false);
//	return KeyState::RELEASED;
//}

} // namespace

using namespace Reef;


std::unique_ptr<WindowImpl>
WindowImpl::create(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar)
{
	if (glfwInit() == GLFW_FALSE)
	{
		return nullptr;
	}
//
//#if _DEBUG
//	// Create a debug Vulkan context or tell your Vulkan library (GLFW, SDL) to do so.
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
//#endif
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//	// Set window hints
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_REFRESH_RATE, 60);
//	glfwWindowHint(GLFW_DEPTH_BITS, 32);

	auto window = std::unique_ptr<WindowImpl>(new WindowImpl);
	window->mTitle = title;
	window->mWindowHandle = glfwCreateWindow(width, height, window->mTitle.c_str(), nullptr, nullptr);

	if (!window->mWindowHandle)
	{
		return nullptr;
	}

	//Coral::ContextConfig config{};
	//config.graphicsAPI	= Coral::GraphicsAPI::VULKAN;
	//config.hwnd			= window->getNativeWindowHandle();
	//window->mContext	= Coral::RAII::createContext(config);

	//if (!window->mContext)
	//{
	//	return nullptr;
	//}

	//Coral::SwapchainConfig swapchainConfig{};
	//swapchainConfig.format		= Coral::PixelFormat::RGBA8_SRGB;
	//swapchainConfig.depthFormat = Coral::PixelFormat::DEPTH24_STENCIL8;

	//window->mSwapchain = Coral::RAII::createSwapchain(window->mContext.get(), swapchainConfig);

	//if (!window->mSwapchain)
	//{
	//	return nullptr;
	//}

	return window;
}


WindowImpl::~WindowImpl()
{
	if (mWindowHandle)
	{
		glfwDestroyWindow(mWindowHandle);
	}
	glfwTerminate();
}


void
WindowImpl::show()
{
	glfwShowWindow(mWindowHandle);
}


void
WindowImpl::hide()
{
	glfwHideWindow(mWindowHandle);
}


bool
WindowImpl::isShowing() const
{
	int visible = glfwGetWindowAttrib(mWindowHandle, GLFW_VISIBLE);

	return visible == GLFW_TRUE;
}


bool
WindowImpl::close()
{
	glfwSetWindowShouldClose(mWindowHandle, GLFW_TRUE);
	return true;
}


bool 
WindowImpl::shouldClose() const
{
	return glfwWindowShouldClose(mWindowHandle);
}


void 
WindowImpl::resize(uint32_t width, uint32_t height)
{
	glfwSetWindowSize(mWindowHandle, width, height);
}


uint32_t 
WindowImpl::width() const
{
	int width, height;
	glfwGetWindowSize(mWindowHandle, &width, &height);

	return static_cast<uint32_t>(width);
}


uint32_t 
WindowImpl::height() const
{
	int width, height;
	glfwGetWindowSize(mWindowHandle, &width, &height);

	return static_cast<uint32_t>(height);
}


void 
WindowImpl::setTitle(const char* title)
{
	mTitle = title;
	glfwSetWindowTitle(mWindowHandle, mTitle.c_str());
}


const char*
WindowImpl::title() const
{
	return mTitle.c_str();
}


bool
WindowImpl::isFullscreen() const
{
	return true;
}


bool
WindowImpl::setFullscreen()
{
	return true;
}


bool
WindowImpl::setWindowed()
{
	return true;
}


bool
WindowImpl::showTitleBar()
{
	return true;
}


bool
WindowImpl::hideTitleBar()
{
	return true;
}


void
WindowImpl::present()
{
	glfwSwapBuffers(mWindowHandle);
}


void
WindowImpl::processEvents()
{
	glfwPollEvents();
}


void* 
WindowImpl::getNativeWindowHandle()
{
	return glfwGetWin32Window(mWindowHandle);
}


//KeyState
//Window::getKeyState(Key key) const
//{
//	return toKeyState(glfwGetKey(mWindowHandle, convert(key)));
//}
//
//
//KeyState
//Window::getKeyState(const InputChord& chord) const
//{
//	return KeyState::RELEASED;
//}
//
//
//KeyState
//Window::getMouseButtonState(MouseButton button) const
//{
//	return toKeyState(glfwGetMouseButton(static_cast<GLFWwindow*>(mWindowHandle), convert(button)));
//}
//
//
//Vec2
//Window::getMousePosition() const
//{
//	double x, y;
//	glfwGetCursorPos(mWindowHandle, &x, &y);
//	return { static_cast<float>(x) / width(), static_cast<float>(y) / height() };
//}
//
//
//void
//Window::setMousePosition(const Vec2& normalizedPosition)
//{
//	glfwSetCursorPos(mWindowHandle, normalizedPosition.x / width(), normalizedPosition.y / height());
//}


//Coral::Context& 
//Window::getRenderContext()
//{
//	return *mContext;
//}
//
//
//Coral::Swapchain&
//Window::getSwapchain()
//{
//	return *mSwapchain;
//}
