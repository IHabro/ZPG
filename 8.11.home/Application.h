#pragma once

#include "Includes.h"
#include "GeneralModel.h"
#include "ShaderProgram.h"
#include "Factory.h"
#include "Scene.h"
#include <vector>

using namespace std;

class Application
{
private:
	static Application* instance;
	Application();

	Scene* activeScene;
	vector<Scene*> scenes;

	ShaderProgram* shaderProgram;
	GLFWwindow* window;
	glm::mat4 modeMat;
	glm::mat4 projMat;
	glm::mat4 viewMat;

	bool rightClick = false;

public:
	//
	Factory* factory;

	//Creation Stuff
	static Application* GetInstance();
	~Application();

	//Add Methods
	void AddModeMatrix(glm::mat4 mat);
	void AddProjMatrix(glm::mat4 mat);
	void AddViewMatrix(glm::mat4 mat);

	void AddScene(Scene* sc);

	//Other Methods
	void SetUp();
	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
	void Run();
	void SetActiveScene(unsigned int num);

	//Predefined functions from main.cpp
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};

