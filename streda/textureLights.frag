#version 330

#define MAX_LIGHTS 4

struct Light
{
  //type
  int type;

  //Light & Point & Spot
  vec3 position;

  //Direction & Spot
  vec3 direction;

  //Lights
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;

  //Point Light
  float distance;

  float constant;
  float linear;
  float quadratic;

  //Spot Light
  float cutoff;
};

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 uv;

out vec4 frag_colour;

uniform vec3 viewPosition;

uniform Light lights[MAX_LIGHTS];
uniform Light l;

uniform int lightsCount;
uniform sampler2D Texture;

Light calculateLight(Light light)
{
	Light result;

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);

	float s = 1.2;
	vec3 viewDir = normalize(viewPosition - worldPosition);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);

	result.ambient = vec4(0.1, 0.1, 0.1, 1.0);
	result.diffuse = dot_product * texture(Texture, uv);
	result.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	return result;
}

Light calculateDirectionLight(Light light)
{
	Light result;

	vec3 toLightVector = normalize(-light.direction);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);

	float s = 0.2;
	vec3 viewDir = normalize(viewPosition - worldPosition);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	
	result.ambient = vec4(0.1, 0.1, 0.1, 1.0);
	result.diffuse = dot_product * texture(Texture, uv);;
	result.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	return result;
}

Light calculatePointLight(Light light)
{
	Light result;

	result.distance = length(light.position - worldPosition);
	float attenuation = 1.0 / (light.constant + light.linear * result.distance + light.quadratic * (result.distance * result.distance));

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);	

	float s = 1.2;
	vec3 viewDir = normalize(viewPosition - worldPosition);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	
	result.ambient = vec4(0.1, 0.1, 0.1, 1.0);
	result.diffuse = dot_product * texture(Texture, uv);;
	result.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	result.ambient *= attenuation;
	result.diffuse *= attenuation;
	result.specular *= attenuation;

	return result;
}

Light calculateSpotLight(Light light)
{
	Light result;

	vec3 toLightVector = normalize(light.position - worldPosition);

	float theta = dot(toLightVector, normalize(-light.direction));

	if(theta > light.cutoff)
	{
		float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);

		float s = 1.2;
		vec3 viewDir = normalize(viewPosition - worldPosition);
		float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);

		result.distance = length(light.position - worldPosition);
		float attenuation = 1.0 / (light.constant + light.linear * result.distance + light.quadratic * (result.distance * result.distance));

		result.ambient = vec4(0.1, 0.1, 0.1, 1.0) * attenuation;
		result.diffuse = dot_product * texture(Texture, uv) * attenuation;
		result.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0) * attenuation;
	}
	else
	{
		result.ambient = vec4(0.1, 0.1, 0.1, 1.0);
		result.diffuse = texture(Texture, uv) * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		result.specular = vec4(0.0, 0.0, 0.0, 1.0);
	}

	return result;
}

Light result[4];

void main()
{
								//Set to global ambient
	vec4 resultLightning = vec4(0.1, 0.1, 0.1, 1.0);

	for(int i = 0;i < lightsCount;i++)
	{
		if(lights[i].type == 0)
		{
			result[i] = calculateLight(lights[i]);
		}
		else if(lights[i].type == 1)
		{
			result[i] = calculateDirectionLight(lights[i]);
		}
		else if(lights[i].type == 2)
		{
			result[i] = calculatePointLight(lights[i]);	
		}
		else if(lights[i].type == 3)
		{
			result[i] = calculateSpotLight(lights[i]);
		}
	}

	for(int i = 0;i < lightsCount;i++)
	{
		resultLightning += result[i].diffuse + result[i].specular;
	}

	frag_colour = resultLightning;
};