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
	this->controller = this->controller->GetInstance();
	this->renderer = new Renderer();
	this->projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	this->activeScene = new Scene();
	this->manager = new SceneManager();
}

Application::~Application()
{
	delete this->factory;
	delete this->controller;
	delete this->renderer;

	delete this->activeScene;
	delete this->manager;
}
#pragma endregion



#pragma region Add Methods
void Application::AddScene(Scene* sc)
{
	this->manager->AddScene(sc);
}

//Theoretically not needed function
void Application::SetActiveScene(int num)
{
	if (num > this->manager->GetNumberOfElements())
	{
		printf("Cannot set this scene number.");
		return;
	}

	this->activeScene = this->manager->GetThScene(num);
}
#pragma endregion


#pragma region Get Methods
bool  Application::GetRightClick()
{
	return this->rightClick;
}

Scene* Application::GetActiveScene()
{
	return this->activeScene;
}
#pragma endregion


#pragma region Other Methods
void Application::SetRightClick(bool newValue)
{
	this->rightClick = newValue;
}

void Application::ChangeProjectionMatrix(glm::mat4 newProjMat)
{
	this->projMat = newProjMat;
}

void Application::SetUp()
{
	glfwSetErrorCallback(this->controller->error_callback);

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

	//Controller Callback functions
	glfwSetCursorPosCallback(window, this->controller->cursor_callback);
	glfwSetMouseButtonCallback(window, this->controller->button_callback);
	glfwSetKeyCallback(window, this->controller->key_callback);
	glfwSetWindowFocusCallback(window, this->controller->window_focus_callback);
	glfwSetWindowIconifyCallback(window, this->controller->window_iconify_callback);
	glfwSetWindowSizeCallback(window, this->controller->window_size_callback);

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

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(this->window))
	{
       // clear color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	   //Give Scene to renderer
	   this->renderer->RenderScene(this->activeScene, this->projMat);

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
