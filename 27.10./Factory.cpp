#include "Factory.h"

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

GeneralModel* Factory::CreateGeneralModel(PointData points[], int size, int PTR)
{
	return new GeneralModel(points, size, PTR);
}
