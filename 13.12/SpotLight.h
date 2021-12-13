#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	glm::vec3 direction;
	float cutOff;

public:
	SpotLight(glm::vec3 dir, glm::vec3 pos);
	SpotLight(glm::vec3 dir, glm::vec3 pos, float co);
	~SpotLight();

	glm::vec3 GetDirection();
	void SetDirection(glm::vec3 dir);

	float GetCutOff();
	void SetCutOff(float co);
};

