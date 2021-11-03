#pragma once

#include "Includes.h"

class FragmentShader
{
private:
	const char* fragment_shader;
	GLuint fragmentShaderId;

public:
	FragmentShader();
	~FragmentShader();
	GLuint GetFragmentShader();
};

