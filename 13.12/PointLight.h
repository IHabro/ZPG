#pragma once
#include "Light.h"


class PointLight : public Light
{
private:
	float constant;
	float linear;
	float quadratic;

public:
	PointLight(glm::vec3 pos);
	PointLight(glm::vec3 pos, float con, float lin, float qua);
	~PointLight();

	//Constant
	float GetConstant();
	void SetConstant(float con);

	//Linear
	float GetLinear();
	void SetLinear(float lin);

	//Quadratic
	float GetQuadratic();
	void SetQuadratic(float qua);
};

