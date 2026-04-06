/**
 * @file Gui.cpp
 * @brief Implementation of the Gui class.
 */

#include "Gui.h"

#include "Game.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

Gui::Gui(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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

void Gui::render(
    GLFWwindow *window,
    int gameState,
    int &counter,
    unsigned int &win,
    unsigned int &lost,
    unsigned int &draw,
    float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // --- GAME OVER POPUP MODAL ---
    if (gameState != 1)
    {
        if (!popup_opened)
        {
            ImGui::OpenPopup("Game Over");
            popup_opened = true;
        }
    }
    else
    {
        popup_opened = false;
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(
            "Game Over", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    {
        if (gameState == Game::WIN)
        {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Player Wins!");
        }
        else if (gameState == Game::LOSS)
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "AI Wins!");
        }
        else
        {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "It's a Draw!");
        }

        ImGui::Separator();

        if (ImGui::Button("Play Again", ImVec2(120, 0)))
        {
            Game::reset(counter);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Quit", ImVec2(120, 0)))
        {
            glfwSetWindowShouldClose(window, true);
        }
        ImGui::EndPopup();
    }

    // --- SETTINGS WINDOW ---
    ImGui::Begin("Settings");
    {
        ImGui::Text("Performance:");
        ImGui::Text("Frame Time: %.3f ms", deltaTime * 1000.0f); // Converts seconds to milliseconds
        ImGui::Text("FPS: %.1f", 1.0f / deltaTime);

        ImGui::Text("Color Settings:");
        ImGui::ColorEdit3("Hash line color", (float *)&this->Hash_color);
        ImGui::ColorEdit3("Background color", (float *)&this->clear_color);

        ImGui::Separator();

        ImGui::Text("AI Settings:");
        ImGui::SliderInt("AI Dumbness %", &Game::error_chance, 0, 100);

        ImGui::Separator();

        if (ImGui::Button("Reset All Stats"))
        {
            win = 0;
            lost = 0;
            draw = 0;
        }

        ImGui::Text("Game Stats:");
        ImGui::Text("Turn Counter : %d", counter);
        ImGui::Text("Player Wins  : %d", win);
        ImGui::Text("AI Wins      : %d", lost);
        ImGui::Text("Draws        : %d", draw);

        ImGui::Separator();

        ImGui::Text("Performance: %.1f FPS", ImGui::GetIO().Framerate);

        if (this->show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}