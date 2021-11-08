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

glm::mat4 Object::GetObjectModelMatrix()
{
	return this->objectModelMatrix;
}

void Object::Draw(glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 cameraPosition)
{
	//Activate Shader - glUseProgram(shaderID);
	this->objectShader->Activate();

	//View Matrix
	GLint viewMatrix = this->objectShader->GetModelMatrix("viewMatrix");
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &viewMat[0][0]);

	//Projection Matrix
	GLint projectionMatrix = this->objectShader->GetModelMatrix("projectionMatrix");
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &projMat[0][0]);

	//Model Matrix
	//Find Matrix
	GLint modelMatrix = this->objectShader->GetModelMatrix("modelMatrix");

	this->objectShader->SetCameraPosition(cameraPosition);

	//Set Matrix
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &this->objectModelMatrix[0][0]);
	//Bind Object VAO
	this->objectModel->BindVAO();
	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, this->objectModel->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	this->objectShader->Deactivate();
}
#pragma endregion

