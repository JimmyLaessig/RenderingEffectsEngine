//module;
//
//#include <imgui.h>
//#include "imgui/imgui_impl_opengl3.h"
//#include "imgui/imgui_impl_glfw.h"
//
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//
//module Engine.Application.ImGUILayer;
//
//import Engine.Application;
//import Engine.Application.WindowLayer;
//
//
//import RenderLib;
//
//using namespace Reef;
//
//
//
//import Engine.Application.WindowLayer;
//import Engine.Application;
//import Engine.Application.WindowImpl;
//
//import Engine.Rendering.Renderer;
//
//bool
//ImGUILayer::onInit()
//{
//	mWindowLayer = application()->getLayer<Engine::WindowLayer>();
//	
//	if (!mWindowLayer)
//	{
//		return false;
//	}
//
//	IMGUI_CHECKVERSION();
//	auto ctx = ImGui::CreateContext();
//
//	if (!ctx)
//	{
//		return false;
//	}
//
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//	ImGui::StyleColorsDark();
//
//	auto window = mWindowLayer->window();
//
//	auto windowHandle = static_cast<GLFWwindow*>(static_cast<WindowImpl*>(window)->mWindowHandle);
//
//	if (!ImGui_ImplGlfw_InitForOpenGL(windowHandle, true))
//	{
//		return false;
//	}
//
//	if (!ImGui_ImplOpenGL3_Init())
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//void
//ImGUILayer::deinit()
//{
//	ImGui_ImplOpenGL3_Shutdown();
//	ImGui::DestroyContext();
//}
//
//
//void
//ImGUILayer::update()
//{
//	ImGui_ImplOpenGL3_NewFrame();
//	ImGui_ImplGlfw_NewFrame();
//	ImGui::NewFrame();
//}
//
//
//void
//ImGUILayer::render()
//{
//	bool showDemoWindow{ true };
//	ImGui::ShowDemoWindow(&showDemoWindow);
//	ImGui::Render();
//
//	auto& renderer = Engine::Rendering::Renderer::instance();
//
//	auto& context = renderer.context();
//
//	RenderLib::CommandBufferConfig config{};
//
//	mCommandBuffer = RenderLib::RAII::createCommandBuffer(&context, config);
//
//	mCommandBuffer->begin();
//
//	std::array clearColor =
//	{
//		RenderLib::ClearColor({ 0.f, 0.f, 0.f, 0.f }, 0)
//	};
//	RenderLib::ClearDepth clearDepth(1.0f, 0);
//
//	mCommandBuffer->cmdBeginRenderPass(RenderLib::RenderPassBeginConfig{ mWindowLayer->renderSurface()->backbuffer(), { 0, 0, 2048, 1024 } });
//	//mCommandBuffer->cmdClearAttachments(clearColor, clearDepth);
//
//	mCommandBuffer->cmdExecuteCustomCommand([]()
//	{
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//	});
//
//	mCommandBuffer->cmdEndRenderPass();
//
//	mCommandBuffer->end();
//
//	renderer.submitCommandBuffer(mCommandBuffer.get());
//}
