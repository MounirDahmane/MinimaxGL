/**
 * @file Application.h
 * @brief Main application class that orchestrates the engine components and game loop.
 */

#pragma once

class Application
{
public:
    /**
     * @brief Default constructor.
     */
    Application() = default;

    /**
     * @brief Default destructor.
     */
    ~Application() = default;

    // Prevent copying of the main application instance
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    /**
     * @brief Initializes systems and launches the main rendering loop.
     */
    void Run();
};