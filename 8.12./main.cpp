#include "Application.h"
#include "Factory.h"
#include "FactoryParams.h"

int main(void)
{
	Application* app = app->GetInstance();

	app->AddScene(Factory::GetInstance()->Create4SpheresScene());
	app->AddScene(Factory::GetInstance()->CreateBasicTextureScene());
	app->AddScene(Factory::GetInstance()->CreateMixedScene());
	app->AddScene(Factory::GetInstance()->CreateExperimentalScene());
	app->SetActiveScene(0);

	app->Run();

	return 0;
}
