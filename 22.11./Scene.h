#pragma once

#include "GeneralModel.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "ObjectManager.h"

#include <iostream>
#include <vector>

class Object;
class ObjectManager;

class Scene
{
private:
	ObjectManager* manager;
	Camera* camera;
	Light* light;

public:
	//Creation Stuff
	Scene(glm::vec3 light);
	~Scene();

	//Camera Functions
	void SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MouseMove(double new_x, double new_y, int width, int height);

	//Get Functions
	Camera* ReturnCamera();
	glm::mat4 GetCamera();
	glm::vec3 GetCameraPosition();
	glm::vec3 GetLightPosition();
	ObjectManager* GetManager();

	//Add Methods
	void AddObject(Object* obj);
	void AddLight(glm::vec3 light);
};

