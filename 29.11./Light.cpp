#include "Light.h"

#pragma region Constructor & Deconstructor
Light::Light()
{
	this->position = glm::vec3(0, 0, 0 );
}

Light::Light(glm::vec3 pos)
{
	this->position = pos;
}

Light::~Light()
{

}
#pragma endregion


#pragma region Methods
glm::vec3 Light::GetPosition()
{
	return this->position;
}

void Light::SetPosition(glm::vec3 pos)
{
	this->position = pos;

	this->Notify();
}
#pragma endregion
