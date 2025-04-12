#pragma once

#include "glad/glad.h"

constexpr float Hash_lines[]
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
constexpr float center_square[]
{
	-0.30f,  0.30f, 0.0f, 0.0f, 1.0f,
	-0.30f, -0.30f, 0.0f, 0.0f, 0.0f,
	 0.30f, -0.30f, 0.0f, 1.0f, 0.0f,
	-0.30f,  0.30f, 0.0f, 0.0f, 1.0f,
	 0.30f,  0.30f, 0.0f, 1.0f, 1.0f,
	 0.30f, -0.30f, 0.0f, 1.0f, 0.0f,
};
constexpr float center_right_square[]
{
	 0.40f,  0.30f ,0.0f, 0.0f, 1.0f,
	 0.40f, -0.30f ,0.0f, 0.0f, 0.0f,
	 1.0f , -0.30f ,0.0f, 1.0f, 0.0f,
	 0.40f,  0.30f ,0.0f, 0.0f, 1.0f,
	 1.0f , -0.30f ,0.0f, 1.0f, 0.0f,
	 1.0f,   0.30f ,0.0f, 1.0f, 1.0f,
};
constexpr float center_up_square[]
{
	 -0.30f, 1.0f , 0.0f, 0.0f, 1.0f,
	 -0.30f, 0.40f, 0.0f, 0.0f, 0.0f,
	  0.30f, 0.40f, 0.0f, 1.0f, 0.0f,
	 -0.30f, 1.0f , 0.0f, 0.0f, 1.0f,
	  0.30f, 0.40f, 0.0f, 1.0f, 0.0f,
	  0.30f, 1.0f , 0.0f, 1.0f, 1.0f,
};
constexpr float center_down_square[]
{
	 -0.30f, -1.0f  , 0.0f, 0.0f, 0.0f,
	 -0.30f, -0.40f , 0.0f, 0.0f, 1.0f,
	  0.30f, -0.40f , 0.0f, 1.0f, 1.0f,
	 -0.30f, -1.0f  , 0.0f, 0.0f, 0.0f,
	  0.30f, -0.40f , 0.0f, 1.0f, 1.0f,
	  0.30f, -1.0f  , 0.0f, 1.0f, 0.0f,
};
constexpr float center_left_square[]
{
	  -0.40f,  0.30f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -0.30f , 0.0f, 1.0f, 0.0f,
	  -1.0f , -0.30f , 0.0f, 0.0f, 0.0f,
	  -0.40f,  0.30f , 0.0f, 1.0f, 1.0f,
	  -1.0f , -0.30f , 0.0f, 0.0f, 0.0f,
	  -1.0f,   0.30f , 0.0f, 0.0f, 1.0f,
};
constexpr float top_left_square[]
{
	  -1.0f,  1.0f  , 0.0f, 0.0f, 1.0f,
	  -1.0f,  0.40f , 0.0f, 0.0f, 0.0f,
	  -0.40f, 0.40f , 0.0f, 1.0f, 0.0f,
	  -0.40f, 0.40f , 0.0f, 1.0f, 0.0f,
	  -0.40f, 1.0f  , 0.0f, 1.0f, 1.0f,
	  -1.0f,  1.0f  , 0.0f, 0.0f, 1.0f,
};
constexpr float top_right_square[]
{
	  1.0f,  1.0f  , 0.0f, 1.0f, 1.0f,
	  1.0f,  0.40f , 0.0f, 1.0f, 0.0f,
	  0.40f, 0.40f , 0.0f, 0.0f, 0.0f,
	  0.40f, 0.40f , 0.0f, 0.0f, 0.0f,
	  0.40f, 1.0f  , 0.0f, 0.0f, 1.0f,
	  1.0f,  1.0f  , 0.0f, 1.0f, 1.0f,
};
constexpr float bottom_left_square[]
{
	  -1.0f,  -1.0f  , 0.0f, 0.0f, 0.0f,
	  -1.0f,  -0.40f , 0.0f, 0.0f, 1.0f,
	  -0.40f, -0.40f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -0.40f , 0.0f, 1.0f, 1.0f,
	  -0.40f, -1.0f  , 0.0f, 1.0f, 0.0f,
	  -1.0f,  -1.0f  , 0.0f, 0.0f, 0.0f,
};
constexpr float bottom_right_square[]
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
	void _BindHashLine();
	void _squares();
	unsigned int _VAO[9], _VBO[9], _lineVAO, _lineVBO;
	const float** squares = new const float* [9];
};