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

out vec4 frag_colour;

uniform vec3 viewPosition;

uniform Light lights[MAX_LIGHTS];

uniform int lightsCount;

void calculateLight(Light light)
{
	light.ambient = vec4(0.1, 0.1, 0.1, 1.0);

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);
	light.diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

	float s = 1.2;
	vec3 viewDir = normalize(viewPosition - worldPosition);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	light.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);
}

void calculateDirectionLight(Light light)
{
	light.ambient = vec4(0.1, 0.1, 0.1, 1.0);

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);
	light.diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

	float s = 1.2;
	vec3 viewDir = normalize(light.direction);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	light.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);
}

void calculatePointLight(Light light)
{
	light.distance = length(light.position - worldPosition);

	float attenuation = 1.0 / (light.constant + light.linear * light.distance + light.quadratic * (light.distance * light.distance));

	light.ambient = vec4(0.1, 0.1, 0.1, 1.0);

	vec3 toLightVector = normalize(light.position - worldPosition);
	float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);
	light.diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

	float s = 1.2;
	vec3 viewDir = normalize(light.direction);
	float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
	light.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	light.ambient += attenuation;
	light.diffuse += attenuation;
	light.specular += attenuation;
}

void calculateSpotLight(Light light)
{
	vec3 toLightVector = normalize(light.position - worldPosition);

	float theta = dot(toLightVector, normalize(-light.direction));

	if(theta > light.cutoff)
	{
		light.ambient = vec4(0.1, 0.1, 0.1, 1.0);
		
		float dot_product = max(dot(toLightVector, normalize(worldNormal)), 0.0);
		light.diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

		float s = 1.2;
		vec3 viewDir = normalize(viewPosition - worldPosition);
		float spec = pow(max(dot(viewDir, reflect(-toLightVector, worldNormal)), 0.0), 32);
		light.specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);
	}
	else
	{
		light.ambient = vec4(0.1, 0.1, 0.1, 1.0);
		light.diffuse = vec4(0, 0, 0, 0);
		light.specular = vec4(0, 0, 0, 0);
	}
}

void calculateDistance(Light light)
{
	light.distance = length(light.position - worldPosition);
}

//type
//0 - Light (calculateLight)
//1 - Directiona (calculateDirectionLight)
//2 - Point (calculatePointLight)
//3 - Spot (calculateSpotLight)

void main()
{
	vec4 resultLightning = vec4(0, 0, 0, 0);

	for(int i = 0;i < lightsCount;i++)
	{
		switch(lights[i].type)
		{
			case 0:
			{
				 calculateLight(lights[i]);
			}break;
			case 1:
			{
				calculateDirectionLight(lights[i]);
			}break;
			case 2:
			{
				calculatePointLight(lights[i]);
			}break;
			case 3:
			{
				calculateSpotLight(lights[i]);
			}break;
		}
	}

	resultLightning += lights[0].ambient;

	for(int i = 0;i < lightsCount;i++)
	{
		resultLightning += lights[i].diffuse + lights[i].specular;
	}

	frag_colour = resultLightning;
};