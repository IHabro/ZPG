#include "Application.h"

#pragma region Constructor & Deconstructor & Singleton Stuff
Application* Application::instance = 0;

Application* Application::GetInstance()
{
	if (!instance)
	{
		instance = new Application();
	}

	return instance;
}

Application::Application()
{
	this->SetUp();

	this->factory = this->factory->GetInstance();
	this->shaderProgram = new ShaderProgram("default.vert", "default.frag");

	this->activeScene = new Scene();
	this->scenes = vector<Scene*>();
}

Application::~Application()
{
	delete this->shaderProgram;
	delete this->factory;
	delete this->activeScene;
}
#pragma endregion



#pragma region Add Methods
void Application::AddModeMatrix(glm::mat4 mat)
{
	this->modeMat = mat;
}

void Application::AddProjMatrix(glm::mat4 mat)
{
	this->projMat = mat;
}

void  Application::AddViewMatrix(glm::mat4 mat)
{
	this->viewMat = mat;
}

void Application::AddScene(Scene* sc)
{
	this->scenes.push_back(sc);
}

//Theoretically not needed function
void Application::SetActiveScene(unsigned int num)
{
	if (num > this->scenes.size())
	{
		printf("Cannot set this scene number.");
		return;
	}

	this->activeScene = this->scenes[num];
}
#pragma endregion



#pragma region Other Methods
void Application::SetUp()
{
	glfwSetErrorCallback(this->error_callback);

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		::exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	//this->InitSpecificVersion();

	this->window = glfwCreateWindow(800, 600, "ZPG - hab0065", NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		::exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	//Callback functions
	glfwSetCursorPosCallback(window, this->cursor_callback);
	glfwSetMouseButtonCallback(window, this->button_callback);
	glfwSetKeyCallback(window, this->key_callback);
	glfwSetWindowFocusCallback(window, this->window_focus_callback);
	glfwSetWindowIconifyCallback(window, this->window_iconify_callback);
	glfwSetWindowSizeCallback(window, this->window_size_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	this->VersionInfo();
}

void Application::VersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::InitSpecificVersion()
{
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);
	*/
}

void Application::CheckStatus()
{
	this->shaderProgram->CheckStatus();
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(this->window))
	{
       // clear color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	   this->activeScene->RenderScene(this->projMat);

       // update other events like input handling
       glfwPollEvents();

       // put the stuff we’ve been drawing onto the display
       glfwSwapBuffers(window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	::exit(EXIT_SUCCESS);
}
#pragma endregion



#pragma region  Predefined functions from main.cpp
void  Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Application::GetInstance()->activeScene->MoveForward();
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Application::GetInstance()->activeScene->MoveRight();
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Application::GetInstance()->activeScene->MoveBackward();
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Application::GetInstance()->activeScene->MoveLeft();
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	Application::GetInstance()->projMat = glm::perspective(glm::radians(45.0f), (float) width / height, 0.1f, 100.0f);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	if (Application::GetInstance()->rightClick)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Application::GetInstance()->activeScene->MouseMove(x, y, width, height);
	}

	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		Application::GetInstance()->rightClick = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		Application::GetInstance()->rightClick = false;
	}

	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}
#pragma endregion
