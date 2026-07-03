#include <Engine/Core/PerformanceOverlay.hpp>

#include <imgui.h>

using namespace Reef;


void
PerformanceOverlay::onComponentCreated()
{
}


void
PerformanceOverlay::onFrameUpdate(const FrameTime& frameTime)
{
	mLastFrameTimeUpdate += frameTime.deltaTime;

	if (mLastFrameTimeUpdate >= mUpdateIntervalInSeconds)
	{
		mLastFrameTimeUpdate = 0;
		mLastFrameTimeCPU    = frameTime.deltaTime;
		mLastFrameTimeGPU    = frameTime.deltaTime;
	}
}


void
PerformanceOverlay::onUpdateUI()
{
	ImGui::SetNextWindowPos(ImVec2(engine().viewport().resolution.x - 10, 10), 0, ImVec2(1, 0));

	auto flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse 
		       | ImGuiWindowFlags_NoMove   | ImGuiWindowFlags_AlwaysAutoResize
		       | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing;

	if (ImGui::Begin("Perf. Overlay", nullptr, flags))
	{
		if (ImGui::BeginTable("Perf. Overlay Table", 3, ImGuiTableFlags_SizingStretchProp))
		{
			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			ImGui::Text("FPS");

			ImGui::TableNextColumn();
			ImGui::Text(":");

			ImGui::TableNextColumn();
			ImGui::Text("%d", static_cast<int>(1.f / mLastFrameTimeCPU));

			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			ImGui::Text("Frame time (ms)");

			ImGui::TableNextColumn();
			ImGui::Text(":");

			ImGui::TableNextColumn();
			ImGui::Text("%.2f", mLastFrameTimeCPU * 1000);

			ImGui::EndTable();
		}
	}
	ImGui::End();
}
