#pragma once

#include "GeneralModel.h"
#include "Camera.h"
#include <iostream>
#include <vector>


class Scene
{
private:
	Camera* camera;

	std::vector<GeneralModel*> objects;

	GeneralModel* gm1;
	GeneralModel* gm2;

public:
	Scene();
	~Scene();
	void AddObject(GeneralModel* obj);
	void RenderScene();
};

