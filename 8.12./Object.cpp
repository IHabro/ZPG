#include "Object.h"


#pragma region Constructor & Deconstructor
Object::Object()
{
	this->objectModel = nullptr;
	this->objectModelMatrix = glm::mat4(1.0f);
	this->objectShader = nullptr;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = nullptr;
	this->textureID = -1;
	this->texture = false;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, const char* texture)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = texture;
	this->textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	this->texture = true;
}

Object::Object(GeneralModel* model, ShaderProgram* shader, glm::mat4 matrix, bool skybox)
{
	this->objectModel = model;
	this->objectShader = shader;
	this->objectModelMatrix = matrix;

	this->textureName = nullptr;
	//texture location
	vector<const char*> sbl = vector<const char*>();
	sbl.push_back("right_posx.jpg");
	sbl.push_back("left_negx.jpg");
	sbl.push_back("top_posy.jpg");
	sbl.push_back("bottom_negy.jpg");
	sbl.push_back("back_posz.jpg");
	sbl.push_back("front_negz.jpg");

	//right, left, top, bot, back, front
	this->textureID = SOIL_load_OGL_cubemap(sbl[0], sbl[1], sbl[2], sbl[3], sbl[4], sbl[5],
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	this->texture = true;
	this->skybox = true;
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

GLuint Object::GetTextureId()
{
	return this->textureID;
}
#pragma endregion
