#pragma once

#include "GeneralModel.h"
#include "Object.h"
#include "Camera.h"
#include <iostream>
#include <vector>


class Scene
{
private:
	Camera* camera;
	vector<GeneralModel*> objects;
	vector<Object*> objectsObj;

public:
	//Creation Stuff
	Scene();
	~Scene();

	//Methods
	void AddObject(GeneralModel* obj);
	void RenderScene(ShaderProgram* sh);
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MouseMove(double new_x, double new_y, int width, int height);
	void SetModelMatrixForNthObject(glm::mat4 mat, int th);
	glm::mat4 GetCamera();
	glm::vec3 GetCameraPosition();

	//Experimental Methods
	void AddObjectObj(Object* obj);
};

