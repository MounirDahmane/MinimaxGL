/**
 * @file setup.h
 * @brief Window initialization, input processing, and core application setup.
 */

#pragma once

#include <GLFW/glfw3.h>

// Extern declarations for globals so Application.cpp can access them
extern unsigned int window_width;
extern unsigned int window_height;
extern GLFWwindow *window;

extern int counter;
extern unsigned int win;
extern unsigned int lost;
extern unsigned int draw;

/**
 * @brief Processes continuous keyboard input per frame.
 * @param window The active GLFW window instance.
 */
void ProcessInput(GLFWwindow *window);

/**
 * @class GLwindow
 * @brief RAII wrapper for initializing and terminating the GLFW window and OpenGL context.
 */
class GLwindow
{
public:
    GLwindow();
    ~GLwindow();

    GLwindow(const GLwindow &) = delete;
    GLwindow &operator=(const GLwindow &) = delete;
};