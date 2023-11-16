#pragma once
#include "Game.h"
#include "glad/glad.h"

unsigned int width = 800;
unsigned int height = 800;
int  counter = 0;

unsigned int win = 0;
unsigned int lost = 0;
unsigned int draw = 0;

GLFWwindow* window;


void Game_Result()
{
	int state = Game::Check_Game();
	if (state == WIN)
		win++;
	else if (state == LOSS)
		lost = lost + 1;
	else if (state == DRAW)
		draw++;
}
void FrameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (Game::Check_Game() != 1 || counter == 9)
	{
		Game_Result();
		Game::repeat(counter, window);
	}
		
	if (button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_RELEASE)
	{
		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);

		if (x < 240 && y < 235)
			Game::logic(0, window,  counter);
		else if (280 < x && x < 515 && y < 235)
			Game::logic(1, window,  counter);
		else if (560 < x && x < 800 && y < 235)
			Game::logic(2, window,  counter);
		else if (x < 240 && 280 < y && y < 520)
			Game::logic(3, window,  counter);
		else if (280 < x && x < 515 && 280 < y && y < 515)
			Game::logic(4, window,  counter);
		else if (560 < x && x < 800 && 280 < y && y < 516)
			Game::logic(5, window,  counter);
		else if (x < 240 && 560 < y && y < 800)
			Game::logic(6, window,  counter);
		else if (280 < x && x < 520 && 560 < y && y < 800)
			Game::logic(7, window,  counter);
		else if (560 < x && x < 800 && 560 < y && y < 800)
			Game::logic(8, window,  counter);
	}
	Game::AI(window,  counter);
}
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		Game::reset( counter);
}


class GLwindow
{
public:
	GLwindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "TicTacToe", NULL, NULL);

		if (window == NULL)
		{
			std::cout << "ERROR::FAILED::LODADING_GLFW_WINDOW" << std::endl;
			glfwTerminate();
			return ;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, FrameBuffer_size_callback);
		glfwSetMouseButtonCallback(window, mouse_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "ERROR::FAILED_LOADING_GLAD" << std::endl;
		}
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	~GLwindow()
	{
		glfwTerminate();
	}
};