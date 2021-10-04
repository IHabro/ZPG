#pragma once

#include "Includes.h"
#include "Shape.h"
#include "ShaderProgram.h"

using namespace std;

class Application
{
private:
	static Application* instance;
	Application();

	Shape* shape1;
	Shape* shape2;
	ShaderProgram* shaderProgram;
	GLFWwindow* window;
	GLint status;

public:
	static Application* GetInstance();
	~Application();
	void AddShape(Shape* sh1, Shape* sh2);
	void SetUp();
	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
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

