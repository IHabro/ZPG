#pragma once

#include "Object.h"
#include "Manager.h"
#include "Scene.h"

class Renderer
{
private:
	Scene* sceneToRender;
	Manager* sceneManager;
	glm::mat4 projMat;

public:
	Renderer();
	~Renderer();

	void RenderScene(Scene* sc, glm::mat4 matrix);
	void RenderObject(Object* obj);
};

