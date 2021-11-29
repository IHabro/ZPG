#include "Application.h"
#include "Factory.h"
#include "FactoryParams.h"

int main(void)
{
	Application* app = app->GetInstance();

	app->AddScene(Factory::GetInstance()->Create4ShpheresScene());
	app->AddScene(Factory::GetInstance()->CreateBasicTextureScene());
	app->AddScene(Factory::GetInstance()->CreateExperimentalScene());
	app->SetActiveScene(2);

	app->Run();

	return 0;
}
