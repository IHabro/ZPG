#include "Camera.h"
#include "ShaderProgram.h"

#pragma region Constructor & Deconstructor
Camera::Camera()
{
	eye = glm::vec3(0.0f, 0.0f, 10.0f);
	center = glm::vec3(0.0f, 0.0f, -10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	eye = eye;
	center = center;
	up = up;
}

Camera::~Camera()
{

}
#pragma endregion


//Every time when I update something inside Camera, I should call Notify()

#pragma region Methods
void Camera::ToFront()
{
	eye += (glm::normalize(center));

	Notify();
}

void Camera::ToBack()
{
	eye -= (glm::normalize(center));

	Notify();
}

void Camera::ToLeft()
{
	eye += (glm::normalize(glm::cross(center, up)));

	Notify();
}

void Camera::ToRight()
{
	eye -= (glm::normalize(glm::cross(center, up)));

	Notify();
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
	center = direction;
	up = glm::cross(right, direction);

	Notify();
}

void Camera::SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	eye = eye;
	center = center;
	up = up;

	Notify();
}
#pragma endregion


#pragma region Get Methods
glm::mat4 Camera::GetCamera()
{
	return glm::lookAt(eye, eye + center, up);
}

glm::vec3 Camera::GetCameraPosition()
{
	return eye;
}

glm::vec3 Camera::GetTarget()
{
	return center;
}
#pragma endregion
