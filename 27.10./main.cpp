
#include "Application.h"
#include "GeneralModel.h"

//Class Scene 
//Class Object	- Model class
//				- Transformation class
//				- Shader

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
	//Transformation Matrix
	float angle = 0;
	glm::mat4 tranMat = glm::mat4(1.0f);

	tranMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	tranMat = glm::rotate(tranMat, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	//tranMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, myView));
	tranMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	tranMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

#pragma region Converted OOP code
	Application* app = app->GetInstance();
	app->AddMatrix(tranMat);

	//Create points for shapes
	PointData pointData1[] = {
		0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.1f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	PointData pointData2[] = {
		-0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

#pragma region Insert GeneralModel objects to Application
	app->AddObject(app->factory->CreateGeneralModel(pointData1, 3, 3));
	app->AddObject(app->factory->CreateGeneralModel(pointData2, 3, 3));
#pragma endregion

	app->CheckStatus();
	app->Run();
#pragma endregion
}
