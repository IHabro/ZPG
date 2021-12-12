#pragma once

#include "Object.h"
#include <vector>

class Object;

class ObjectManager
{
private:
	vector<Object*> objects;

public:
	ObjectManager();
	~ObjectManager();

	void AddObject(Object* obj);
	int GetNumberOfElements();
	Object* GetThElement(unsigned int th);
	void RemoveThElement(unsigned int th);
};

