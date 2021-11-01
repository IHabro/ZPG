#pragma once

#include "Includes.h"
#include "GeneralModel.h"
#include "ShaderProgram.h"
#include "Factory.h"
#include "Scene.h"

using namespace std;

class Application
{
private:
	static Application* instance;

	Scene* scene;

	ShaderProgram* shaderProgram;
	GLFWwindow* window;
	glm::mat4 modeMat;
	glm::mat4 projMat;
	glm::mat4 viewMat;

	bool rightClick = false;

	Application();

public:
	Factory* factory;

	static Application* GetInstance();
	~Application();
	void AddObject(GeneralModel* obj);
	void AddModeMatrix(glm::mat4 mat);
	void AddProjMatrix(glm::mat4 mat);
	void AddViewMatrix(glm::mat4 mat);

	void SetUp();
	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
	void SetMatricies();
	void Run();


	//Predefined functions from main.cpp
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};

