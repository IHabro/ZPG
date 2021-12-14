#include "SpotLight.h"
#include <glm/trigonometric.hpp>

SpotLight::SpotLight(glm::vec3 dir, glm::vec3 pos) : PointLight(position)
{
	type = 3;
	position = pos;
	direction = dir;
	cutOff = glm::cos(glm::radians(12.5f));
}

SpotLight::SpotLight(glm::vec3 dir, glm::vec3 pos, float co, float con, float lin, float qua) : PointLight(pos, con, lin, qua)
{
	type = 3;

	position = pos;
	direction = dir;
	cutOff = co;

	constant = con;
	linear = lin;
	quadratic = qua;
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
