#ifndef REEF_PLATFORM_WINDOWMANAGER_HPP
#define REEF_PLATFORM_WINDOWMANAGER_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/Event.hpp>
#include <Reef/Platform/Window.hpp>

namespace Reef
{

class WindowManager;

/*!
 * Interface for managing application windows
 */
class REEF_API WindowManager
{
public:

	virtual ~WindowManager() = default;

	/*!
	 * Create a new window
     * \param title The window title
     * \param width The window width in pixels
     * \param height The window height in pixels
     * \param fullscreen Flag indicating if the window should be created in fullscreen mode
     * \param showTitleBar Flag indicating if the window should show the title bar
     * \return Returns a pointer to the created window, or nullptr if the window could not be created
	 */
	virtual Window* createWindow(std::string_view title, uint32_t width, uint32_t height, bool fullscreen, bool showTitleBar) = 0;

	/*!
	 * Destroy the window
     * \param window The window to destroy
	 */
	virtual void destroy(Window* window) = 0;

	/*!
	 * Get the number of open windows
	 */
    virtual uint32_t windowCount() const = 0;

}; // class WindowManager

} // namespace Reef

#endif // !REEF_PLATFORM_WINDOWMANAGER_HPP
