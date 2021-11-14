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
	Object* CreateSphere(const char* vertex, const char* fragment, glm::mat4 matrix);
};

