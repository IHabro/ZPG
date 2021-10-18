#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Includes.h"

class ShaderProgram
{
private:
	VertexShader* vertex;
	FragmentShader* fragment;
	GLuint Program;

public:
	ShaderProgram();
	~ShaderProgram();
	GLuint getShaderProgram();
	GLint getModelMatrix();
};

