#include "FragmentShader.h"



FragmentShader::FragmentShader()
{
	this->fragment_shader =
		"#version 330\n"
		"in vec4 colour;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4(1.0, 0.0, 0.0, 1.0);"
		"     frag_colour = vec4(colour);"
		"}";

	//frag_colour = vec4(colour);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &this->fragment_shader, NULL);
	glCompileShader(this->fragmentShader);
}

FragmentShader::~FragmentShader()
{

}

GLuint FragmentShader::GetFragmentShader()
{
	return this->fragmentShader;
}
