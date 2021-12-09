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
	vector<Light*> lights;

public:
	//Creation Stuff
	Scene(Light* light);
	~Scene();

	//Camera Functions
	void SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MouseMove(double new_x, double new_y, int width, int height);

	//Get Functions
	//Camera
	Camera* ReturnCamera();
	glm::mat4 GetCamera();
	glm::vec3 GetCameraPosition();

	//Light
	glm::vec3 GetLightPosition();
	Light* ReturnLight();
	vector<Light*> GetLights();

	//Manager
	ObjectManager* GetManager();

	//Add Methods
	void AddObject(Object* obj);
	void AddLight(Light* light);
};

