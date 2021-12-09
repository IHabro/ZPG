#version 330

layout(location = 0) in vec3 pointPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

out vec2 uv;
out vec3 worldPosition;
out vec3 worldNormal;

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Model;

void main()
{
	mat4 MVP = Projection * View * Model;
	
	worldPosition = vec3(Model * vec4(pointPosition, 1.0f) );
	worldNormal = normalize(transpose(inverse(mat3(Model))) * normal);
	gl_Position = MVP * vec4(pointPosition, 1.0f);
	uv = vec2(texture);
}
