#pragma once

#include "Includes.h"

class VertexShader
{
private:
	const char* vertex_shader;
	GLuint vertexShaderId;

public:
	VertexShader();
	~VertexShader();
	GLuint GetVertexShader();
};

