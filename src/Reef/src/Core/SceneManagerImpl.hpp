#ifndef REEF_CORE_SCENEMANAGERIMPL_HPP
#define REEF_CORE_SCENEMANAGERIMPL_HPP

#include <Reef/Core/SceneManager.hpp>

#include <Reef/Core/FrameTime.hpp>

#include "SceneImpl.hpp"

#include <unordered_set>
#include <memory>

namespace Reef
{
class ApplicationImpl;

class SceneManagerImpl: public SceneManager
{
public:

    SceneManagerImpl(ApplicationImpl& application);

    ~SceneManagerImpl();

	Scene* createScene() override;

	void destroyScene(Scene* scene) override;

	void tick(const FrameTime& frameTime);

private:

    ApplicationImpl& mApplication;

    std::unordered_set<std::unique_ptr<SceneImpl>> mScenes;

}; // class SceneManagerImpl

} // namespace Reef

#endif //!REEF_CORE_SCENEMANAGERIMPL_HPP
