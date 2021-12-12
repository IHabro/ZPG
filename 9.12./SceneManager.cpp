#include "SceneManager.h"

#pragma region Constructor & Destructor
SceneManager::SceneManager()
{
	this->scenes = vector<Scene*>();
}

SceneManager::~SceneManager()
{

}
#pragma endregion


#pragma region Methods
void SceneManager::AddScene(Scene* scene)
{
	this->scenes.push_back(scene);
}

int SceneManager::GetNumberOfElements()
{
	return this->scenes.size();
}

Scene* SceneManager::GetThScene(unsigned int th)
{
	return this->scenes[th];
}

void SceneManager::RemoveThElement(unsigned int th)
{
	this->scenes.erase(this->scenes.begin() + th);
}
#pragma endregion