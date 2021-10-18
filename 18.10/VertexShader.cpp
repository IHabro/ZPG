#include "VertexShader.h"

/*
//Working Version
this->vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec4 pointPosition;"
		"layout(location=1) in vec4 pointColour;"
		"uniform mat4 modelMatrix;"
		"out vec4 colour;"
		"void main ()"
		"{"
		"     gl_Position = vec4(pointPosition);"
		"	  colour = vec4(pointColour);"
		"}";
*/

VertexShader::VertexShader()
{
	this->vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec4 pointPosition;"
		"layout(location=1) in vec4 pointColour;"
		"uniform mat4 modelMatrix;"
		"out vec4 colour;"
		"void main ()"
		"{"
		"     gl_Position = modelMatrix * vec4(pointPosition);"
		"	  colour = vec4(pointColour);"
		"}";

	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(this->vertexShader);
}

VertexShader::~VertexShader()
{
	delete this->vertex_shader;
}

GLuint VertexShader::GetVertexShader()
{
	return this->vertexShader;
}
