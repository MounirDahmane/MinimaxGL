/**
 * @file Gui.h
 * @brief Manages the Dear ImGui context and user interface overlay.
 */

#pragma once

#include "imgui.h"

// Forward declaration avoids importing the massive GLFW header into every file that includes Gui.h
struct GLFWwindow;

class Gui
{
public:
    /**
     * @brief Initializes the ImGui context, settings, and backends.
     * @param window The active GLFW window.
     */
    Gui(GLFWwindow *window);

    /**
     * @brief Shuts down the ImGui context and cleans up memory.
     */
    ~Gui();

    // Prevent copying to avoid ImGui context corruption
    Gui(const Gui &) = delete;
    Gui &operator=(const Gui &) = delete;

    /**
     * @brief Renders the ImGui settings window and the Game Over popup.
     * @param window The active GLFW window.
     * @param gameState Current state of the game (1 = playing, else game over).
     * @param counter Current turn count for the active round.
     * @param win Total player wins.
     * @param lost Total AI wins.
     * @param draw Total draws.
     */
    void render(
        GLFWwindow *window,
        int gameState,
        int &counter,
        unsigned int &win,
        unsigned int &lost,
        unsigned int &draw,
        float deltaTime);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
    ImVec4 Hash_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

private:
    bool show_demo_window = false; ///< Set to true to show the ImGui debug window
    bool popup_opened = false;     ///< Tracks if the Game Over modal is currently active
};