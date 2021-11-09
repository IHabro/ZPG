#pragma once

#include "GeneralModel.h"
#include "Object.h"

class Factory
{
private:
	static Factory* instance;
	Factory();

public:
	//Creation Stuff
	static Factory* GetInstance();
	~Factory();

	//Factory Methods
	//GeneralModel* CreateGeneralModel(PointData points[], int size);
	GeneralModel* CreateSphere();
	Object* CreateSphereObj(const char* vertex, const char* fragment, glm::mat4 matrix);
};

