#include "Controller.h"
#include "Camera.h"
#include "Includes.h"

#pragma region Constructor & Deconstructor & Singleton Stuff
Controller* Controller::instance = 0;

Controller* Controller::GetInstance()
{
	if (!instance)
	{
		instance = new Controller();
	}

	return instance;
}

Controller::Controller()
{

}

Controller::~Controller()
{

}
#pragma endregion

#pragma region Methods
void  Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Application::GetInstance()->GetActiveScene()->MoveForward();
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Application::GetInstance()->GetActiveScene()->MoveRight();
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Application::GetInstance()->GetActiveScene()->MoveBackward();
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Application::GetInstance()->GetActiveScene()->MoveLeft();
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	Application::GetInstance()->ChangeProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f));
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	if (Application::GetInstance()->GetRightClick())
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Application::GetInstance()->GetActiveScene()->MouseMove(x, y, width, height);
	}

	//printf("cursor_callback \n");
}

void Controller::LeftClick(GLFWwindow* window)
{
	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	double cursorx, cursory;
	glfwGetCursorPos(window, &cursorx, &cursory);


	GLint x = (GLint)cursorx;
	GLint y = (GLint)cursory;

	Camera* camera = Application::GetInstance()->GetActiveScene()->ReturnCamera();

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	int newy = h-y;

	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

	//Mùžeme nastavit vybrané tìleso scena->setSelect(index-1);

	//Mùžeme vypoèíst pozici v globálním souøadném systému.  
	glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4 view = camera->GetCamera();
	glm::mat4 projection = Application::GetInstance()->GetProjection();
	glm::vec4 viewPort = glm::vec4(0, 0, w, h);

	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	Application::GetInstance()->factory->SeedTree(Application::GetInstance()->GetActiveScene(), pos);

	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		Application::GetInstance()->SetRightClick(true);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		Application::GetInstance()->SetRightClick(false);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		Controller::LeftClick(window);
	}

	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}
#pragma endregion