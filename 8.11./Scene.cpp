#include "Scene.h"

#pragma region Constructor & Deconstructor
Scene::Scene()
{
	this->camera = Camera::GetInstance();
	this->objects = vector<GeneralModel*>();
	this->objectsObj = vector<Object*>();
}

Scene::~Scene()
{
	delete this->camera;
}
#pragma endregion



#pragma region Experimental Methods
//Experimental Method for Objects
void Scene::AddObjectObj(Object* obj)
{
	this->objectsObj.push_back(obj);
}

void Scene::AddLight(glm::vec3 light)
{
	this->lightPosition = light;
}
#pragma endregion



#pragma region Methods
void Scene::AddObject(GeneralModel* obj)
{
	this->objects.push_back(obj);
}

void Scene::SetModelMatrixForNthObject(glm::mat4 mat, int th)
{
	this->objects[th]->SetModelMatrix(mat);
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
void Scene::RenderScene(ShaderProgram* sh)
{
	for (auto x : this->objects)
	{
		//transformation Matrix
		glm::mat4 modelMat = x->GetModelMatrix();
		GLint modelMatrix = sh->GetModelMatrix("modelMatrix");
		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &modelMat[0][0]);

		x->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, x->GetPointsToRead());
	}
}
#pragma endregion
