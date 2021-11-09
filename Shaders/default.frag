#version 330

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 frag_colour;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main()
{
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec3 lightDir = normalize(lightPosition - ex_worldPosition);
	vec3 viewDir = normalize(viewPosition - ex_worldPosition);
	float s = 1.2;
	float spec = pow(max(dot(viewDir, reflect(-lightDir, ex_worldNormal)), 0.0), 32);
	vec4 specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);
	float dot_product = max(dot(lightDir, normalize(ex_worldNormal)), 0.0);
	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
	frag_colour = ambient + diffuse + specular;
};