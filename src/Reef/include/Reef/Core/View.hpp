#ifndef REEF_CORE_VIEW_HPP
#define REEF_CORE_VIEW_HPP

#include <Reef/Export.hpp>

#include <Reef/Core/Viewport.hpp>

#include <Reef/Core/Event.hpp>

#include <cstdint>

namespace Reef::Core
{

/*!
 * \brief Interface representing a view into the scene
 */
class REEF_API View
{
public:

	virtual ~View() = default;

	//virtual Viewport viewport() const = 0;

	virtual uint32_t width() const = 0;

	virtual uint32_t height() const = 0;

	virtual Event<uint32_t, uint32_t>& onViewResized() = 0;

	virtual void* nativeWindowHandle() = 0;

}; // class View

} // namespace Reef::Core

#endif // !REEF_CORE_VIEW_HPP
