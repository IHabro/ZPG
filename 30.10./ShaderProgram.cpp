#include "ShaderProgram.h"

//ShaderProgram(Camera* cam);
ShaderProgram::ShaderProgram()
{
	this->vertex = new VertexShader();
	this->fragment = new FragmentShader();

	this->ProgramId = glCreateProgram();
	glAttachShader(this->ProgramId, this->fragment->GetFragmentShader());
	glAttachShader(this->ProgramId, this->vertex->GetVertexShader());
	glLinkProgram(this->ProgramId);
}

ShaderProgram::~ShaderProgram()
{
	delete this->vertex;
	delete this->fragment;
}

GLuint ShaderProgram::GetShaderProgramId()
{
	return this->ProgramId;
}

GLint ShaderProgram::GetModelMatrix(const GLchar* name)
{
	GLint returnedLocation = glGetUniformLocation(this->GetShaderProgramId(), name);

	if (returnedLocation != -1)
	{
		return returnedLocation;
	}

	return returnedLocation;
}
