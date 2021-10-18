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
	this->shape1 = nullptr;
	this->shape2 = nullptr;

	this->SetUp();

	this->shaderProgram = new ShaderProgram();
}

Application::~Application()
{
	delete this->shape1;
	delete this->shape2;
	delete this->shaderProgram;
}

void Application::AddShape(Shape* sh1,Shape* sh2)
{
	this->shape1 = sh1;
	this->shape2 = sh2;
}

void Application::SetUp()
{
	glfwSetErrorCallback(this->error_callback);

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	//this->InitSpecificVersion();

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

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
	glGetProgramiv(shaderProgram->getShaderProgram(), GL_LINK_STATUS, &this->status);
	if (this->status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram->getShaderProgram(), GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram->getShaderProgram(), infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

/*
//Working Code
void Application::Run()
{
	while (!glfwWindowShouldClose(this->window))
	{
	   // clear color and depth buffer
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   glUseProgram(this->shaderProgram->getShaderProgram());




	   glBindVertexArray(this->shape1->GetVao()); // draw triangles
	   glDrawArrays(GL_POLYGON, 0, this->shape1->GetPointsToRead()); //mode,first,count

	   glBindVertexArray(this->shape2->GetVao()); // draw triangles
	   glDrawArrays(GL_POLYGON, 0, this->shape2->GetPointsToRead()); //mode,first,count



	   // update other events like input handling
	   glfwPollEvents();
	   // put the stuff we’ve been drawing onto the display
	   glfwSwapBuffers(window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}*/

void Application::Run()
{
	while (!glfwWindowShouldClose(this->window))
	{
       // clear color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glUseProgram(this->shaderProgram->getShaderProgram());

	   //transformation Matrix
	   GLint modelMatrix = this->shaderProgram->getModelMatrix();
	   this->tranMat = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
	   glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &this->tranMat[0][0]);


       glBindVertexArray(this->shape1->GetVao()); // draw triangles
       glDrawArrays(GL_POLYGON, 0, this->shape1->GetPointsToRead()); //mode,first,count

	   glBindVertexArray(this->shape2->GetVao()); // draw triangles
	   glDrawArrays(GL_POLYGON, 0, this->shape2->GetPointsToRead()); //mode,first,count



       // update other events like input handling
       glfwPollEvents();
       // put the stuff we’ve been drawing onto the display
       glfwSwapBuffers(window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::AddMatrix(glm::mat4 mat)
{
	this->tranMat = mat;
}














//Predefined functions from main.cpp
void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void  Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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
	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}
