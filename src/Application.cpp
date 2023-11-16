#include "Application.h"

#include "text.h"
#include "Shader.h"    
#include "vertices.h"
#include "texture.h"
#include "setup.h"
#include "Gui.h"


const char* VertexShaderSource   = "resources/shaders/VertexShader.txt";
const char* FragmentShaderSource = "resources/shaders/FragmentShader.txt";
const char* LineVertexShader     = "resources/shaders/hash_line_vs.txt";
const char* LineFragmentShader   = "resources/shaders/hash_line_fs.txt";
const char* textVertexShader     = "resources/shaders/text_vs.txt";
const char* textFragmentShader   = "resources/shaders/text_fs.txt";

#define Xpng "resources/Textures/x_texture.png"
#define Opng "resources/Textures/o_texture.png"

unsigned int VBO, VAO;
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};


void Render(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, bool& visible, std::map<GLchar, Character> Characters)
{
	// activate corresponding render state	
	if (visible)
	{
		shader.use();
		glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

tictactoe::tictactoe()
{
	std::map<GLchar, Character> Characters;
	GLwindow glwindow;
	//Gui gui(window);
	Shader shader(VertexShaderSource, FragmentShaderSource);
	Shader line(LineVertexShader, LineFragmentShader);

	Shader text(textVertexShader, textFragmentShader);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    text.use();
	glUniformMatrix4fv(glGetUniformLocation(text.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//Text FreeType;
	//FreeType.Init();

	VRTX vertices;
	Texture x_texture(Xpng);
	Texture o_texture(Opng);
	
	double lastTime = 0.0f;
	bool yes = false;

	/*glGenVertexArrays(1, &FreeType.VAO);
	glGenBuffers(1, &FreeType.VBO);
	glBindVertexArray(FreeType.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, FreeType.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/
    //--------------------
    FT_Library ft;
 
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return ;
    }

    FT_Face face;
    if (FT_New_Face(ft, "resources/Fonts/Antonio-Bold.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return ;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
   
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // -----------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //===================
	while (!glfwWindowShouldClose(window))
	{
		//glClearColor(gui.clear_color.x, gui.clear_color.y, gui.clear_color.z, 1.0f);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetTime() - lastTime > 0.5) {
			yes = !yes;
			lastTime = glfwGetTime();
		}

		Render(shader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.2f), yes, Characters);
		Render(shader, "Press Enter", 350.0f, 400.0f, 2.0f, glm::vec3(0.3, 0.7f, 0.9f), yes, Characters);

		glfwSwapBuffers(window);
		glfwPollEvents();
#if 0
		line.use();
		line.SetUniform3f("aColor", gui.Hash_color.x, gui.Hash_color.y, gui.Hash_color.z);
		vertices.DrawLines();

		shader.use();
		shader.SetUniform3f("aColor", gui.clear_color.x, gui.clear_color.y, gui.clear_color.z);
		for (int i = 0; i < 9; i++)
		{
			if (Game::board[i] == 'X')
			{
				x_texture.BindTexture();
				vertices.render(i);
			}
			else if (Game::board[i] == 'O')
			{

				o_texture.BindTexture();
				vertices.render(i);
			}
			else
			{
				shader.SetUniform1i("none", 1);
				vertices.render(i);
				shader.SetUniform1i("none", 0);
			}
		}

		gui.render(counter, win, lost, draw);
		glfwSwapBuffers(window);
		glfwPollEvents();
#endif
	}
	//gui.FinalResult(win, lost, draw);
}


