#include "Light.h"

#pragma region Constructor & Deconstructor
Light::Light()
{
	type = 0;
	position = glm::vec3(0, 0, 0 );
}

Light::Light(glm::vec3 pos)
{
	type = 0;
	position = pos;
}

Light::~Light()
{

}
#pragma endregion


#pragma region Methods
int Light::GetType()
{
	return type;
}

glm::vec3 Light::GetPosition()
{
	return position;
}

void Light::SetPosition(glm::vec3 pos)
{
	position = pos;

	Notify();
}
#pragma endregion
