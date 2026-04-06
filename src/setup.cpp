/**
 * @file setup.cpp
 * @brief Implementation of window setup and input handling logic.
 */

// clang-format off
#include <glad/glad.h> // MUST BE LINE 1
// clang-format on

#include "setup.h"
#include "Game.h"
#include <iostream>

// --- Public Globals ---
unsigned int window_width = 800;
unsigned int window_height = 800;
GLFWwindow *window = nullptr;

int counter = 0;
unsigned int win = 0;
unsigned int lost = 0;
unsigned int draw = 0;

// --- Private File Data ---
namespace
{
    /**
     * @brief GLFW callback for handling window resize events.
     */
    void FrameBuffer_size_callback(GLFWwindow *win_ptr, int width, int height)
    {
        glViewport(0, 0, width, height);
        window_width = width;
        window_height = height;
    }

    /**
     * @brief GLFW callback for handling mouse input.
     */
    void mouse_callback(GLFWwindow *win_ptr, int button, int action, int mods)
    {
        // IMPORTANT: Ignore clicks completely if the game is over!
        // The ImGui popup handles restarting now.
        if (Game::Check_Game() != 1) 
            return;

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            double x, y;
            glfwGetCursorPos(win_ptr, &x, &y);

            if (x < 240 && y < 235)
                Game::logic(0, win_ptr, counter);
            else if (x > 280 && x < 515 && y < 235)
                Game::logic(1, win_ptr, counter);
            else if (x > 560 && x < 800 && y < 235)
                Game::logic(2, win_ptr, counter);
            else if (x < 240 && y > 280 && y < 520)
                Game::logic(3, win_ptr, counter);
            else if (x > 280 && x < 515 && y > 280 && y < 515)
                Game::logic(4, win_ptr, counter);
            else if (x > 560 && x < 800 && y > 280 && y < 516)
                Game::logic(5, win_ptr, counter);
            else if (x < 240 && y > 560 && y < 800)
                Game::logic(6, win_ptr, counter);
            else if (x > 280 && x < 520 && y > 560 && y < 800)
                Game::logic(7, win_ptr, counter);
            else if (x > 560 && x < 800 && y > 560 && y < 800)
                Game::logic(8, win_ptr, counter);
        }

        Game::AI(win_ptr, counter);
    }
} // namespace

// --- Implementation ---

void ProcessInput(GLFWwindow *win_ptr)
{
    if (glfwGetKey(win_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win_ptr, true);

    if (glfwGetKey(win_ptr, GLFW_KEY_R) == GLFW_PRESS)
        Game::reset(counter);
}

GLwindow::GLwindow()
{
    if (!glfwInit())
    {
        std::cerr << "ERROR::FAILED::INITIALIZING_GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "TicTacToe", NULL, NULL);

    if (window == nullptr)
    {
        std::cerr << "ERROR::FAILED::LOADING_GLFW_WINDOW" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FrameBuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR::FAILED_LOADING_GLAD" << std::endl;
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLwindow::~GLwindow() { glfwTerminate(); }