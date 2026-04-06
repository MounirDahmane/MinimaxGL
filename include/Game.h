/**
 * @file Game.h
 * @brief Core game logic, state management, and Minimax AI for Tic-Tac-Toe.
 */

#pragma once

#include <GLFW/glfw3.h>

namespace Game
{
// Modern C++ constants replacing legacy #define macros
constexpr int WIN = 1000;
constexpr int DRAW = 0;
constexpr int LOSS = -1000;

constexpr char AI_MARKER = 'O';
constexpr char PLAYER_MARKER = 'X';
constexpr char EMPTY_SPACE = '-';

// Extern declarations for global game state
extern int Game_over;
extern char Turn;
extern char board[9];
extern int error_chance;

/**
 * @brief Evaluates the current board to check for a win, loss, draw, or continuation.
 * @return WIN, LOSS, DRAW, or 1 if the game is still ongoing.
 */
int Check_Game();

/**
 * @brief Evaluates the board specifically for the AI Minimax algorithm.
 * @param player The marker of the player to evaluate for.
 * @return WIN if the player won, DRAW otherwise.
 */
int Evaluate(char player);

/**
 * @brief Recursive Minimax algorithm to calculate the best possible score.
 * @param player The current player's turn in the simulation.
 * @return The best possible score for the given branch.
 */
int Minimax(char player);

/**
 * @brief Determines the optimal next move for the AI.
 * @param current_board Pointer to the current game board array.
 * @param player The AI's marker.
 * @return The integer index (0-8) of the best move.
 */
int GetBestMove(char *current_board, char player);

/**
 * @brief Resets the board and game state for a new round.
 * @param counter Reference to the global turn counter.
 */
void reset(int &counter);

/**
 * @brief Processes a human player's move.
 * @param Pos The index (0-8) where the player clicked.
 * @param window The active GLFW window.
 * @param counter Reference to the global turn counter.
 */
void logic(int Pos, GLFWwindow *window, int &counter);

/**
 * @brief Executes the AI's turn using the Minimax algorithm.
 * @param window The active GLFW window.
 * @param counter Reference to the global turn counter.
 */
void AI(GLFWwindow *window, int &counter);
} // namespace Game