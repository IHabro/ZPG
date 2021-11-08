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
	vector<Object*> objectsObj;
	glm::vec3 lightPosition;

	//Currently working thing
	vector<GeneralModel*> objects;

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
	void AddLight(glm::vec3 light);
};

