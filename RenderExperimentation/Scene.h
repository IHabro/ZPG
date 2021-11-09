#pragma once

#include "GeneralModel.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Manager.h"

#include <iostream>
#include <vector>

//Manager Class

class Object;
class Manager;

class Scene
{
private:
	Manager* manager;
	Camera* camera;
	Light* light;
	vector<Object*> objects;

public:
	//Creation Stuff
	Scene(glm::vec3 light);
	Scene();
	~Scene();

	//Methods
	void RenderScene(glm::mat4 projMat);
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MouseMove(double new_x, double new_y, int width, int height);

	//Get Functions
	glm::mat4 GetCamera();
	glm::vec3 GetCameraPosition();
	glm::vec3 GetLightPosition();
	Manager* GetManager();

	//Add Methods
	void AddObject(Object* obj);
	void AddLight(glm::vec3 light);
};

