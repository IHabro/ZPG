#pragma once

#include "Object.h"
#include <vector>

class Object;

class Manager
{
private:
	vector<Object*> objects;

public:
	Manager();
	~Manager();

	void AddObject(Object* obj);
	int GetNumberOfElements();
	Object* GetThElement(unsigned int th);
	void RemoveThElement(unsigned int th);
};

