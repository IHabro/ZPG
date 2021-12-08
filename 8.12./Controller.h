#pragma once

#include "Includes.h"
#include "Application.h"

using namespace std;

class Controller
{
private:
	static Controller* instance;
	Controller();

public:
	static Controller* GetInstance();
	~Controller();

	//Predefined functions from main.cpp
	//Controller Class
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};

