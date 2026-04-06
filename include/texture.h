#pragma once

/**
 * @class Texture
 * @brief Manages the loading, binding, and cleanup of 2D OpenGL textures.
 */
class Texture
{
public:
    /**
     * @brief Loads an image from the disk and uploads it to the GPU.
     * @param Path The relative or absolute path to the image file.
     */
    Texture(const char *Path);

    /**
     * @brief Destructor safely deletes the texture from GPU memory.
     */
    ~Texture();

    // Prevent copying to avoid double-deletion of the same OpenGL texture ID
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    /**
     * @brief Binds the texture to the current OpenGL context.
     * @param slot The texture unit to bind to (defaults to 0, e.g., GL_TEXTURE0).
     */
    void BindTexture(unsigned int slot = 0) const;

private:
    unsigned int _texture; ///< The OpenGL ID handle for this texture
};