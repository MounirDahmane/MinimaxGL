/**
 * @file Shader.h
 * @brief Definition of the Shader class for loading, compiling, and linking OpenGL shader programs.
 */

#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
    unsigned int ID; ///< The OpenGL ID handle for this shader program

    /**
     * @brief Constructor that reads and builds the shader from file paths.
     * @param vertexPath The relative or absolute path to the Vertex Shader source code.
     * @param fragmentPath The relative or absolute path to the Fragment Shader source code.
     */
    Shader(const char *vertexPath, const char *fragmentPath);

    /**
     * @brief Destructor safely deletes the shader program from GPU memory.
     */
    ~Shader();

    // Prevent copying to avoid double-deletion of the same OpenGL Program ID
    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    /**
     * @brief Activates the shader program.
     */
    void use() const;

    /**
     * @brief Sets a uniform float value in the shader.
     * @param name The name of the uniform variable.
     * @param value The float value to set.
     */
    void SetUniform1f(const char *name, float value) const;

    /**
     * @brief Sets a uniform integer value in the shader.
     * @param name The name of the uniform variable.
     * @param value The integer value to set.
     */
    void SetUniform1i(const char *name, int value) const;

    /**
     * @brief Sets a uniform 3D float vector (vec3) in the shader.
     * @param name The name of the uniform variable.
     * @param x The X component.
     * @param y The Y component.
     * @param z The Z component.
     */
    void SetUniform3f(const char *name, float x, float y, float z) const;

private:
    /**
     * @brief Utility function for checking shader compilation and linking errors.
     * @param shader The OpenGL ID of the shader or program.
     * @param type The type of shader ("VERTEX", "FRAGMENT", or "PROGRAM").
     * @param path The path to the file (used for detailed error logging).
     */
    void checkCompileErrors(
        unsigned int shader, const std::string &type, const std::string &path) const;
};