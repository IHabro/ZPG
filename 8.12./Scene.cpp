#include "Scene.h"

#pragma region Constructor & Deconstructor
Scene::Scene(glm::vec3 light)
{
	this->camera = new Camera();
	this->manager = new ObjectManager();
	this->light = new Light(light);
}

Scene::~Scene()
{
	delete this->camera;
	delete this->manager;
	delete this->light;
}
#pragma endregion



#pragma region Methods
void Scene::SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	this->camera->SetCamera(eye, center, up);
}

void Scene::AddLight(glm::vec3 light)
{
	this->light->SetPosition(light);
}

void Scene::AddObject(Object* obj)
{
	this->manager->AddObject(obj);
}

void Scene::MoveLeft()
{
	this->camera->ToLeft();
}

void Scene::MoveRight()
{
	this->camera->ToRight();
}

void Scene::MoveForward()
{
	this->camera->ToFront();
}

void Scene::MoveBackward()
{
	this->camera->ToBack();
}

void Scene::MouseMove(double new_x, double new_y, int width, int height)
{
	this->camera->MouseMove(new_x, new_y, width, height);
}
#pragma endregion



#pragma region Get Methods
ObjectManager* Scene::GetManager()
{
	return this->manager;
}

//Light section
Light* Scene::ReturnLight()
{
	return this->light;
}

glm::vec3 Scene::GetLightPosition()
{
	return this->light->GetPosition();
}
//end

//Camera Section
Camera* Scene::ReturnCamera()
{
	return this->camera;
}

glm::mat4 Scene::GetCamera()
{
	return this->camera->GetCamera();
}

glm::vec3 Scene::GetCameraPosition()
{
	return this->camera->GetCameraPosition();
}
//end
#pragma endregion
