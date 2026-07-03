#ifndef REEF_PLATFORM_WINDOWMANAGERIMPL_HPP
#define REEF_PLATFORM_WINDOWMANAGERIMPL_HPP

#include <Reef/Platform/WindowManager.hpp>

#include "WindowImpl.hpp"

#include <unordered_set>
#include <memory>

namespace Reef
{
class ApplicationImpl;

class WindowManagerImpl : public WindowManager
{
public:
    WindowManagerImpl(ApplicationImpl& application);

	Window* createWindow(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar) override;

	void destroy(Window* window) override;

	void processEvents();

    uint32_t windowCount() const override;

private:

	ApplicationImpl& mApplication;

	std::unordered_set<std::unique_ptr<WindowImpl>> mWindows;

}; // class WindowManagerImpl

} // namespace Reef

#endif //!REEF_PLATFORM_WINDOWMANAGERIMPL_HPP
