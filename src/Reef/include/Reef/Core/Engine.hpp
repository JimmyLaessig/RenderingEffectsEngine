#ifndef ENGINE_CORE_ENGINE_HPP
#define ENGINE_CORE_ENGINE_HPP

#include <Engine/System.hpp>

#include <Engine/Core/Viewport.hpp>

#include <memory>

namespace Reef
{

class Scene;
class IWindow;
class IInput;
class ICanvas;

class ENGINE_API Engine
{
public:

	static std::unique_ptr<Engine> createEngine(IWindow& window);

	virtual ~Engine() = default;

	virtual Scene* activeScene() = 0;

	virtual const Scene* activeScene() const = 0;

	virtual void updateFrame() = 0;

	virtual Viewport viewport() const = 0;

	virtual const IInput& input() const = 0;

	virtual IInput& input() = 0;

	//virtual void addCanvas(ICanvas& canvas) = 0;
};

} // namespace Reef

#endif // !#define ENGINE_CORE_ENGINE_HPP
