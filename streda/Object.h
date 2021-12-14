#pragma once

#include "GeneralModel.h"
#include "ShaderProgram.h"
#include "Scene.h"

class Scene;

class Object
{
private:
	int objectId;
	GeneralModel* objectModel;
	ShaderProgram* objectShader;
	const char* textureName;

	GLuint textureID;
	glm::mat4 objectModelMatrix;
	
	bool texture;
	bool skybox;
	bool lights;
	bool assimp;

public:
	//Constructor & Deconstructor
	Object();
	Object(GeneralModel*, ShaderProgram*, glm::mat4);
	Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, const char* texture);
	Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, bool skybox);
	Object(GeneralModel* model, ShaderProgram* shader, bool lights, glm::mat4 matrix);
	Object(bool assimp, GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix);
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
	bool GetSkybox();
	bool GetLights();
	bool GetAssimp();
	GLuint GetTextureId();

	int GetObjectId();
};
