#include "Object.h"


#pragma region Constructor & Deconstructor
Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;
}

Object::~Object()
{
	delete this->objectModel;
	delete this->objectShader;
}
#pragma endregion

#pragma region Methods
void Object::ChangeShader(ShaderProgram* newShader)
{
	this->objectShader = newShader;
}

void Object::ChangeMatrix(glm::mat4 newMatrix)
{
	this->objectModelMatrix = newMatrix;
}

void Object::Draw(Scene* sc, glm::mat4 projMat)
{
	//Activate Shader - glUseProgram(shaderID);
	this->objectShader->Activate();

	//View Matrix
	this->objectShader->SetMat4(sc->GetCamera(), "viewMatrix");

	//Projection Matrix
	this->objectShader->SetMat4(projMat, "projectionMatrix");

	//Model Matrix
	this->objectShader->SetMat4(this->objectModelMatrix, "modelMatrix");

	//Camera Position
	this->objectShader->SetVec3(sc->GetCameraPosition(), "viewPosition");
	this->objectShader->SetVec3(sc->GetLightPosition(), "lightPosition");

	//Bind Object VAO
	this->objectModel->BindVAO();
	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, this->objectModel->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	this->objectShader->Deactivate();
}

GeneralModel* Object::GetObjectModel()
{
	return this->objectModel;
}

ShaderProgram* Object::GetShader()
{
	return this->objectShader;
}

glm::mat4 Object::GetObjectModelMatrix()
{
	return this->objectModelMatrix;
}
#pragma endregion

