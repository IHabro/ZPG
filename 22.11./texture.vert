#version 330

layout(location = 0) in vec3 pointPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

out vec2 uv;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(pointPosition, 1.0f);
	uv = vec2(texture);
}
