#include "Factory.h"
#include "IncludeModels.h"

#include "PointData.h"

#pragma region Constructor & Deconstructor & Singleton Stuff
Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

Factory::Factory()
{
	this->defaultMatrix = glm::mat4(1.0f);
	this->defaultLight = glm::vec3(0.0f, 0.0f, 0.0f);
}

Factory::~Factory()
{

}
#pragma endregion

#pragma region Scene Factory Methods
Scene* Factory::Create4ShpheresScene()
{
	Scene* result = new Scene(this->defaultLight);
	FactoryParams defaultParam = { "default.vert", "default.frag", result };

	result->AddObject(this->CreateSphere(defaultParam, glm::translate(this->defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(this->CreateSphere(defaultParam, glm::translate(this->defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(this->CreateSphere(defaultParam, glm::translate(this->defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(this->CreateSphere(defaultParam, glm::translate(this->defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateBasicTextureScene()
{
	const float texture_plain[] = {
		//vrchol, normála, uv souøadnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};

	Scene* result = new Scene(this->defaultLight);
	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	
	result->SetCamera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	result->AddObject(this->CreateTexturePlain(basicTexture, this->defaultMatrix, texture_plain, 6));

	return result;
}
#pragma endregion

#pragma region Object Factory Methods
Object* Factory::CreateSphere(FactoryParams params, glm::mat4 matrix)
{
	GeneralModel* gm = new GeneralModel(sphere, 17280);
	ShaderProgram* sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera());

	return new Object( gm, sp, matrix);
}

Object* Factory::CreateTexturePlain(FactoryParams params, glm::mat4 matrix, const float points[], int size)
{
	PointDataWithTexture* tmp = new PointDataWithTexture[size];

	for (int i = 0, j = 0; i < size; i++, j = j + 8)
	{
		tmp[i].corr.x = points[j + 0];
		tmp[i].corr.y = points[j + 1];
		tmp[i].corr.z = points[j + 2];

		tmp[i].norm.x = points[j + 3];
		tmp[i].norm.y = points[j + 4];
		tmp[i].norm.z = points[j + 5];

		tmp[i].text.u = points[j + 6];
		tmp[i].text.v = points[j + 7];
	}

	GeneralModel*	gm = new GeneralModel(tmp, size);
	ShaderProgram*	sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera());

	return new Object(gm, sp, matrix, "test.png");
}
#pragma endregion
