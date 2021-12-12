#version 330

struct Light
{
  vec3 position;

  vec4 ambient;
  vec4 diffuse;
  vec4 specular;

  vec4 phong;
};

in vec3 worldPosition;
in vec3 worldNormal;

out vec4 frag_colour;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

Light calculatePhong()
{
	Light light;

	light.ambient = vec4(0.1, 0.1, 0.1, 1.0);
	light.position = lightPosition;

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);
	light.diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

	float s = 1.2;
	vec3 viewDir = normalize(viewPosition - worldPosition);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	light.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	light.phong = light.ambient + light.diffuse + light.specular;

	return light;
}

void main()
{
	Light light = calculatePhong();

	frag_colour = light.phong;
};