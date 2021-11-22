#include "Application.h"
#include "FactoryParams.h"

int main(void)
{
	Application* app = app->GetInstance();

	app->AddScene(app->factory->Create4ShpheresScene());
	app->AddScene(app->factory->CreateBasicTextureScene());
	app->SetActiveScene(1);

	app->Run();

	return 0;
}