#pragma once

#include "GeneralModel.h"
#include "Camera.h"
#include <iostream>
#include <vector>


class Scene
{
private:
	Camera* camera;

	std::vector<GeneralModel*> objects;

public:
	Scene();
	~Scene();
	void AddObject(GeneralModel* obj);
	void RenderScene(ShaderProgram* sh);
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MouseMove(double new_x, double new_y, int width, int height);
	void SetModelMatrixForNthObject(glm::mat4 mat, int th);

	glm::mat4 GetCamera();
	glm::vec3 GetCameraPosition();
};

