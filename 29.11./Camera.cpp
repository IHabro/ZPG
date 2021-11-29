#include "Camera.h"
#include "ShaderProgram.h"

#pragma region Constructor & Deconstructor
Camera::Camera()
{
	this->eye = glm::vec3(0.0f, 0.0f, 10.0f);
	this->center = glm::vec3(0.0f, 0.0f, -10.0f);
	this->up = glm::vec3(0.0f, 0.0f, 1.0f);
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;
}

Camera::~Camera()
{

}
#pragma endregion


//Every time when I update something inside Camera, I should call Notify()

#pragma region Methods
void Camera::ToFront()
{
	this->eye += (glm::normalize(this->center));

	this->Notify();
}

void Camera::ToBack()
{
	this->eye -= (glm::normalize(this->center));

	this->Notify();
}

void Camera::ToLeft()
{
	this->eye += (glm::normalize(glm::cross(this->center, this->up)));

	this->Notify();
}

void Camera::ToRight()
{
	this->eye -= (glm::normalize(glm::cross(this->center, this->up)));

	this->Notify();
}

void Camera::MouseMove(double new_x, double new_y, int width, int height)
{
	double anglex = 3.14f;
	double angley = 0.0f;

	double speed = 0.009f;

	anglex += speed * float(width / 2 - new_x);
	angley += speed * float(height / 2 - new_y);

	glm::vec3 direction(
		cos(angley) * sin(anglex),
		sin(angley),
		cos(angley) * cos(anglex)
	);

	glm::vec3 right = glm::vec3(
		sin(anglex - 3.14f / 2.0f),
		0,
		cos(anglex - 3.14f / 2.0f)
	);
	this->center = direction;
	this->up = glm::cross(right, direction);

	this->Notify();
}

void Camera::SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

	this->Notify();
}
#pragma endregion


#pragma region Get Methods
glm::mat4 Camera::GetCamera()
{
	return glm::lookAt(this->eye, this->eye + this->center, this->up);
}

glm::vec3 Camera::GetCameraPosition()
{
	return this->eye;
}
#pragma endregion
