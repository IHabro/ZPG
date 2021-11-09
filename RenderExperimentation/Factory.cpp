#include "Factory.h"
#include "IncludeModels.h"

#pragma region Constructor & Deconstructor & Singleton Stuff
Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

Factory::Factory()
{

}

Factory::~Factory()
{

}
#pragma endregion

#pragma region Factory Methods
/*
GeneralModel* Factory::CreateGeneralModel(PointData points[], int size)
{
	return new GeneralModel(points, size);
}
*/

GeneralModel* Factory::CreateSphere()
{
	return new GeneralModel(sphere, 17280);
}

Object* Factory::CreateSphereObj(const char* vertex, const char* fragment, glm::mat4 matrix)
{
	return new Object(new GeneralModel(sphere, 17280), new ShaderProgram(vertex, fragment), matrix);
}
#pragma endregion
