#pragma once

#include "Object.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "ModelSkyBox.h"

class Renderer
{
private:
	ModelSkyBox* model;
	Scene* sceneToRender;
	glm::mat4 projMat;

public:
	Renderer();
	~Renderer();

	void RenderScene(Scene* sc, glm::mat4 matrix);
	void RenderObject(Object* obj);
	void RenderSkyBox(Object* obj);
	void RenderLights(Object* obj);
	void RenderTextured(Object* obj);
	void RenderNormal(Object* obj);
	void RenderAssimpIBO(Object* obj);
};

