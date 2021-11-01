#include "ShaderProgram.h"

//ShaderProgram(Camera* cam);
ShaderProgram::ShaderProgram()
{
	this->vertex = new VertexShader();
	this->fragment = new FragmentShader();
	this->camera = nullptr;

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
	GLint returnedLocation = glGetUniformLocation(this->ProgramId, name);

	if (returnedLocation != -1)
	{
		return returnedLocation;
	}

	return returnedLocation;
}

void ShaderProgram::Activate()
{
	glUseProgram(this->ProgramId);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::CheckStatus()
{
	GLint status;
	glGetProgramiv(this->ProgramId, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->ProgramId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::SetLightPosition(glm::vec3 position)
{
	glUniform3fv(glGetUniformLocation(this->ProgramId, "lightPosition"), 1, glm::value_ptr(position));
}

void ShaderProgram::SetCameraPosition(glm::vec3 position)
{
	glUniform3fv(glGetUniformLocation(this->ProgramId, "viewPosition"), 1, glm::value_ptr(position));
}

