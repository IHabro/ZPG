#include "Application.h"
#include "Factory.h"
#include "FactoryParams.h"

int main(void)
{
	Application* app = app->GetInstance();

	app->AddScene(Factory::GetInstance()->Create4SpheresScene());			//0 - 4 Spheres
	app->AddScene(Factory::GetInstance()->CreateBasicTextureScene());		//1 - Wooden plain
	app->AddScene(Factory::GetInstance()->CreateMixedScene());				//2 - 4 Spheres + Wooden plain
	app->AddScene(Factory::GetInstance()->Create4SpheresSkyBoxScene());		//3 - 4 Spheres + Skybox
	app->AddScene(Factory::GetInstance()->CreateLightsScene());				//4 - 4 Spheres + 4 lights
	
	app->SetActiveScene(4);

	app->Run();

	return 0;
}
