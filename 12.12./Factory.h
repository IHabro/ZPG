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
	Object* CreateTexturePlain(FactoryParams params, glm::mat4 matrix, const float points[], int size);
	Object* CreateSkyBox(Scene* sc, glm::mat4 matrix);
	Object* CreateLightsSphere(Scene* sc, glm::mat4 matrix);
	Object* ImportPlane(Scene* sc, glm::mat4 matrix);
	Object* ImportHouse(Scene* sc, glm::mat4 matrix);
	Object* ImportZombie(Scene* sc, glm::mat4 matrix);
	Object* ImportTree(Scene* sc, glm::mat4 matrix);

public:
	//Creation Stuff
	static Factory* GetInstance();
	~Factory();

	//Scene Factory Methods
	Scene* Create4SpheresScene();
	Scene* CreateBasicTextureScene();
	Scene* CreateMixedScene();
	Scene* Create4SpheresSkyBoxScene();
	Scene* Create4Spheres4LightsScene();
	Scene* CreateExperimentalScene();



};

