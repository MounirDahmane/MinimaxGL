#include "vertices.h"

// --- PRIVATE FILE DATA ---
// Wrapping these in an anonymous namespace prevents naming collisions
// in other files and keeps them strictly internal to vertices.cpp.
namespace
{
constexpr float Hash_lines[]{
    // vertical up
    1.0f,
    0.40f,
    0.0f,
    1.0f,
    0.30f,
    0.0f,
    -1.0f,
    0.40f,
    0.0f,
    -1.0f,
    0.40f,
    0.0f,
    1.0f,
    0.30f,
    0.0f,
    -1.0f,
    0.30f,
    0.0f,
    // vertical down
    1.0f,
    -0.40f,
    0.0f,
    1.0f,
    -0.30f,
    0.0f,
    -1.0f,
    -0.40f,
    0.0f,
    -1.0f,
    -0.40f,
    0.0f,
    1.0f,
    -0.30f,
    0.0f,
    -1.0f,
    -0.30f,
    0.0f,
    // hortizontal left
    -0.40f,
    1.0f,
    0.0f,
    -0.30f,
    1.0f,
    0.0f,
    -0.30f,
    -1.0f,
    0.0f,
    -0.40f,
    1.0f,
    0.0f,
    -0.40f,
    -1.0f,
    0.0f,
    -0.30f,
    -1.0f,
    0.0f,
    // horizontal right
    0.40f,
    1.0f,
    0.0f,
    0.30f,
    1.0f,
    0.0f,
    0.30f,
    -1.0f,
    0.0f,
    0.40f,
    1.0f,
    0.0f,
    0.40f,
    -1.0f,
    0.0f,
    0.30f,
    -1.0f,
    0.0f,
};

// Square Data (X, Y, Z, U, V)
constexpr float top_left_square[]{-1.0f,  1.0f,  0.0f, 0.0f, 1.0f, -1.0f,  0.40f, 0.0f, 0.0f, 0.0f,
                                  -0.40f, 0.40f, 0.0f, 1.0f, 0.0f, -0.40f, 0.40f, 0.0f, 1.0f, 0.0f,
                                  -0.40f, 1.0f,  0.0f, 1.0f, 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f};
constexpr float center_up_square[]{-0.30f, 1.0f,  0.0f,  0.0f,  1.0f,  -0.30f, 0.40f, 0.0f,
                                   0.0f,   0.0f,  0.30f, 0.40f, 0.0f,  1.0f,   0.0f,  -0.30f,
                                   1.0f,   0.0f,  0.0f,  1.0f,  0.30f, 0.40f,  0.0f,  1.0f,
                                   0.0f,   0.30f, 1.0f,  0.0f,  1.0f,  1.0f};
constexpr float top_right_square[]{1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  0.40f, 0.0f, 1.0f, 0.0f,
                                   0.40f, 0.40f, 0.0f, 0.0f, 0.0f, 0.40f, 0.40f, 0.0f, 0.0f, 0.0f,
                                   0.40f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f,  0.0f, 1.0f, 1.0f};
constexpr float center_left_square[]{-0.40f, 0.30f, 0.0f,  1.0f,   1.0f,  -0.40f, -0.30f, 0.0f,
                                     1.0f,   0.0f,  -1.0f, -0.30f, 0.0f,  0.0f,   0.0f,   -0.40f,
                                     0.30f,  0.0f,  1.0f,  1.0f,   -1.0f, -0.30f, 0.0f,   0.0f,
                                     0.0f,   -1.0f, 0.30f, 0.0f,   0.0f,  1.0f};
constexpr float center_square[]{-0.30f, 0.30f,  0.0f, 0.0f, 1.0f, -0.30f, -0.30f, 0.0f, 0.0f, 0.0f,
                                0.30f,  -0.30f, 0.0f, 1.0f, 0.0f, -0.30f, 0.30f,  0.0f, 0.0f, 1.0f,
                                0.30f,  0.30f,  0.0f, 1.0f, 1.0f, 0.30f,  -0.30f, 0.0f, 1.0f, 0.0f};
constexpr float center_right_square[]{0.40f, 0.30f, 0.0f,  0.0f,   1.0f, 0.40f,  -0.30f, 0.0f,
                                      0.0f,  0.0f,  1.0f,  -0.30f, 0.0f, 1.0f,   0.0f,   0.40f,
                                      0.30f, 0.0f,  0.0f,  1.0f,   1.0f, -0.30f, 0.0f,   1.0f,
                                      0.0f,  1.0f,  0.30f, 0.0f,   1.0f, 1.0f};
constexpr float bottom_left_square[]{-1.0f,  -1.0f, 0.0f,   0.0f,   0.0f,   -1.0f, -0.40f, 0.0f,
                                     0.0f,   1.0f,  -0.40f, -0.40f, 0.0f,   1.0f,  1.0f,   -0.40f,
                                     -0.40f, 0.0f,  1.0f,   1.0f,   -0.40f, -1.0f, 0.0f,   1.0f,
                                     0.0f,   -1.0f, -1.0f,  0.0f,   0.0f,   0.0f};
constexpr float center_down_square[]{-0.30f, -1.0f, 0.0f,  0.0f,   0.0f,  -0.30f, -0.40f, 0.0f,
                                     0.0f,   1.0f,  0.30f, -0.40f, 0.0f,  1.0f,   1.0f,   -0.30f,
                                     -1.0f,  0.0f,  0.0f,  0.0f,   0.30f, -0.40f, 0.0f,   1.0f,
                                     1.0f,   0.30f, -1.0f, 0.0f,   1.0f,  0.0f};
constexpr float bottom_right_square[]{1.0f,   -1.0f, 0.0f,  1.0f,   0.0f,  1.0f,  -0.40f, 0.0f,
                                      1.0f,   1.0f,  0.40f, -0.40f, 0.0f,  0.0f,  1.0f,   0.40f,
                                      -0.40f, 0.0f,  0.0f,  1.0f,   0.40f, -1.0f, 0.0f,   0.0f,
                                      0.0f,   1.0f,  -1.0f, 0.0f,   1.0f,  0.0f};
} // namespace

// --- IMPLEMENTATION ---

VRTX::VRTX()
{
    // Initialize the modern array (replaces dynamic allocation / new)
    _squares = {
        top_left_square,
        center_up_square,
        top_right_square,
        center_left_square,
        center_square,
        center_right_square,
        bottom_left_square,
        center_down_square,
        bottom_right_square};

    this->_Assign();
    this->_BindHashLine();
}

VRTX::~VRTX()
{
    // Optimized: glDelete handles entire arrays natively, no for-loop needed!
    glDeleteBuffers(9, _VBO);
    glDeleteVertexArrays(9, _VAO);

    glDeleteBuffers(1, &_lineVBO);
    glDeleteVertexArrays(1, &_lineVAO);
}

void VRTX::render(int index)
{
    // Added a bounds check to prevent crashing if a bad index is passed
    if (index < 0 || index > 8)
        return;

    glBindVertexArray(this->_VAO[index]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0); // Safely unbind
}

void VRTX::DrawLines()
{
    glBindVertexArray(this->_lineVAO);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glBindVertexArray(0); // Safely unbind
}

void VRTX::_Assign()
{
    glGenVertexArrays(9, _VAO);
    glGenBuffers(9, _VBO);

    for (int i = 0; i < 9; i++)
    {
        glBindVertexArray(_VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO[i]);
        // 30 floats total per square (6 vertices * 5 attributes)
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, _squares[i], GL_STATIC_DRAW);

        // Position Attribute (X, Y, Z)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // Texture Attribute (U, V)
        glVertexAttribPointer(
            1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // Clean up bindings to prevent accidental modification elsewhere
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VRTX::_BindHashLine()
{
    glGenVertexArrays(1, &_lineVAO);
    glGenBuffers(1, &_lineVBO);

    glBindVertexArray(_lineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Hash_lines), Hash_lines, GL_STATIC_DRAW);

    // Position Attribute only (X, Y, Z) - No textures for lines
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}