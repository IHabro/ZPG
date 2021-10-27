#include "Scene.h"


Scene::Scene()
{
	this->camera = nullptr;
	this->objects = std::vector<GeneralModel*>();

	this->gm1 = nullptr;
	this->gm2 = nullptr;
}

Scene::~Scene()
{
	delete this->camera;
	delete this->gm1;
	delete this->gm2;
}

void Scene::AddObject(GeneralModel* obj)
{
	this->objects.push_back(obj);
}

void Scene::RenderScene()
{
	for (auto x : this->objects)
	{
		x->BindVAO();
		glDrawArrays(GL_POLYGON, 0, x->GetPointsToRead());
	}
}
