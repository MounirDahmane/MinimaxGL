/**
 * @file Application.cpp
 * @brief Implementation of the main Application loop and rendering logic.
 */

#include <glad/glad.h> // MUST BE FIRST
#include <filesystem> // C++17
#include <iostream>
#include <unistd.h>   // For readlink (Linux specific)

#include "Application.h"
#include "Game.h"
#include "Gui.h"
#include "Shader.h"
#include "setup.h"
#include "texture.h"
#include "vertices.h"

namespace
{
    /**
     * @brief Finds the absolute path of the directory containing the executable.
     */
    std::string GetExecutableDir() {
        char buffer[1024];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1) {
            buffer[len] = '\0';
            return std::filesystem::path(buffer).parent_path().string();
        }
        return ".";
    }

    /**
     * @brief Resolves a path relative to the project root (one level up from build/bin).
     */
    std::string GetResPath(const std::string& relativePath) {
        std::filesystem::path base = GetExecutableDir();
        // Assumes executable is in a subfolder like 'build/' or 'bin/'
        return (base / ".." / relativePath).lexically_normal().string();
    }
}

void Application::Run()
{
    // 1. Initialize Context and Window
    GLwindow glwindow;
    if (!window) return;

    // Timing variables for Delta Time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // 2. Initialize Engine Components with resolved absolute paths
    Gui gui(window);
    Shader shader(GetResPath("resources/shaders/VertexShader.txt").c_str(), 
                  GetResPath("resources/shaders/FragmentShader.txt").c_str());
    Shader line(GetResPath("resources/shaders/hash_line_vs.txt").c_str(), 
                GetResPath("resources/shaders/hash_line_fs.txt").c_str());

    VRTX vertices;
    Texture x_texture(GetResPath("resources/Textures/x_texture.png").c_str());
    Texture o_texture(GetResPath("resources/Textures/o_texture.png").c_str());

    bool score_tallied = false;

    // 3. Main Game Loop
    while (!glfwWindowShouldClose(window))
    {
        // --- Calculate Delta Time ---
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // --- Render Background ---
        glClearColor(gui.clear_color.x, gui.clear_color.y, gui.clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- Input & Logic ---
        ProcessInput(window);
        int gameState = Game::Check_Game();

        // Increment the global scores once per game end
        if (gameState != 1 && !score_tallied) {
            if (gameState == Game::WIN) win++;
            else if (gameState == Game::LOSS) lost++;
            else if (gameState == Game::DRAW) draw++;
            score_tallied = true;
        }

        if (gameState == 1) score_tallied = false;

        // --- Render Grid Lines ---
        line.use();
        line.SetUniform3f("aColor", gui.Hash_color.x, gui.Hash_color.y, gui.Hash_color.z);
        vertices.DrawLines();

        // --- Render Pieces ---
        shader.use();
        for (int i = 0; i < 9; i++) {
            if (Game::board[i] == Game::PLAYER_MARKER) {
                x_texture.BindTexture();
                vertices.render(i);
            }
            else if (Game::board[i] == Game::AI_MARKER) {
                o_texture.BindTexture();
                vertices.render(i);
            }
        }

        // --- Render ImGui GUI ---
        gui.render(window, gameState, counter, win, lost, draw);

        // --- Swap & Poll ---
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
} 