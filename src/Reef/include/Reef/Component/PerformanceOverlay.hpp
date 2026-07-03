#ifndef ENGINE_COMPONENTS_PERFORMANCEOVERLAY_HPP
#define ENGINE_COMPONENTS_PERFORMANCEOVERLAY_HPP

#include <Engine/System.hpp>

#include <Engine/Component/ScriptableComponent.hpp>

namespace Reef
{

class ENGINE_API PerformanceOverlay : public SubclassOf<PerformanceOverlay, ScriptableComponent>
{
public:

	void onComponentCreated();

	void onFrameUpdate(const FrameTime& frameTime);

	void onUpdateUI();

private:

	float mLastFrameTimeUpdate{ 0.f };

	float mUpdateIntervalInSeconds{ 1.f };

	float mLastFrameTimeCPU{ 0.f };

	float mLastFrameTimeGPU{ 0.f };
};

} // namespace Reef

#endif // !ENGINE_CORE_PERFORMANCEOVERLAY_HPP
