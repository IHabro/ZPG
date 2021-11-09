#include "Application.h"
#include "GeneralModel.h"

//Controller Class ?

int main(void)
{
	Application* app = app->GetInstance();

	//Light creation
	glm::vec3 light = glm::vec3(0.0f, 0.0f, 0.0f);

#pragma region Object Scene Prep
	Scene* sc = new Scene(light);
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 0.0f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f))));
	sc->AddObject(app->factory->CreateSphereObj("default.vert", "default.frag", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.5f, 0.0f))));
#pragma endregion

#pragma region Application code
	app->AddScene(sc);
	app->SetActiveScene(0);

	app->CheckStatus();
	app->Run();
#pragma endregion

	return 0;
}