#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->vertex = new VertexShader();
	this->fragment = new FragmentShader();

	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->fragment->GetFragmentShader());
	glAttachShader(this->Program, this->vertex->GetVertexShader());
	glLinkProgram(this->Program);
}

ShaderProgram::~ShaderProgram()
{
	delete this->vertex;
	delete this->fragment;
}

GLuint ShaderProgram::getShaderProgram()
{
	return this->Program;
}
