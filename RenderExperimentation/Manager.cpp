#include "Manager.h"

#pragma region Constructor & Deconstructor
Manager::Manager()
{
	this->objects = vector<Object*>();
}

Manager::~Manager()
{

}
#pragma endregion



#pragma region Methods
void Manager::AddObject(Object* obj)
{
	this->objects.push_back(obj);
}

int Manager::GetNumberOfElements()
{
	return this->objects.size();
}

Object* Manager::GetThElement(unsigned int th)
{
	return this->objects[th];
}

void Manager::RemoveThElement(unsigned int th)
{
	this->objects.erase(this->objects.begin() + th);
}
#pragma endregion
