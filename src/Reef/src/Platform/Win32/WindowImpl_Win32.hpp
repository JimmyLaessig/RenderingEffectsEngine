#ifndef REEF_PLATFORM_WIN32_WINDOWIMPLWIN32_HPP
#define REEF_PLATFORM_WIN32_WINDOWIMPLWIN32_HPP

#include "../WindowImpl.hpp"

#include "../../Core/EventImpl.hpp"

#include <array>
#include <cstdint>
#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#undef DELETE

namespace Reef
{

class WindowImplWin32 : public WindowImpl
{
public:

    static std::unique_ptr<WindowImplWin32> create(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar);

    ~WindowImplWin32();

    void show() override;

    void hide() override;

    bool isShowing() const override;

    bool shouldClose() const override;

    void setPosition(const glm::vec2& position) override;

    void resize(const glm::uvec2& clientResolution) override;

    Viewport windowRect() const override;

    Viewport clientRect() const override;

    void setTitle(std::string_view title) override;

    const std::string& title() const override;

    bool isFullscreen() const override;

    bool setFullscreen() override;

    bool setWindowed() override;

    bool showTitleBar() override;

    bool hideTitleBar() override;

    void processEvents() override;

    void* nativeWindowHandle() override;

    KeyState getKeyState(Key key) const override;

    KeyState getMouseButtonState(MouseButton button) const override;

    void setCursorPosition(const glm::uvec2& pixelPosition) override;

    glm::ivec2 getCursorPosition() const override;

    Event<WindowEvent>& onWindowEvent() override;

    Event<glm::ivec2>& onWindowMoved() override;

    uint32_t width() const override;

    uint32_t height() const override;

    Event<uint32_t, uint32_t>& onViewResized() override;

private:

    LRESULT onWindowMoved(int32_t x, int32_t y);

    LRESULT onWindowResized(uint32_t width, uint32_t height);

    LRESULT onMouseMoved(int32_t x, int32_t y);

    LRESULT processMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK processMessageCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    std::string mTitle;

    HINSTANCE mHInstance{ nullptr };

    HWND mHwnd{ nullptr };

    bool mIsShowing{ false };

    bool mWindowShouldClose{ false };

    std::array<KeyState, 123> mKeyStates;

    std::array<KeyState, 8> mMouseButtonStates;

    KeyboardLayout mKeyboardLayout{ KeyboardLayout::ENGLISH };

    EventImpl<WindowEvent> mWindowEvent;

    EventImpl<uint32_t, uint32_t> mWindowResizedEvent;

    EventImpl<glm::ivec2> mWindowMovedEvent;

    WINDOWPOS mWindowPos;

}; // class WindowImplWin32

} // namespace Reef

#endif // !REEF_PLATFORM_WIN32_WINDOWIMPLWIN32_HPP
