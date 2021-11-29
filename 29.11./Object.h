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
	const char* textureName;
	bool texture;

public:
	//Constructor & Deconstructor
	Object();
	Object(GeneralModel*, ShaderProgram*, glm::mat4);
	Object(GeneralModel*, ShaderProgram*, glm::mat4, const char*);
	~Object();

	//Methods
	void ChangeShader(ShaderProgram*);
	void ChangeMatrix(glm::mat4);

	//Get Methods
	GeneralModel* GetObjectModel();
	ShaderProgram* GetShader();
	glm::mat4 GetObjectModelMatrix();
	const char* GetTextureName();
	bool GetTexture();
};
