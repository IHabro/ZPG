#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
	glm::vec3 direction;
	float cutOff;

public:
	SpotLight(glm::vec3 dir, glm::vec3 pos);
	SpotLight(glm::vec3 dir, glm::vec3 pos, float co, float con, float lin, float qua );
	~SpotLight();

	glm::vec3 GetDirection();
	void SetDirection(glm::vec3 dir);

	float GetCutOff();
	void SetCutOff(float co);
};

