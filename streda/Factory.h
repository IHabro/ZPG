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

	//Object Factory Methods
	Object* CreateSphere(FactoryParams, glm::mat4);
	Object* CreateTexturePlain(FactoryParams, glm::mat4, int);
	Object* CreateSkyBox(Scene* sc, glm::mat4 matrix);
	Object* CreateLightsSphere(FactoryParams params, glm::mat4 matrix);
	Object* CreateAssimpModel(Scene* sc, glm::mat4 matrix, string filePath, string textureFile);

public:
	//Creation Stuff
	static Factory* GetInstance();
	~Factory();

	//Object Factory Methods
	void SeedTree(Scene* sc, glm::vec3 position);

	//Scene Factory Methods
	Scene* Create4SpheresScene();
	Scene* CreateBasicTextureScene();
	Scene* CreateMixedScene();
	Scene* Create4SpheresSkyBoxScene();
	Scene* CreateLightsScene();
	Scene* CreateCombinedScene();
	Scene* CreateExperimentalScene();
};

