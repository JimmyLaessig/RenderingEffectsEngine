#ifndef REEF_SCENEMANAGER_HPP
#define REEF_SCENEMANAGER_HPP

#include <Reef/Export.hpp>
#include <Reef/Core/Scene.hpp>

namespace Reef
{

class REEF_API SceneManager
{
public:

	virtual ~SceneManager() = default;

	virtual Scene* createScene() = 0;

    virtual void destroyScene(Scene* scene) = 0;

}; // class SceneManager

} // namespace Reef

#endif //!REEF_SCENEMANAGER_HPP
