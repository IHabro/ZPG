#pragma once

#include "GeneralModel.h"
#include "ShaderProgram.h"
#include "Scene.h"

class Scene;

class Object
{
private:
	GeneralModel* objectModel;
	ShaderProgram* objectShader;
	glm::mat4 objectModelMatrix;

public:
	//Constructor & Deconstructor
	Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix);
	~Object();

	//Methods
	void ChangeShader(ShaderProgram* newShader);
	void ChangeMatrix(glm::mat4 newMatrix);
	void Draw(Scene* sc, glm::mat4 projMat);

	//Get Methods
	GeneralModel* GetObjectModel();
	ShaderProgram* GetShader();
	glm::mat4 GetObjectModelMatrix();
};
