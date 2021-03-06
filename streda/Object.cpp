#include "Object.h"

int ids = 0;

#pragma region Constructor & Deconstructor
Object::Object()
{
	this->objectId = ids++;
	this->objectModel = nullptr;
	this->objectModelMatrix = glm::mat4(1.0f);
	this->objectShader = nullptr;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
	this->skybox = false;
	this->lights = false;
	this->assimp = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	this->objectId = ids++;
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
	this->skybox = false;
	this->lights = false;
	this->assimp = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, const char* texture)
{
	this->objectId = ids++;
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = texture;
	this->textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	this->texture = true;
	this->skybox = false;
	this->lights = false;
	this->assimp = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, bool skybox)
{
	this->objectId = ids++;
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = nullptr;
	this->texture = false;
	this->skybox = true;
	this->lights = false;
	this->assimp = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, bool lights, glm::mat4 matrix)
{
	this->objectId = ids++;
	this->objectModel = model;
	this->objectModelMatrix = matrix;
	this->objectShader = shader;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
	this->skybox = false;
	this->lights = lights;
	this->assimp = false;
}

Object::Object(bool assimp, GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	this->objectId = ids++;
	this->objectModel = model;
	this->objectModelMatrix = matrix;
	this->objectShader = shader;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
	this->skybox = false;
	this->lights = false;
	this->assimp = assimp;
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

bool Object::GetSkybox()
{
	return this->skybox;
}

bool  Object::GetLights()
{
	return this->lights;
}

bool Object::GetAssimp()
{
	return this->assimp;
}

int Object::GetObjectId()
{
	return this->objectId;
}

GLuint Object::GetTextureId()
{
	return this->textureID;
}
#pragma endregion
