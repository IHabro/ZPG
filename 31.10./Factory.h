#pragma once

#include "GeneralModel.h"

class Factory
{
private:
	static Factory* instance;
	Factory();

public:
	static Factory* GetInstance();
	~Factory();
	//GeneralModel* CreateGeneralModel(PointData points[], int size);
	GeneralModel* CreateSphere();
};

