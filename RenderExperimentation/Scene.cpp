#include "Scene.h"

#pragma region Constructor & Deconstructor
Scene::Scene()
{
	this->camera = new Camera();
	this->manager = new Manager();
	this->objects = vector<Object*>();
	this->light = new Light();
}

Scene::Scene(glm::vec3 light)
{
	this->camera = new Camera();
	this->manager = new Manager();
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
void Scene::AddLight(glm::vec3 light)
{
	this->light->SetPosition(light);
}

void Scene::AddObject(Object* obj)
{
	this->objects.push_back(obj);
}

glm::vec3 Scene::GetLightPosition()
{
	return this->light->GetPosition();
}

Manager* Scene::GetManager()
{
	return this->manager;
}

//Camera
glm::mat4 Scene::GetCamera()
{
	return this->camera->GetCamera();
}

glm::vec3 Scene::GetCameraPosition()
{
	return this->camera->GetCameraPosition();
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

//Draw Scene
void Scene::RenderScene(glm::mat4 projMat)
{
	for (auto x : this->objects)
	{
		//Renderer Class
		x->Draw(this, projMat);
	}
}
#pragma endregion
