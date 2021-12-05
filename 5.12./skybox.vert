#version 330

layout (location = 0) in vec3 pointPosition;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position = MVP * vec4(pointPosition, 1.0);

    TexCoords = pointPosition;
}