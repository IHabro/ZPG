#include "Scene.h"

#pragma region Constructor & Deconstructor
Scene::Scene()
{
	this->camera = Camera::GetInstance();
	this->objects = vector<Object*>();
}

Scene::~Scene()
{
	delete this->camera;
}
#pragma endregion



#pragma region Experimental Methods
void Scene::AddLight(glm::vec3 light)
{
	this->lightPosition = light;
}
#pragma endregion



#pragma region Methods
void Scene::AddObject(Object* obj)
{
	this->objects.push_back(obj);
}

void Scene::SetModelMatrixForNthObject(glm::mat4 mat, int th)
{
	this->objects[th]->ChangeMatrix(mat);
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

glm::vec3 Scene::GetLightPosition()
{
	return this->lightPosition;
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

		//x->Draw(this);
		x->Draw(this->camera->GetCamera(), projMat, this->camera->GetCameraPosition());
	}
}
#pragma endregion
