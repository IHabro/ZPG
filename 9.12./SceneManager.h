#pragma once

#include "Scene.h"
#include <vector>

class SceneManager
{
private:
	vector<Scene*> scenes;

public:
	SceneManager();
	~SceneManager();

	void AddScene(Scene* scene);
	int GetNumberOfElements();
	Scene* GetThScene(unsigned int th);
	void RemoveThElement(unsigned int th);
};

