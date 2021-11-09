#include "Application.h"
#include "GeneralModel.h"



int main(void)
{
#pragma region Prep
	//Transformation Matrix
	float angle = 0;
	glm::mat4 tranMat = glm::mat4(1.0f);

	tranMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	tranMat = glm::rotate(tranMat, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	tranMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	tranMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	//Camera Matricies
	//Camera View matrix
	//Imported from first code block
	glm::mat4 viewMat = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//Projection Matrix
	//45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	//Light creation
	glm::vec3 light = glm::vec3(0.0f, 0.0f, 0.0f);
#pragma endregion

	Application* app = app->GetInstance();

#pragma region Object Scene Prep
	Scene* sc = new Scene(light);
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 0.0f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.5f, 0.0f))));
#pragma endregion

#pragma region Application code
	app->AddModeMatrix(tranMat);
	app->AddProjMatrix(projMat);

	app->AddScene(sc);
	app->SetActiveScene(0);

	app->CheckStatus();
	app->Run();
#pragma endregion

	return 0;
}

/*
Observer between Shader and Camera | Shadery se registrujou na Cameru
? Class Renderer(scene) ?

	//Legacy Code:
	//Create points for shapes
	PointData triangle1[] = {
		// x     y     z |   R     G     B
		0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	PointData triangle2[] = {
		// x     y     z |   R     G     B
		-0.1f, -0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	PointData squareTriangle1[] = {
		// x     y     z |   R     G     B
		-0.5f, 0.1f, 0.0f, 0.0f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f,
		-0.1f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f
	};

	PointData squareTriangle2[] = {
		// x     y     z |   R     G     B
		-0.5f, 0.1f, 0.0f, 0.0f, 0.5f, 0.5f,
		-0.1f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f,
		-0.1f, 0.1f, 0.0f, 0.0f, 0.5f, 0.5f
	};

	//2D Triangles and Square
	//Should not work
	//app->AddObject(app->factory->CreateGeneralModel(triangle1, 3));
	//app->AddObject(app->factory->CreateGeneralModel(triangle2, 3));
	//app->AddObject(app->factory->CreateGeneralModel(squareTriangle1, 3));
	//app->AddObject(app->factory->CreateGeneralModel(squareTriangle2, 3));

	//3D Sphere
	//Working version with direct scene adding
	app->AddObject(app->factory->CreateSphere());
	app->AddObject(app->factory->CreateSphere());
	app->AddObject(app->factory->CreateSphere());
	app->AddObject(app->factory->CreateSphere());
*/
