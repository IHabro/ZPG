#include "Object.h"


#pragma region Constructor & Deconstructor
Object::Object()
{
	this->objectModel = nullptr;
	this->objectModelMatrix = glm::mat4(1.0f);
	this->objectShader = nullptr;

	this->textureName = nullptr;
	this->texture = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = nullptr;
	this->texture = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, const char* texture)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = texture;
	this->texture = true;
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
#pragma endregion

#pragma region Get Methods
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
const char* Object::GetTextureName()
{
	return this->textureName;
}

bool Object::GetTexture()
{
	return this->texture;
}
#pragma endregion
