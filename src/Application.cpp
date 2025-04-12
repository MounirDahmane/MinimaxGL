#include "Application.h"

#include "Shader.h"    
#include "vertices.h"
#include "texture.h"
#include "setup.h"
#include "Gui.h"

const char* VertexShaderSource   = "resources/shaders/VertexShader.txt";
const char* FragmentShaderSource = "resources/shaders/FragmentShader.txt";
const char* LineVertexShader	 = "resources/shaders/hash_line_vs.txt";
const char* LineFragmentShader	 = "resources/shaders/hash_line_fs.txt";

#define Xpng "resources/Textures/x_texture.png"
#define Opng "resources/Textures/o_texture.png"

tictactoe::tictactoe()
{
	GLwindow glwindow;
	Gui gui(window);
	Shader shader(VertexShaderSource, FragmentShaderSource);
	Shader line(LineVertexShader, LineFragmentShader);

	VRTX vertices;
	Texture x_texture(Xpng);
	Texture o_texture(Opng);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(gui.clear_color.x, gui.clear_color.y, gui.clear_color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ProcessInput(window);

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
	}
	gui.FinalResult(win, lost, draw);
}