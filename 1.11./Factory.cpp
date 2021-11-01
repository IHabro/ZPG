#include "Factory.h"
#include "IncludeModels.h"

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
