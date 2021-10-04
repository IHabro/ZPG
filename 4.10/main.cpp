
#include "Application.h"
#include "Shape.h"


// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);

// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);

int main(void)
{
#pragma region Converted OOP code
	Application* app = app->GetInstance();

	//Create points for shapes
	PointData pointData1[] = {
		0.1, 0.1, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		0.1, 0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
		0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0
	};

	PointData pointData2[] = {
		-0.1, -0.1, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		-0.1, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		-0.5, -0.1, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0
	};

#pragma region Create Shape objects from points
	Shape* shape1 = new Shape(pointData2, 3, 3);
	Shape* shape2 = new Shape(pointData1, 3, 3);
#pragma endregion

#pragma region Insert Shape objects to Application
	app->AddShape(shape1, shape2);
#pragma endregion

	app->CheckStatus();
	app->Run();
#pragma endregion
}
