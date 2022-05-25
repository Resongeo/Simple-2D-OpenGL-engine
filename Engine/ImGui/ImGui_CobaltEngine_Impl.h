#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Core/Cobalt.h"

namespace Cobalt
{
	class ImGUI
	{
	public:
		static void Init(GLFWwindow* window)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");

			CB_LOG_INFO("ImGui initialized.");
		}

		static void SetupStyle()
		{
			ImGuiStyle* style = &ImGui::GetStyle();

			style->WindowTitleAlign = ImVec2(0.5, 0.5);
			style->WindowRounding = 8.0f;
			style->FrameRounding = 4.0f;
			style->WindowPadding = ImVec2(10, 10);
			style->Colors[ImGuiCol_Text] = ImColor(240, 240, 240);
			style->Colors[ImGuiCol_WindowBg] = ImColor(33, 33, 35);
			style->Colors[ImGuiCol_CheckMark] = ImColor(140, 227, 105);
			style->Colors[ImGuiCol_SliderGrab] = ImColor(115, 160, 220);
			style->Colors[ImGuiCol_SliderGrabActive] = ImColor(25, 70, 130);
			style->Colors[ImGuiCol_ResizeGrip] = ImColor(115, 160, 220, 51);
			style->Colors[ImGuiCol_TitleBg] = ImColor(26, 26, 26);
			style->Colors[ImGuiCol_TitleBgActive] = ImColor(60, 60, 60);
			style->Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 44);
			style->Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255, 100);
			style->Colors[ImGuiCol_FrameBgActive] = ImColor(48, 48, 48, 150);
			style->Colors[ImGuiCol_TabActive] = ImColor(0, 0, 0, 0);
			style->Colors[ImGuiCol_TabUnfocused] = ImColor(0, 0, 0, 0);
			style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(0, 0, 0, 0);
			style->Colors[ImGuiCol_Button] = ImColor(115, 165, 215, 100);
			style->Colors[ImGuiCol_ButtonHovered] = ImColor(115, 165, 215, 165);
			style->Colors[ImGuiCol_ButtonActive] = ImColor(35, 70, 120, 255);
		}

		static void NewFrame()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		}

		static void Render()
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}

		static void ShutDown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	};
}