#pragma once

#include "Includes.h"
#include "GeneralModel.h"
#include "ShaderProgram.h"
#include "Factory.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Controller.h"

#include <vector>

using namespace std;

class Controller;

class Application
{
private:
	static Application* instance;
	Application();

	GLFWwindow* window;
	Controller* controller;
	glm::mat4 projMat;
	bool rightClick = false;

	Scene* activeScene;
	SceneManager* manager;
	
public:
	//Public Variables
	Factory* factory;
	Renderer* renderer;

	//Creation Stuff
	static Application* GetInstance();
	~Application();

	//Add Methods
	void AddScene(Scene* sc);

	//Get Methods
	Scene* GetActiveScene();
	bool GetRightClick();
	glm::mat4 GetProjection();

	//Other Methods
	void SetUp();
	void VersionInfo();
	void InitSpecificVersion();
	void Run();
	void SetActiveScene(int num);
	void ChangeProjectionMatrix(glm::mat4 newProjMat);
	void SetRightClick(bool newValue);
};

