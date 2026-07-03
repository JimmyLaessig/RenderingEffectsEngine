#ifndef REEF_EDITOR_SCENEINSPECTOR_H

#include <Editor/Inspector.hpp>

#include <Engine/SceneGraph/Entity.hpp>
#include <Engine/SceneGraph/Scene.hpp>

namespace Reef
{

class EDITOR_API SceneInspector 
{
public:

	void inspect(Scene& scene);

private:

	//void inspect(SceneObject& sceneObject);

	Scene* mLastScene{ nullptr };

	//std::unordered_map<SceneObject*, bool> mCollapsed;
};

} // namespace Reef

#endif // !REEF_EDITOR_SCENEINSPECTOR_H
