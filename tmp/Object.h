#pragma once

#include "GeneralModel.h"
#include "ShaderProgram.h"

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
	glm::mat4 GetObjectModelMatrix();
	void Draw(glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 cameraPosition);
};
