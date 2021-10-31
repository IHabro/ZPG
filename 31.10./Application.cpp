#include "Application.h"

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
	this->shaderProgram = new ShaderProgram();
	this->scene = new Scene();
}

Application::~Application()
{
	delete this->shaderProgram;
	delete this->factory;
}

void Application::AddObject(GeneralModel* obj)
{
	this->scene->AddObject(obj);
}

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

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
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

void Application::SetMatricies()
{
	//View Matrix
	this->viewMat = this->scene->GetCamera();
	GLint viewMatrix = this->shaderProgram->GetModelMatrix("viewMatrix");
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &this->viewMat[0][0]);

	//Projection Matrix - once before while
	GLint projectionMatrix = this->shaderProgram->GetModelMatrix("projectionMatrix");
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &this->projMat[0][0]);
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	glm::vec3 light = glm::vec3(2.5f, 2.5f, 0.0f);

	while (!glfwWindowShouldClose(this->window))
	{
       // clear color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
	   this->shaderProgram->Activate();
	   this->SetMatricies();

	   glUniform3fv(glGetUniformLocation(this->shaderProgram->GetShaderProgramId(), "lightPosition"), 1, glm::value_ptr(light));
	   glUniform3fv(glGetUniformLocation(this->shaderProgram->GetShaderProgramId(), "viewPosition"), 1,
		   glm::value_ptr(this->scene->GetCameraPosition()));

	   glm::mat4 moveMat1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f));
	   glm::mat4 moveMat2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f));
	   glm::mat4 moveMat3 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 0.0f));

	   this->scene->SetModelMatrixForNthObject(moveMat1, 1);
	   this->scene->SetModelMatrixForNthObject(moveMat2, 2);
	   this->scene->SetModelMatrixForNthObject(moveMat3, 3);

	   this->scene->RenderScene(this->shaderProgram);

       // update other events like input handling
       glfwPollEvents();

       // put the stuff we’ve been drawing onto the display
       glfwSwapBuffers(window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	::exit(EXIT_SUCCESS);
}

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

#pragma region  Predefined functions from main.cpp

void  Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Application::GetInstance()->scene->MoveForward();
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Application::GetInstance()->scene->MoveLeft();
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Application::GetInstance()->scene->MoveBackward();
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Application::GetInstance()->scene->MoveRight();
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
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	if (Application::GetInstance()->rightClick)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Application::GetInstance()->scene->MouseMove(x, y, width, height);
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
