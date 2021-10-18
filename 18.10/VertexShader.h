#pragma once

#include "Includes.h"

class VertexShader
{
private:
	const char* vertex_shader;
	GLuint vertexShader;

public:
	VertexShader();
	~VertexShader();
	GLuint GetVertexShader();
};

