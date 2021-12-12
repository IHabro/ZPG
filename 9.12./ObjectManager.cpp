#include "ObjectManager.h"

#pragma region Constructor & Deconstructor
ObjectManager::ObjectManager()
{
	this->objects = vector<Object*>();
}

ObjectManager::~ObjectManager()
{

}
#pragma endregion



#pragma region Methods
void ObjectManager::AddObject(Object* obj)
{
	this->objects.push_back(obj);
}

int ObjectManager::GetNumberOfElements()
{
	return this->objects.size();
}

Object* ObjectManager::GetThElement(unsigned int th)
{
	return this->objects[th];
}

void ObjectManager::RemoveThElement(unsigned int th)
{
	this->objects.erase(this->objects.begin() + th);
}
#pragma endregion
