#version 330

layout(location = 0) in vec3 pointPosition;
layout(location = 1) in vec3 normal;

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
	ex_worldPosition = vec3(modelMatrix * vec4(pointPosition, 1.0f) );
	ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * normal);
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(pointPosition, 1.0f);
}