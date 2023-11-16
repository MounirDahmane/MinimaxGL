#pragma once 

//#include "glad/glad.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H




// struct Text
//{
//    void Init()
//    {
//        FT_Library ft;
//
//        if (FT_Init_FreeType(&ft))
//        {
//            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//            return;
//        }
//
//        FT_Face face;
//        if (FT_New_Face(ft, "resources/Fonts/Antonio-Bold.ttf", 0, &face)) {
//            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//            return;
//        }
//        else {
//
//            FT_Set_Pixel_Sizes(face, 0, 48);
//
//            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//            for (unsigned char c = 0; c < 128; c++)
//            {
//                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//                {
//                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//                    continue;
//                }
//
//                unsigned int texture;
//                glGenTextures(1, &texture);
//                glBindTexture(GL_TEXTURE_2D, texture);
//                glTexImage2D(
//                    GL_TEXTURE_2D,
//                    0,
//                    GL_RED,
//                    face->glyph->bitmap.width,
//                    face->glyph->bitmap.rows,
//                    0,
//                    GL_RED,
//                    GL_UNSIGNED_BYTE,
//                    face->glyph->bitmap.buffer
//                );
//
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//                Character character = {
//                    texture,
//                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                    static_cast<unsigned int>(face->glyph->advance.x)
//                };
//                Characters.insert(std::pair<char, Character>(c, character));
//            }
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//
//        FT_Done_Face(face);
//        FT_Done_FreeType(ft);
//    }
//    void Render(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, bool& visible)
//    {
//        // activate corresponding render state	
//        if (visible)
//        {
//            shader.use();
//            glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
//            glActiveTexture(GL_TEXTURE0);
//            glBindVertexArray(this->VAO);
//
//            // iterate through all characters
//            std::string::const_iterator c;
//            for (c = text.begin(); c != text.end(); c++)
//            {
//                Character ch = Characters[*c];
//
//                float xpos = x + ch.Bearing.x * scale;
//                float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//                float w = ch.Size.x * scale;
//                float h = ch.Size.y * scale;
//                // update VBO for each character
//                float vertices[6][4] = {
//                    { xpos,     ypos + h,   0.0f, 0.0f },
//                    { xpos,     ypos,       0.0f, 1.0f },
//                    { xpos + w, ypos,       1.0f, 1.0f },
//
//                    { xpos,     ypos + h,   0.0f, 0.0f },
//                    { xpos + w, ypos,       1.0f, 1.0f },
//                    { xpos + w, ypos + h,   1.0f, 0.0f }
//                };
//                // render glyph texture over quad
//                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//                // update content of VBO memory
//                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
//
//                glBindBuffer(GL_ARRAY_BUFFER, 0);
//                // render quad
//                glDrawArrays(GL_TRIANGLES, 0, 6);
//                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//                x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//            }
//            glBindVertexArray(0);
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//    }
//
//    unsigned int VAO, VBO;
//};
