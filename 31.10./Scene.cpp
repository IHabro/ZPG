#include "Scene.h"


Scene::Scene()
{
	this->camera = new Camera();
	this->objects = std::vector<GeneralModel*>();
}

Scene::~Scene()
{
	delete this->camera;
}

void Scene::AddObject(GeneralModel* obj)
{
	this->objects.push_back(obj);
}

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

glm::mat4 Scene::GetCamera()
{
	return this->camera->GetCamera();
}

void Scene::SetModelMatrixForNthObject(glm::mat4 mat, int th)
{
	this->objects[th]->SetModelMatrix(mat);
}

glm::vec3 Scene::GetCameraPosition()
{
	return this->camera->GetCameraPosition();
}
