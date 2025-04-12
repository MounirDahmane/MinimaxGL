#include "texture.h"

#include <iostream>
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

Texture::Texture(const char* Path)
{
	glGenTextures(1, &this->_texture);
	assign_texture(this->_texture, Path);
}
void Texture::assign_texture(unsigned int texture, const char* Path)
{
	int width, height, nbrChannels;
	unsigned char* data = stbi_load(Path, &width, &height, &nbrChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum format = 0;
	if (nbrChannels == 1)
		format = GL_RED;
	else if (nbrChannels == 3)
		format = GL_RGB;
	else if (nbrChannels == 4)
		format = GL_RGBA;

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::FAILED::LOADING_TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}
void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->_texture);
}