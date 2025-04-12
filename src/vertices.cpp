#include "vertices.h"

VRTX::VRTX()
{
	this->_squares();
	this->_Assign();
	this->_BindHashLine();
}
VRTX::~VRTX()
{
	for (int i = 0; i < 9; i++)
	{
		glDeleteBuffers(1, &VRTX::_VBO[i]);
		glDeleteVertexArrays(1, &VRTX::_VAO[i]);
	}
	delete[] squares;
}

void VRTX::render(int index)
{
	glBindVertexArray(this->_VAO[index]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
void VRTX::DrawLines()
{
	glBindVertexArray(this->_lineVAO);
	glDrawArrays(GL_TRIANGLES, 0, 24);
}
void VRTX::_squares()
{
	squares[0] = top_left_square;
	squares[1] = center_up_square;
	squares[2] = top_right_square;
	squares[3] = center_left_square;
	squares[4] = center_square;
	squares[5] = center_right_square;
	squares[6] = bottom_left_square;
	squares[7] = center_down_square;
	squares[8] = bottom_right_square;
}
void VRTX::_Assign()
{
	glGenVertexArrays(9, _VAO);
	glGenBuffers(9, _VBO);
	for (int i = 0; i < 9; i++)
	{
		glBindVertexArray(_VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(const float) * 30, squares[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
void VRTX::_BindHashLine()
{
	glGenVertexArrays(1, &_lineVAO);
	glGenBuffers(1, &_lineVBO);

	glBindVertexArray(_lineVAO);

	glBindBuffer(GL_ARRAY_BUFFER, _lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Hash_lines), Hash_lines, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}