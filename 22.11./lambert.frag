//Working version for 4 Spheres + Zrcadlovy odlesk

#version 330
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
out vec4 frag_colour;
void main()
{
	vec3 lightDir = normalize(lightPosition - ex_worldPosition);
	float dot_product = max(dot(lightDir, normalize(ex_worldNormal)), 0.0);
	
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
	frag_colour = ambient + diffuse;
}