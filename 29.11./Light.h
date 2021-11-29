#pragma once

#include <glm/vec3.hpp> // glm::vec3

#include "AbstractObserver.h"

class Light : public Subject
{
private:
	glm::vec3 position;

public:
	Light();
	Light(glm::vec3 pos);
	~Light();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 pos);
};

