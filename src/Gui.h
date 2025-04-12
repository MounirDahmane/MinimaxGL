#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

class Gui
{
public:
	Gui(GLFWwindow* window);
	~Gui();

	void FinalResult(unsigned int& win, unsigned int& lost, unsigned int& draw);
	void render(int& counter, unsigned int& win, unsigned int& lost, unsigned int& draw);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
	ImVec4 Hash_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


private:
	bool show_demo_window = true;
};