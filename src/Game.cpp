/**
 * @file Game.cpp
 * @brief Implementation of the Tic-Tac-Toe game logic and AI.
 */

#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace Game
{
// --- Memory Allocation for Globals ---
int Game_over = 0;
char Turn = PLAYER_MARKER;
char board[9] = {
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE,
    EMPTY_SPACE};

int error_chance = 40;

// --- Implementation ---

int Check_Game()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[(i * 3)] == board[(i * 3) + 1] && board[(i * 3) + 1] == board[(i * 3) + 2] &&
            board[(i * 3) + 2] != EMPTY_SPACE)
        {
            Game_over = 1;
            return (board[(i * 3) + 2] == PLAYER_MARKER) ? WIN : LOSS;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i + 6] != EMPTY_SPACE)
        {
            Game_over = 1;
            return (board[i + 6] == PLAYER_MARKER) ? WIN : LOSS;
        }
    }

    // Check diagonals
    if (board[0] == board[4] && board[4] == board[8] && board[8] != EMPTY_SPACE)
    {
        Game_over = 1;
        return (board[8] == PLAYER_MARKER) ? WIN : LOSS;
    }
    if (board[2] == board[4] && board[4] == board[6] && board[6] != EMPTY_SPACE)
    {
        Game_over = 1;
        return (board[6] == PLAYER_MARKER) ? WIN : LOSS;
    }

    // Check for draw
    int piece_counter = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == PLAYER_MARKER || board[i] == AI_MARKER)
            piece_counter++;
    }

    if (piece_counter == 9)
        return DRAW;

    return 1;
}

int Evaluate(char player)
{
    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return WIN;
        if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player)
            return WIN;
    }

    // Check diagonals
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
                bestScore = std::max(Minimax(PLAYER_MARKER), bestScore);
                board[i] = EMPTY_SPACE;
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
                bestScore = std::min(Minimax(AI_MARKER), bestScore);
                board[i] = EMPTY_SPACE;
            }
        }
        return bestScore;
    }
}

int GetBestMove(char *current_board, char player)
{
    // 1. Initialize random seed once
    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    // 2. The Dumbness Logic: Chance to pick a random empty square
    if (rand() % 100 < error_chance)
    {
        int empty_spots[9];
        int count = 0;
        for (int i = 0; i < 9; i++)
        {
            if (current_board[i] == EMPTY_SPACE)
            {
                empty_spots[count++] = i;
            }
        }
        if (count > 0)
            return empty_spots[rand() % count];
    }

    // 3. The Smart Logic: Minimax
    int bestMove = -1;
    int bestScore = -10000;

    for (int i = 0; i < 9; i++)
    {
        if (current_board[i] == EMPTY_SPACE)
        {
            current_board[i] = AI_MARKER;
            int score = Minimax(PLAYER_MARKER);
            current_board[i] = EMPTY_SPACE;

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void reset(int &counter)
{
    for (std::size_t i = 0; i < 9; i++)
        board[i] = EMPTY_SPACE;

    counter = 0;
    Turn = PLAYER_MARKER;
    Game_over = 0;
}

void logic(int Pos, GLFWwindow *window, int &counter)
{
    if (Turn == PLAYER_MARKER)
    {
        if (board[Pos] != EMPTY_SPACE)
            return;

        board[Pos] = Turn;
        Turn = AI_MARKER;
        counter++;
    }
}

void AI(GLFWwindow *window, int &counter)
{
    if (Turn == AI_MARKER)
    {
        int ai_move = GetBestMove(board, AI_MARKER);
        if (ai_move != -1 && board[ai_move] == EMPTY_SPACE)
        {
            board[ai_move] = Turn;
            Turn = PLAYER_MARKER;
            if (counter != 9)
                counter++;
        }
    }
}
} // namespace Game