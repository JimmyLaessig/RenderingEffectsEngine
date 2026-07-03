#include <Editor/SceneInspector.hpp>

#include <Editor/Inspector.hpp>

#include <Engine/SceneGraph/Component.hpp>

#include <imgui.h>
#include <iostream>

using namespace Reef;


//void
//SceneInspector::inspect(SceneObject& object)
//{
//	//auto iter = mCollapsed.find(&object);
//	//if (iter == mCollapsed.end())
//	//{
//	//	iter = mCollapsed.emplace(&object, true).first;
//	//}
//
//	//ImGui::PushID(&object);
//
//	//ImGui::SetNextItemOpen(iter->second);
//
//	//iter->second = ImGui::CollapsingHeader(object.name().c_str(), nullptr, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
//	//if (iter->second) {
//	//	ImGui::Indent();
//
//	//	ImGui::Text("asdasd");
//	//	for (auto child : object.children())
//	//	{
//	//		//for (auto component : entity.getComponents<Component>())
//	//		//{
//	//		//	ImGui::Text("%s", component->type().name());
//
//	//		//	//if (auto inspector = PropertyInspector::findInspector(component->type()))
//	//		//	//{
//	//		//	//	inspector->inspect()
//	//		//	//}
//	//		//}
//
//	//		inspect(*child);
//	//	}
//	//	ImGui::Unindent();
//	//}
//
//	//ImGui::PopID();
//}


void
SceneInspector::inspect(Scene& scene)
{
	if (ImGui::Button("test button"))
	{
		std::cout << "test button pressed" << std::endl;
	}
	if (mLastScene != &scene)
	{
		//mCollapsed.clear();
		mLastScene = &scene;
	}

	//for (auto entity : scene.())
	//{
	//	inspectEntity(*entity);
	//}
}
