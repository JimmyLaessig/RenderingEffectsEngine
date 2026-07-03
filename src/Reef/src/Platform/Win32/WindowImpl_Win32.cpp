#include "WindowImpl_Win32.hpp"

#include <windowsx.h>

#include <array>
#include <cassert>
#include <ranges>

//#include <backends/imgui_impl_win32.h>

using namespace Reef;


KeyboardLayout
getKeyboardLayout()
{
    HKL layout = GetKeyboardLayout(0);
    LANGID langId = LOWORD((DWORD_PTR)layout);

    CHAR layoutName[KL_NAMELENGTH];
    GetKeyboardLayoutName(layoutName);

    switch (langId)
    {
        case 0x0409: return KeyboardLayout::ENGLISH;
        case 0x0407: return KeyboardLayout::GERMAN;
        default:
            assert(false);
            return KeyboardLayout::ENGLISH;
    }
}


std::array<int, 5>
MouseButtonMapping =
{
    /* MousButton::LEFT */   VK_LBUTTON,
    /* MousButton::RIGHT */  VK_RBUTTON,
    /* MousButton::MIDDLE */ VK_MBUTTON,
    /* MousButton::X1 */     VK_XBUTTON1,
    /* MousButton::X2 */     VK_XBUTTON2,
};


namespace KeyMappings
{


std::array<int, 123> German =
{
    /* Key::SPACE */  VK_SPACE,
    /* Key::MINUS */  VK_OEM_MINUS,
    /* Key::PERIOD */ VK_OEM_PERIOD,
    /* Key::COMMA */  VK_OEM_COMMA,

    /* Key::ZERO */  '0',
    /* Key::ONE */    '1',
    /* Key::TWO */    '2',
    /* Key::THREE */  '3',
    /* Key::FOUR */   '4',
    /* Key::FIVE */   '5',
    /* Key::SIX */    '6',
    /* Key::SEVEN */  '7',
    /* Key::EIGHT */  '8',
    /* Key::NINE */   '9',

    /* Key::A */ 'A',
    /* Key::B */ 'B',
    /* Key::C */ 'C',
    /* Key::D */ 'D',
    /* Key::E */ 'E',
    /* Key::F */ 'F',
    /* Key::G */ 'G',
    /* Key::H */ 'H',
    /* Key::I */ 'I',
    /* Key::J */ 'J',
    /* Key::K */ 'K',
    /* Key::L */ 'L',
    /* Key::M */ 'M',
    /* Key::N */ 'N',
    /* Key::O */ 'O',
    /* Key::P */ 'P',
    /* Key::Q */ 'Q',
    /* Key::R */ 'R',
    /* Key::S */ 'S',
    /* Key::T */ 'T',
    /* Key::U */ 'U',
    /* Key::V */ 'V',
    /* Key::W */ 'W',
    /* Key::X */ 'X',
    /* Key::Y */ 'Y',
    /* Key::Z */ 'Z',

    /* Key::ESCAPE */     VK_ESCAPE,
    /* Key::RETURN */      VK_RETURN,
    /* Key::TAB */            VK_TAB,
    /* Key::BACKSPACE */      VK_BACK,
    /* Key::INSERT */         VK_INSERT,
    /* Key::DELETE */         VK_DELETE,
    /* Key::RIGHT */          VK_RIGHT,
    /* Key::LEFT */           VK_LEFT,
    /* Key::DOWN */           VK_DOWN,
    /* Key::UP */             VK_UP,
    /* Key::PAGE_UP */        VK_PRIOR,
    /* Key::PAGE_DOWN */      VK_NEXT,
    /* Key::HOME */           VK_HOME,
    /* Key::END */            VK_END,
    /* Key::CAPS_LOCK */      VK_CAPITAL,
    /* Key::SCROLL_LOCK */    VK_SCROLL,
    /* Key::NUM_LOCK */       VK_NUMLOCK,
    /* Key::PRINT_SCREEN */   VK_SNAPSHOT,
    /* Key::PAUSE */          VK_PAUSE,

    /* Key::F1, */ VK_F1,             
    /* Key::F2, */ VK_F2,             
    /* Key::F3, */ VK_F3,             
    /* Key::F4, */ VK_F4,             
    /* Key::F5, */ VK_F5,             
    /* Key::F6, */ VK_F6,             
    /* Key::F7, */ VK_F7,             
    /* Key::F8, */ VK_F8,             
    /* Key::F9, */ VK_F9,             
    /* Key::F10 */ VK_F10,             
    /* Key::F11 */ VK_F11,             
    /* Key::F12 */ VK_F12,             
    /* Key::F13 */ VK_F13,             
    /* Key::F14 */ VK_F14,             
    /* Key::F15 */ VK_F15,             
    /* Key::F16 */ VK_F16,             
    /* Key::F17 */ VK_F17,             
    /* Key::F18 */ VK_F18,             
    /* Key::F19 */ VK_F19,             
    /* Key::F20 */ VK_F20,             
    /* Key::F21 */ VK_F21,             
    /* Key::F22 */ VK_F22,             
    /* Key::F23 */ VK_F23,             
    /* Key::F24 */ VK_F24,             

    /* Key::NUMPAD_ZERO, */ VK_NUMPAD0,
    /* Key::NUMPAD_ONE,  */ VK_NUMPAD1,
    /* Key::NUMPAD_TWO,  */ VK_NUMPAD2,
    /* Key::NUMPAD_THREE */ VK_NUMPAD3,
    /* Key::NUMPAD_FOUR, */ VK_NUMPAD4,
    /* Key::NUMPAD_FIVE, */ VK_NUMPAD5,
    /* Key::NUMPAD_SIX,  */ VK_NUMPAD6,
    /* Key::NUMPAD_SEVEN */ VK_NUMPAD7,
    /* Key::NUMPAD_EIGHT */ VK_NUMPAD8,
    /* Key::NUMPAD_NINE, */ VK_NUMPAD9,

    /* Key::NUMPAD_DECIMAL */  VK_DECIMAL,
    /* Key::NUMPAD_DIVIDE */   VK_DIVIDE,
    /* Key::NUMPAD_MULTIPLY */ VK_MULTIPLY,
    /* Key::NUMPAD_SUBTRACT */ VK_SUBTRACT,
    /* Key::NUMPAD_ADD */      VK_ADD,

    //NUMPAD_DECIMAL,  // Numeric keypad 0 key
    //NUMPAD_DIVIDE,   // Numeric keypad / key
    //NUMPAD_MULTIPLY, // Numeric keypad * key
    //NUMPAD_SUBTRACT, // Numeric keypad - key
    //NUMPAD_ADD,      // Numeric keypad + key
    //NUMPAD_RETURN,   // Numeric keypad enter key
    //NUMPAD_EQUAL,    // Numeric keypad = key

    /* Key::LEFT_SHIFT */    VK_LSHIFT,
    /* Key::LEFT_CONTROL */  VK_LCONTROL, 
    /* Key::LEFT_ALT */      VK_LMENU,
    /* Key::LEFT_SUPER */    VK_LWIN,
    /* Key::RIGHT_SHIFT */   VK_RSHIFT,
    /* Key::RIGHT_CONTROL */ VK_RCONTROL,
    /* Key::RIGHT_ALT */     VK_RMENU,
    /* Key::RIGHT_SUPER */   VK_RWIN,

    // Keys available for german keyboard layouts
    /* Key::CARET */        VK_OEM_5,
    /* Key::ESZETT */       VK_OEM_4,
    /* Key::ACUTE_ACCENT */ VK_OEM_6,
    /* Key::UE */           VK_OEM_1,
    /* Key::PLUS */         VK_OEM_PLUS,
    /* Key::OE */           VK_OEM_3,
    /* Key::AE */           VK_OEM_7,
    /* Key::HASH */         VK_OEM_2,
    /* Key::LESS_THAN */    VK_OEM_102,

    // Keys available for english keyboard layouts
    /* Key::LEFT_BRACKET */   VK_NONAME,
    /* Key::RIGHT_BRACKET */  VK_NONAME,
    /* Key::BACKTICK */       VK_NONAME,
    /* Key::BACKSLASH */      VK_NONAME,
    /* Key::SLASH */          VK_NONAME,
    /* Key::SEMICOLON */      VK_NONAME,
    /* Key::EQUAL */          VK_NONAME,
    /* Key::APOSTROPHE */     VK_NONAME,
};

} // namespace KeyMappings

namespace Reef
{

inline const char* CLASS_NAME = "Reef Window Class";

std::unique_ptr<WindowImplWin32>
WindowImplWin32::create(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar)
{
    auto window        = std::make_unique<WindowImplWin32>();
    window->mTitle     = title;
    window->mHInstance = GetModuleHandle(nullptr);

    WNDCLASS wndClass{};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance     = window->mHInstance;
    wndClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc   = &WindowImplWin32::processMessageCallback;

    if (!RegisterClass(&wndClass))
    {
        return nullptr;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;

    auto screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

    RECT rect{};
    rect.left   = (screenWidth - width) / 2;
    rect.top    = (screenHeight - height) / 2;
    rect.right  = rect.left + width;
    rect.bottom = rect.top + height;

    /*AdjustWindowRect(&rect, style, false);

    rect.right -= rect.left;
    rect.bottom -= rect.top;

    rect.left -= rect.left;
    rect.top -= rect.top;*/
    window->mHwnd = CreateWindowEx(0, 
                                   CLASS_NAME, 
                                   window->mTitle.c_str(), 
                                   style, 
                                   rect.left, 
                                   rect.top,
                                   rect.right - rect.left, 
                                   rect.bottom - rect.top, 
                                   nullptr, 
                                   nullptr, 
                                   window->mHInstance,
                                   nullptr);

    if (!window->mHwnd)
    {
        return nullptr;
    }

    SetWindowLongPtr(window->mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window.get()));

    window->mKeyboardLayout = getKeyboardLayout();
    window->mKeyStates.fill(KeyState::RELEASED);
    window->mMouseButtonStates.fill(KeyState::RELEASED);
    window->show();

    /*auto context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    if (!ImGui_ImplWin32_Init(window->mHwnd))
    {
        return nullptr;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;*/

    return window;
}

} // namespace Reef


WindowImplWin32::~WindowImplWin32()
{
    //ImGui_ImplWin32_Shutdown();

    //ImGui::DestroyContext();

    if (mHwnd)
    {
        DestroyWindow(mHwnd);
        mHwnd = nullptr;
    }

    UnregisterClass(CLASS_NAME, mHInstance);
}


void
WindowImplWin32::show()
{
    mIsShowing = true;
    ShowWindow(mHwnd, SW_SHOW);
}


void
WindowImplWin32::hide()
{
    mIsShowing = false;
    ShowWindow(mHwnd, SW_HIDE);
}


bool
WindowImplWin32::isShowing() const
{
    return mIsShowing;
}


bool 
WindowImplWin32::shouldClose() const
{
    return mWindowShouldClose;
}


void
WindowImplWin32::setPosition(const glm::vec2& position)
{
    auto rect = windowRect();
    SetWindowPos(mHwnd, nullptr, position.x, position.y, static_cast<int>(rect.resolution.x), static_cast<int>(rect.resolution.y), 0);
}


void
WindowImplWin32::resize(const glm::uvec2& clientResolution)
{
    auto wr = windowRect();
    auto cr = clientRect();

    auto delta = wr.resolution - cr.resolution;

    glm::ivec2 windowResolution = clientResolution + delta;
    SetWindowPos(mHwnd, nullptr, wr.offset.x, wr.offset.y, windowResolution.x, windowResolution.y, 0);
}


Viewport
WindowImplWin32::windowRect() const
{
    RECT rect{};
    GetWindowRect(mHwnd, &rect);
    auto width  = static_cast<uint32_t>(rect.right - rect.left);
    auto height = static_cast<uint32_t>(rect.bottom - rect.top);
    return Viewport{ { rect.left, rect.top }, { width, height } };
}


Viewport
WindowImplWin32::clientRect() const
{
    RECT rect{};
    GetClientRect(mHwnd, &rect);

    POINT origin{};
    ClientToScreen(mHwnd, &origin);

    auto width  = static_cast<uint32_t>(rect.right - rect.left);
    auto height = static_cast<uint32_t>(rect.bottom - rect.top);
    return Viewport{ { origin.x, origin.y }, { width, height } };
}


void 
WindowImplWin32::setTitle(std::string_view title)
{
    mTitle = title;
    SetWindowText(mHwnd, mTitle.c_str());
}


const std::string&
WindowImplWin32::title() const
{
    return mTitle;
}


bool
WindowImplWin32::isFullscreen() const
{
    return true;
}


bool
WindowImplWin32::setFullscreen()
{
    return true;
}


bool
WindowImplWin32::setWindowed()
{
    return true;
}


bool
WindowImplWin32::showTitleBar()
{
    return true;
}


bool
WindowImplWin32::hideTitleBar()
{
    return true;
}


void
WindowImplWin32::processEvents()
{
    MSG message{};

    while(PeekMessage(&message, mHwnd, 0u, 0u, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // Fetch the latest key state
    for (const auto& [key, state] : std::views::zip(KeyMappings::German, mKeyStates))
    {
        // The key is pressed
        if (GetKeyState(key) < 0)
        {
            state = KeyState::PRESSED;
        }
        // The key is not longer pressed
        else if (state == KeyState::PRESSED)
        {
            state = KeyState::RELEASED;
        }
        // The key is not pressed
        else
        {
            state = KeyState::UP;
        }
    }

    // Fetch the latest mouse button state
    for (const auto& [key, state] : std::views::zip(MouseButtonMapping, mMouseButtonStates))
    {
        // The key is pressed
        if (GetKeyState(key) < 0)
        {
            state = KeyState::PRESSED;
        }
        // The key is not longer pressed
        else if (state == KeyState::PRESSED)
        {
            state = KeyState::RELEASED;
        }
        // The key is not pressed
        else
        {
            state = KeyState::UP;
        }
    }
}


void*
WindowImplWin32::nativeWindowHandle()
{
    return mHwnd;
}


LRESULT
WindowImplWin32::processMessageCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (auto window = reinterpret_cast<Reef::WindowImplWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)))
    {
        return window->processMessage(uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


// Forward declare message handler from imgui_impl_win32.cpp
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT
WindowImplWin32::processMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
    //{
    //    return true;
    //}

    switch (uMsg)
    {
        case WM_CLOSE:
            mWindowEvent.invoke(WindowEvent::CLOSED);
            return true;
        case WM_SIZE:
            return onWindowResized(LOWORD(lParam), HIWORD(lParam));
        //case WM_MOVE:
            return onWindowMoved(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)));
        case WM_INPUTLANGCHANGE:
        case WM_INPUTLANGCHANGEREQUEST:
            mKeyboardLayout = getKeyboardLayout();
            mKeyStates.fill(KeyState::RELEASED);
            mMouseButtonStates.fill(KeyState::RELEASED);
            return true;
        case WM_MOUSEMOVE:
            return onMouseMoved(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        default:
            return DefWindowProc(mHwnd, uMsg, wParam, lParam);
    }
}


LRESULT
WindowImplWin32::onWindowMoved(int32_t x, int32_t y)
{
    mWindowMovedEvent.invoke(glm::ivec2(x, y));
    return true;
}


LRESULT
WindowImplWin32::onWindowResized(uint32_t width, uint32_t height)
{
    mWindowResizedEvent.invoke(width, height);
    return true;
}


LRESULT
WindowImplWin32::onMouseMoved(int32_t x, int32_t y)
{
    // TODO mouse move event
    return true;
}


KeyState
WindowImplWin32::getKeyState(Key key) const
{
    return mKeyStates[static_cast<size_t>(key)];
}


KeyState
WindowImplWin32::getMouseButtonState(MouseButton button) const
{
    return mMouseButtonStates[static_cast<size_t>(button)];
}


void
WindowImplWin32::setCursorPosition(const glm::uvec2& pixelPosition)
{
    SetCursorPos(pixelPosition.x, pixelPosition.y);
}


glm::ivec2
WindowImplWin32::getCursorPosition() const
{
    POINT point{ 0, 0 };
    GetCursorPos(&point);

    Viewport viewport = clientRect();

    return { point.x - viewport.offset.x, point.y - viewport.offset.y };
}


Event<WindowEvent>&
WindowImplWin32::onWindowEvent()
{
    return mWindowEvent;
}


Event<glm::ivec2>&
WindowImplWin32::onWindowMoved()
{
    return mWindowMovedEvent;
}


uint32_t
WindowImplWin32::width() const
{
    return clientRect().resolution.x;
}


uint32_t
WindowImplWin32::height() const
{
    return clientRect().resolution.y;
}


Event<uint32_t, uint32_t>&
WindowImplWin32::onViewResized()
{
    return mWindowResizedEvent;
}
