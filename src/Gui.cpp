#include "Gui.h"
#include <iostream>

Gui::Gui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
}
Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void Gui::render(int& counter, unsigned int& win, unsigned int& lost, unsigned int& draw)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		ImGui::Begin("Settings");
		ImGui::Text("Color Settings :");
		ImGui::ColorEdit3("Hash line color", (float*)&this->Hash_color);
		ImGui::ColorEdit3("background color", (float*)&this->clear_color);

		ImGui::Text("counter = %d", counter);
		ImGui::Text("PLAYER_wins : %d", win);
		ImGui::Text("AI_wins : %d", lost);
		ImGui::Text("DRAWS : %d", draw);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		if (this->show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void Gui::FinalResult(unsigned int& win, unsigned int& lost, unsigned int& draw)
{
	if (win > lost && win > draw)
		std::cout << "PLAYER YOU HAVE WON ! I AM SUPRISED ACTUALLY" << std::endl;
	else if (win < lost && lost > draw)
		std::cout << "AI HAS WON !" << std::endl;
	else
		std::cout << "IT IS A DRAW!" << std::endl;
}