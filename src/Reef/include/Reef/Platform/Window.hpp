#ifndef REEF_PLATFORM_WINDOW_HPP
#define REEF_PLATFORM_WINDOW_HPP

#include <Reef/Export.hpp>
#include <Reef/Core/Viewport.hpp>
#include <Reef/Core/Event.hpp>
#include <Reef/Platform/Input.hpp>

#include <Reef/Core/View.hpp>

#include <glm/glm.hpp>

#include <cstdint>
#include <memory>
#include <string_view>
#include <string>

namespace Reef
{

enum class WindowEvent
{
	SEND_TO_TRAY,
	RESTORED_FROM_TRAY,
	MAXIMIZED,
	RESTORED,
	FOCUSED,
	FOCUS_LOST,
	OPENED,
	CLOSED
};

class REEF_API Window : public Input, public Reef::Core::View
{
public:

	virtual ~Window() = default;

	virtual void show() = 0;

	virtual void hide() = 0;

	virtual bool isShowing() const = 0;

	virtual bool shouldClose() const = 0;

	virtual void setPosition(const glm::vec2& position) = 0;

	virtual void resize(const glm::uvec2& clientResolution) = 0;

	virtual Viewport windowRect() const = 0;

	virtual Viewport clientRect() const = 0;

	virtual void setTitle(std::string_view title) = 0;

	virtual const std::string& title() const = 0;

	virtual bool isFullscreen() const = 0;

	virtual bool setFullscreen() = 0;

	virtual bool setWindowed() = 0;

	virtual bool showTitleBar() = 0;

	virtual bool hideTitleBar() = 0;

	virtual Event<WindowEvent>& onWindowEvent() = 0;

	virtual Event<glm::ivec2>& onWindowMoved() = 0;

}; // class Window

} // namespace Reef

#endif // !REEF_PLATFORM_WINDOW_HPP
