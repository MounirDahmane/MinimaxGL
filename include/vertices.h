#pragma once

#include <array>
#include <glad/glad.h>

/**
 * @class VRTX
 * @brief Manages the Vertex Array Objects (VAOs) and Vertex Buffer Objects (VBOs)
 * for rendering the Tic-Tac-Toe grid and its 9 playable squares.
 * * Grid Layout Indexing:
 * 0 | 1 | 2
 * ---------
 * 3 | 4 | 5
 * ---------
 * 6 | 7 | 8
 */
class VRTX
{
public:
    /**
     * @brief Constructor initializes OpenGL buffers and uploads vertex data to the GPU.
     */
    VRTX();

    /**
     * @brief Destructor safely cleans up the VAOs and VBOs from GPU memory.
     */
    ~VRTX();

    /**
     * @brief Renders a specific square on the board.
     * @param index The index of the square to render (0-8).
     */
    void render(int index);

    /**
     * @brief Renders the main Tic-Tac-Toe grid lines (the hashtag).
     */
    void DrawLines();

private:
    /**
     * @brief Generates and binds VAOs/VBOs for the 9 playable squares.
     */
    void _Assign();

    /**
     * @brief Generates and binds the VAO/VBO for the grid lines.
     */
    void _BindHashLine();

    // OpenGL Object IDs
    unsigned int _VAO[9];  ///< Vertex Array Objects for the 9 squares
    unsigned int _VBO[9];  ///< Vertex Buffer Objects for the 9 squares
    unsigned int _lineVAO; ///< Vertex Array Object for the grid lines
    unsigned int _lineVBO; ///< Vertex Buffer Object for the grid lines

    // Modern C++ array to hold pointers to the vertex data, replacing raw 'new' allocation
    std::array<const float *, 9> _squares;
};