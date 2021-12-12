#pragma once
#include "Light.h"

class DirectionalLight :  public Light
{
private:
	glm::vec3 direction;

public:
	DirectionalLight();
	DirectionalLight(glm::vec3 dir);
	~DirectionalLight();

	glm::vec3 GetDirection();
	void SetDirection(glm::vec3 dir);
};

