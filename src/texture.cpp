/**
 * @file texture.cpp
 * @brief Implementation of the Texture class for managing OpenGL 2D textures.
 */

#include "texture.h"

#include "stb_image.h"

#include <glad/glad.h>
#include <iostream>

Texture::Texture(const char *Path)
    : _texture(0)
{
    // Generate and bind the OpenGL texture object
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    // stbi_set_flip_vertically_on_load(true); // Enable if texture coordinates require Y-axis
    // inversion

    // Load image data from file
    int width, height, nbrChannels;
    unsigned char *data = stbi_load(Path, &width, &height, &nbrChannels, 0);

    if (data)
    {
        // Determine OpenGL color format based on the number of image channels
        GLenum format = GL_RGB;
        if (nbrChannels == 1)
            format = GL_RED;
        else if (nbrChannels == 4)
            format = GL_RGBA;

        // Apply texture wrapping parameters
        if (nbrChannels == 4)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        }

        // Apply texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload texture data to the GPU and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "ERROR::TEXTURE::FAILED_TO_LOAD: " << Path << std::endl;
    }

    // Free CPU memory and unbind texture
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    // Free GPU memory
    if (_texture != 0)
    {
        glDeleteTextures(1, &_texture);
    }
}

void Texture::BindTexture(unsigned int slot) const
{
    // Bind texture to the specified texture unit
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _texture);
}