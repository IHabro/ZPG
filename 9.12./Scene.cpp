#include "Scene.h"

#pragma region Constructor & Deconstructor
Scene::Scene(Light* light)
{
	camera = new Camera();
	manager = new ObjectManager();
	lights = vector<Light*>();
	lights.push_back(light);
}

Scene::~Scene()
{
	delete camera;
	delete manager;
}
#pragma endregion



#pragma region Methods
void Scene::SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	camera->SetCamera(eye, center, up);
}

void Scene::AddLight(Light* light)
{
	lights.push_back(light);
}

void Scene::AddObject(Object* obj)
{
	manager->AddObject(obj);
}

void Scene::MoveLeft()
{
	camera->ToLeft();
}

void Scene::MoveRight()
{
	camera->ToRight();
}

void Scene::MoveForward()
{
	camera->ToFront();
}

void Scene::MoveBackward()
{
	camera->ToBack();
}

void Scene::MouseMove(double new_x, double new_y, int width, int height)
{
	camera->MouseMove(new_x, new_y, width, height);
}
#pragma endregion



#pragma region Get Methods
ObjectManager* Scene::GetManager()
{
	return manager;
}

//Light section
Light* Scene::ReturnLight()
{
	return lights[0];
}

glm::vec3 Scene::GetLightPosition()
{
	return lights[0]->GetPosition();
}

vector<Light*> Scene::GetLights()
{
	return lights;
}
//end

//Camera Section
Camera* Scene::ReturnCamera()
{
	return camera;
}

glm::mat4 Scene::GetCamera()
{
	return camera->GetCamera();
}

glm::vec3 Scene::GetCameraPosition()
{
	return camera->GetCameraPosition();
}

glm::vec3 Scene::GetCameraTarget()
{
	return camera->GetTarget();
}
//end
#pragma endregion
