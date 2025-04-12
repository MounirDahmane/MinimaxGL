#pragma once

#include <chrono>
#include <iostream>
#include "GLFW/glfw3.h"

namespace Game
{
#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

	static int Game_over = 0;
	static char Turn = PLAYER_MARKER;
	char board[9] = {'-', '-', '-',
					 '-', '-', '-',
					 '-', '-', '-' };

	int Check_Game()
	{
		// check rows and columns
		for (int i = 0; i < 3; i++)
		{
			if (board[(i * 3)] == board[(i * 3) + 1] && board[(i * 3) + 1] == board[(i * 3) + 2] && board[(i * 3) + 2] != '-')
			{
				Game_over = 1;
				return (board[(i * 3) + 2] == 'X') ? WIN : LOSS;
			}
			else if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i + 6] != '-')
			{
				Game_over = 1;
				return (board[i + 6] == 'X') ? WIN : LOSS;
			}
		}
		// checking diagnols
		if (board[0] == board[4] && board[4] == board[8] && board[8] != '-')
		{
			Game_over = 1;
			return (board[8] == 'X') ? WIN : LOSS;
		}
		if (board[2] == board[4] && board[4] == board[6] && board[6] != '-')
		{
			Game_over = 1;
			return (board[6] == 'X') ? WIN : LOSS;
		}
		// check if the game has been ended in draw
		int counter = 0;
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == 'X' || board[i] == 'O')
				counter++;
		}
		if (counter == 9)
			return DRAW;

		return 1;
	}
	void Final_Game_State()
	{
		system("cls");
		int state = Check_Game();
		if (state == WIN)
			std::cout << "THE PLAYER X HAS WON" << std::endl;
		else if (state == LOSS)
			std::cout << "THE PLAYER O HAS WON" << std::endl;
		else
			std::cout << "IT IS A DRAW" << std::endl;
	}
	int Evaluate(char player)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
				return WIN;
			if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player)
				return WIN;
		}
		if (board[0] == player && board[4] == player && board[8] == player)
			return WIN;
		if (board[2] == player && board[4] == player && board[6] == player)
			return WIN;

		return DRAW;
	}
	int Minimax(char player)
	{
		int score = Evaluate(AI_MARKER);
		if (score == WIN)
			return score;

		score = Evaluate(PLAYER_MARKER);
		if (score == WIN)
			return -score;

		int emptyCells = 0;
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == EMPTY_SPACE)
				emptyCells++;
		}

		if (emptyCells == 0)
			return DRAW;

		if (player == AI_MARKER)
		{
			int bestScore = -10000;
			for (int i = 0; i < 9; i++)
			{
				if (board[i] == EMPTY_SPACE)
				{
					board[i] = AI_MARKER;
					int score = Minimax(PLAYER_MARKER);
					board[i] = EMPTY_SPACE;
					bestScore = std::max(score, bestScore);
				}
			}
			return bestScore;
		}
		else
		{
			int bestScore = 10000;
			for (int i = 0; i < 9; i++)
			{
				if (board[i] == EMPTY_SPACE)
				{
					board[i] = PLAYER_MARKER;
					int score = Minimax(AI_MARKER);
					board[i] = EMPTY_SPACE;
					bestScore = std::min(score, bestScore);
				}
			}
			return bestScore;
		}
	}
	int GetBestMove(char board[9], char player)
	{
		int bestMove = -1;
		int bestScore = -10000;

		for (int i = 0; i < 9; i++)
		{
			if (board[i] == EMPTY_SPACE)
			{
				board[i] = AI_MARKER;
				int score = Minimax(PLAYER_MARKER);
				board[i] = EMPTY_SPACE;
				if (score > bestScore)
				{
					bestScore = score;
					bestMove = i;
				}
			}
		}
		return bestMove;
	}

	void reset(int& counter)
	{
		for (std::size_t i = 0; i < 9; i++)
			board[i] = EMPTY_SPACE;
		counter = 0;
		Turn = PLAYER_MARKER;
	}
	void repeat(int& counter, GLFWwindow* window)
	{
		std::cout << "Game_Over : ";
		Final_Game_State();
		std::cout << "Do You Want To Play Again : " << std::endl << "press 'y' for yes else for no :";
		char again;
		std::cin >> again;
		again = toupper(again);
		if (again == 'Y')
		{
			reset(counter);
			system("cls");
		}
		else
		{
			glfwSetWindowShouldClose(window, true);
			system("cls");
		}
	}
	void logic(int Pos, GLFWwindow* window, int& counter)
	{
		if (Turn == PLAYER_MARKER)
		{
			if (board[Pos] != '-')
				return;
			board[Pos] = Turn;
			Turn = AI_MARKER;
			counter++;
		}
	}
	void AI(GLFWwindow* window, int& counter)
	{
		if (Turn == AI_MARKER)
		{
			auto ai_move = GetBestMove(board, AI_MARKER);
			if (board[ai_move] != '-')
				return;
			board[ai_move] = Turn;
			Turn = PLAYER_MARKER;
			if (counter != 9)
				counter++;
		}
	}
}