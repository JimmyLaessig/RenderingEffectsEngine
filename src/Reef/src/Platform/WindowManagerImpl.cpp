#include "WindowManagerImpl.hpp"
#include "ApplicationImpl.hpp"

#include "Win32/WindowImpl_Win32.hpp"

using namespace Reef;

WindowManagerImpl::WindowManagerImpl(ApplicationImpl& application)
    : mApplication(application)
{}


Window*
WindowManagerImpl::createWindow(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar)
{
    if (auto window = WindowImplWin32::create(title, width, height, fullscreen, showTitleBar))
    {
        return mWindows.insert(std::move(window)).first->get();
    }

    return nullptr;
}


void
WindowManagerImpl::destroy(Window* window)
{
    mWindows.erase(std::find_if(mWindows.begin(), mWindows.end(), [window](const auto& ptr) { return ptr.get() == window; }));
}


void
WindowManagerImpl::processEvents()
{
    for (auto& window : mWindows)
    {
        window->processEvents();
    }
}


uint32_t
WindowManagerImpl::windowCount() const
{
    return static_cast<uint32_t>(mWindows.size());
}
