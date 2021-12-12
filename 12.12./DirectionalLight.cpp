#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	type = 1;
	direction = glm::vec3(-0.2f, -1.0f, -0.3f);
}

DirectionalLight::DirectionalLight(glm::vec3 dir)
{
	type = 1;
	direction = dir;
}

DirectionalLight::~DirectionalLight()
{

}


glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void DirectionalLight::SetDirection(glm::vec3 dir)
{
	direction = dir;
}
