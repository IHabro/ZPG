#include "Camera.h"
#include "ShaderProgram.h"



Camera::Camera(ShaderProgram* sh)
{
	this->shader = sh;
}

Camera::~Camera()
{

}

void Camera::GetCamera()
{
	/*
	return glm::lookAt(eye, eye + target, up);

	target.x=cos(fi);
	target.z=sin(fi);
	target.y=sin(psi);
	*/
}

void Camera::ToFront()
{
	//eye += (glm::normalize(target));
}

void Camera::ToLeft()
{
	//eye += (glm::normalize(glm::cross(target, up)));
}
