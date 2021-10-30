#include "VertexShader.h"

/*
this->vertex_shader =
"#version 330\n"
"layout(location=0) in vec4 pointPosition;"
"layout(location=1) in vec4 pointColour;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec4 colour;"
"void main ()"
"{"
"     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(pointPosition);"
"	  colour = vec4(pointColour);"
"}";
*/

//working version gl_Position = modelMatrix * vec4(pointPosition);

VertexShader::VertexShader()
{
	this->vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec4 pointPosition;"
		"layout(location=1) in vec4 pointColour;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 colour;"
		"void main ()"
		"{"
		"	  gl_Position = modelMatrix * vec4(pointPosition);"
		"	  colour = vec4(pointColour);"
		"}";

	this->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShaderId, 1, &this->vertex_shader, NULL);
	glCompileShader(this->vertexShaderId);
}

VertexShader::~VertexShader()
{
	delete this->vertex_shader;
}

GLuint VertexShader::GetVertexShader()
{
	return this->vertexShaderId;
}
