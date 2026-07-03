#ifndef REEF_PLATFORM_WINDOWIMPL_HPP
#define REEF_PLATFORM_WINDOWIMPL_HPP

#include <Reef/Platform/Window.hpp>

namespace Reef
{

class WindowImpl : public Window
{
public:

    virtual void processEvents() = 0;

}; // class WindowImpl

} // namespace Reef

#endif // !REEF_PLATFORM_WINDOWIMPL_HPP