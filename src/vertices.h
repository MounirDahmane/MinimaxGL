#pragma once

#include "glad/glad.h"

const float Hash_lines[]
{
	// vertical up :
	 1.0f,  0.40f, 0.0f,
	 1.0f,  0.30f, 0.0f,
	-1.0f,  0.40f, 0.0f,

	-1.0f,  0.40f, 0.0f,
	 1.0f,  0.30f, 0.0f,
	-1.0f,  0.30f, 0.0f,

	//vertical down :
	 1.0f, -0.40f, 0.0f,
	 1.0f, -0.30f, 0.0f,
	-1.0f, -0.40f, 0.0f,

	-1.0f, -0.40f, 0.0f,
	 1.0f, -0.30f, 0.0f,
	-1.0f, -0.30f, 0.0f,

	// hortizontal left :
	-0.40f,  1.0f, 0.0f,
	-0.30f,  1.0f, 0.0f,
	-0.30f, -1.0f, 0.0f,

	-0.40f,  1.0f, 0.0f,
	-0.40f, -1.0f, 0.0f,
	-0.30f, -1.0f, 0.0f,

	// horizontal right :
	 0.40f,  1.0f, 0.0f,
	 0.30f,  1.0f, 0.0f,
	 0.30f, -1.0f, 0.0f,

	 0.40f,  1.0f, 0.0f,
	 0.40f, -1.0f, 0.0f,
	 0.30f, -1.0f, 0.0f,

};
const float center_square[]
{
	-0.30f,  0.30f, 0.0f, 0.0f, 1.0f,
	-0.30f, -0.30f, 0.0f, 0.0f, 0.0f,
	 0.30f, -0.30f, 0.0f, 1.0f, 0.0f,
	-0.30f,  0.30f, 0.0f, 0.0f, 1.0f,
	 0.30f,  0.30f, 0.0f, 1.0f, 1.0f,
	 0.30f, -0.30f, 0.0f, 1.0f, 0.0f,
};
const float center_right_square[]
{
	 0.40f,  0.30f ,0.0f, 0.0f, 1.0f,
	 0.40f, -0.30f ,0.0f, 0.0f, 0.0f,
	 1.0f , -0.30f ,0.0f, 1.0f, 0.0f,
	 0.40f,  0.30f ,0.0f, 0.0f, 1.0f,
	 1.0f , -0.30f ,0.0f, 1.0f, 0.0f,
	 1.0f,   0.30f ,0.0f, 1.0f, 1.0f,
};
const float center_up_square[]
{
	 -0.30f, 1.0f , 0.0f, 0.0f, 1.0f,
	 -0.30f, 0.40f, 0.0f, 0.0f, 0.0f,
	  0.30f, 0.40f, 0.0f, 1.0f, 0.0f,
	 -0.30f, 1.0f , 0.0f, 0.0f, 1.0f,
	  0.30f, 0.40f, 0.0f, 1.0f, 0.0f,
	  0.30f, 1.0f , 0.0f, 1.0f, 1.0f,
};
const float center_down_square[]
{
	 -0.30f, -1.0f  , 0.0f, 0.0f, 0.0f,
	 -0.30f, -0.40f , 0.0f, 0.0f, 1.0f,
	  0.30f, -0.40f , 0.0f, 1.0f, 1.0f,
	 -0.30f, -1.0f  , 0.0f, 0.0f, 0.0f,
	  0.30f, -0.40f , 0.0f, 1.0f, 1.0f,
	  0.30f, -1.0f  , 0.0f, 1.0f, 0.0f,
};
const float center_left_square[]
{
	  -0.40f,  0.30f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -0.30f , 0.0f, 1.0f, 0.0f,
	  -1.0f , -0.30f , 0.0f, 0.0f, 0.0f,
	  -0.40f,  0.30f , 0.0f, 1.0f, 1.0f,
	  -1.0f , -0.30f , 0.0f, 0.0f, 0.0f,
	  -1.0f,   0.30f , 0.0f, 0.0f, 1.0f,
};
const float top_left_square[]
{
	  -1.0f,  1.0f  , 0.0f, 0.0f, 1.0f,
	  -1.0f,  0.40f , 0.0f, 0.0f, 0.0f,
	  -0.40f, 0.40f , 0.0f, 1.0f, 0.0f,
	  -0.40f, 0.40f , 0.0f, 1.0f, 0.0f,
	  -0.40f, 1.0f  , 0.0f, 1.0f, 1.0f,
	  -1.0f,  1.0f  , 0.0f, 0.0f, 1.0f,
};
const float top_right_square[]
{
	  1.0f,  1.0f  , 0.0f, 1.0f, 1.0f,
	  1.0f,  0.40f , 0.0f, 1.0f, 0.0f,
	  0.40f, 0.40f , 0.0f, 0.0f, 0.0f,
	  0.40f, 0.40f , 0.0f, 0.0f, 0.0f,
	  0.40f, 1.0f  , 0.0f, 0.0f, 1.0f,
	  1.0f,  1.0f  , 0.0f, 1.0f, 1.0f,
};
const float bottom_left_square[]
{
	  -1.0f,  -1.0f  , 0.0f, 0.0f, 0.0f,
	  -1.0f,  -0.40f , 0.0f, 0.0f, 1.0f,
	  -0.40f, -0.40f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -0.40f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -1.0f  , 0.0f, 1.0f, 0.0f,
	  -1.0f,  -1.0f  , 0.0f, 0.0f, 0.0f,
};
const float bottom_right_square[]
{
	  1.0f,  -1.0f  , 0.0f, 1.0f, 0.0f,
	  1.0f,  -0.40f , 0.0f, 1.0f, 1.0f,
	  0.40f, -0.40f , 0.0f, 0.0f, 1.0f,
	  0.40f, -0.40f , 0.0f, 0.0f, 1.0f,
	  0.40f, -1.0f  , 0.0f, 0.0f, 0.0f,
	  1.0f,  -1.0f  , 0.0f, 1.0f, 0.0f,
};

// 0 | 1 | 2
// _________
// 3 | 4 | 5
// _________
// 6 | 7 | 8

class VRTX
{
public:

	VRTX();
	~VRTX();
	void render(int index);
	void DrawLines();

private:

	void _Assign();
	void _BindVertexArray(int index);
	void _BindHashLine();
	void _squares();
	//void _BindText();
	unsigned int _VAO[9], _VBO[9], _lineVAO, _lineVBO;
	const float** squares = new const float* [9];
};
