#include "VertexShader.h"

VertexShader::VertexShader()
{
	this->vertex_shader =
		"#version 330\n"
		"layout(location = 0) in vec3 pointPosition;"
		"layout(location = 1) in vec3 normal;"
		"out vec3 ex_worldPosition;"
		"out vec3 ex_worldNormal;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"void main()"
		"{"
			"ex_worldPosition = vec3(modelMatrix * vec4(pointPosition, 1.0f) );"
			"ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * normal);"
			"gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(pointPosition, 1.0f);"
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