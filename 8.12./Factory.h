#pragma once

#include "GeneralModel.h"
#include "FactoryParams.h"
#include "Object.h"
#include "Scene.h"


class Factory
{
private:
	glm::mat4 defaultMatrix;
	glm::vec3 defaultLight;
	
	static Factory* instance;
	Factory();

public:
	//Creation Stuff
	static Factory* GetInstance();
	~Factory();

	//Scene Factory Methods
	Scene* Create4SpheresScene();
	Scene* CreateBasicTextureScene();
	Scene* CreateMixedScene();
	Scene* CreateExperimentalScene();


	//Object Factory Methods
	Object* CreateSphere(FactoryParams, glm::mat4);
	Object* CreateTexturePlain(FactoryParams, glm::mat4, const float*, int);
	Object* CreateSkyBox(FactoryParams, glm::mat4);
};

