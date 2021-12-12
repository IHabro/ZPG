#include "PointLight.h"

PointLight::PointLight(glm::vec3 pos)
{
	type = 2;
	position = pos;
	constant = 1.0f;
	linear = 0.7f;
	quadratic = 1.8f;
}

PointLight::PointLight(glm::vec3 pos, float con, float lin, float qua)
{
	type = 2;
	position = pos;
	constant = con;
	linear = lin;
	quadratic = qua;
}

PointLight::~PointLight()
{

}


//Constant
float PointLight::GetConstant()
{
	return constant;
}

void PointLight::SetConstant(float con)
{
	constant = con;
}


//Linear
float PointLight::GetLinear()
{
	return linear;
}

void PointLight::SetLinear(float lin)
{
	linear = lin;
}


//Quadratic
float PointLight::GetQuadratic()
{
	return quadratic;
}

void PointLight::SetQuadratic(float qua)
{
	quadratic = qua;
}
