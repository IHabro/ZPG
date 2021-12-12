#include "Object.h"


#pragma region Constructor & Deconstructor
Object::Object()
{
	objectModel = nullptr;
	objectModelMatrix = glm::mat4(1.0f);
	objectShader = nullptr;

	textureName = nullptr;
	textureID = -1;
	texture = false;
	skybox = false;
	lights = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	objectModel = model;
	objectShader = shader;
	objectModelMatrix = matrix;

	textureName = nullptr;
	textureID = -1;
	texture = false;
	skybox = false;
	lights = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, const char* text)
{
	objectModel = model;
	objectShader = shader;
	objectModelMatrix = matrix;

	textureName = text;
	textureID = SOIL_load_OGL_texture(text, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texture = true;
	skybox = false;
	lights = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, bool skybox)
{
	objectModel = model;
	objectShader = shader;
	objectModelMatrix = matrix;

	textureName = nullptr;
	texture = false;
	skybox = true;
	lights = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, bool li, glm::mat4 matrix)
{
	objectModel = model;
	objectModelMatrix = matrix;
	objectShader = shader;

	textureName = nullptr;
	textureID = -1;
	texture = false;
	skybox = false;
	lights = li;
}

Object::~Object()
{
	delete objectModel;
	delete objectShader;
}
#pragma endregion

#pragma region Methods
void Object::ChangeShader(ShaderProgram* newShader)
{
	objectShader = newShader;
}

void Object::ChangeMatrix(glm::mat4 newMatrix)
{
	objectModelMatrix = newMatrix;
}
#pragma endregion

#pragma region Get Methods
GeneralModel* Object::GetObjectModel()
{
	return objectModel;
}

ShaderProgram* Object::GetShader()
{
	return objectShader;
}

glm::mat4 Object::GetObjectModelMatrix()
{
	return objectModelMatrix;
}
const char* Object::GetTextureName()
{
	return textureName;
}

bool Object::GetTexture()
{
	return texture;
}

bool Object::GetSkybox()
{
	return skybox;
}

bool  Object::GetLights()
{
	return lights;
}

GLuint Object::GetTextureId()
{
	return textureID;
}
#pragma endregion
