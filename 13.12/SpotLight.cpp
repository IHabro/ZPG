#include "SpotLight.h"
#include <glm/trigonometric.hpp>

SpotLight::SpotLight(glm::vec3 dir, glm::vec3 pos)
{
	type = 3;
	position = pos;
	direction = dir;
	cutOff = glm::cos(glm::radians(12.5f));
}

SpotLight::SpotLight(glm::vec3 dir, glm::vec3 pos, float co)
{
	type = 3;
	position = pos;
	direction = dir;
	cutOff = co;
}

SpotLight::~SpotLight()
{

}


glm::vec3 SpotLight::GetDirection()
{
	return direction;
}

void SpotLight::SetDirection(glm::vec3 dir)
{
	direction = dir;
}


float SpotLight::GetCutOff()
{
	return cutOff;
}

void SpotLight::SetCutOff(float co)
{
	cutOff = co;
}
