#include "Factory.h"
#include "IncludeModels.h"
#include "PointData.h"
#include "ModelSkyBox.h"
#include "GeneralAssimpModel.h"
#include "IncludeLights.h"

#include <memory>

#pragma region Constructor & Deconstructor & Singleton Stuff
Factory* Factory::instance = 0;

GLuint err;

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
	defaultMatrix = glm::mat4(1.0f);
	defaultLight = glm::vec3(0.0f, 5.0f, -15.0f);
}

Factory::~Factory()
{

}
#pragma endregion

#pragma region Scene Factory Methods
Scene* Factory::Create4SpheresScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	FactoryParams defaultParam = { "default.vert", "default.frag", result };

	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateBasicTextureScene()
{
	Scene* result = new Scene(new Light(defaultLight));
	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	
	result->AddObject(CreateTexturePlain(basicTexture, defaultMatrix, 6));

	return result;
}

Scene* Factory::CreateMixedScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	result->AddObject(CreateTexturePlain(basicTexture, defaultMatrix, 6));

	FactoryParams defaultParam = { "default.vert", "default.frag", result };
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::Create4SpheresSkyBoxScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	result->AddObject(CreateSkyBox(result, defaultMatrix));

	FactoryParams defaultParam = { "default.vert", "default.frag", result };
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateLightsScene()
{
	//More Lights
	Scene* result = new Scene(new Light(defaultLight));

	PointLight* pl = new PointLight(glm::vec3(5.0f, 5.0f, 0.0f));
	DirectionalLight* dl = new DirectionalLight(glm::vec3(0.0f, 0.0f, 5.0f));
	SpotLight* sl = new SpotLight(result->GetCameraPosition(), result->GetCameraPosition());

	result->AddLight((Light*)pl);
	result->AddLight((Light*)dl);
	result->AddLight((Light*)sl);

	FactoryParams defaultParam = { "lights.vert", "lights.frag", result };

	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateCombinedScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	PointLight* pl = new PointLight(glm::vec3(5.0f, 5.0f, 0.0f));
	DirectionalLight* dl = new DirectionalLight(glm::vec3(0.0f, 0.0f, 5.0f));
	SpotLight* sl = new SpotLight(result->GetCameraPosition(), result->GetCameraPosition());

	result->AddLight((Light*)pl);
	result->AddLight((Light*)dl);
	result->AddLight((Light*)sl);

	result->AddObject(CreateSkyBox(result, defaultMatrix));

	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	result->AddObject(CreateTexturePlain(basicTexture, defaultMatrix, 6));

	FactoryParams defaultParam = { "lights.vert", "lights.frag", result };
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateExperimentalScene()
{
	Scene* result = new Scene((Light*) (new PointLight(defaultLight)));

	DirectionalLight* dl = new DirectionalLight(glm::vec3(0.0f, -1.0f, 0.0f));
	SpotLight* sl = new SpotLight(result->GetCameraPosition(), result->GetCameraPosition());

	result->AddLight((Light*)dl);
	result->AddLight((Light*)sl);

	result->AddObject(CreateSkyBox(result, defaultMatrix));

	FactoryParams defaultParam = { "lights.vert", "lights.frag", result };
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(2.5f, 5.0f, -15.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(-2.5f, 5.0f, -15.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, 7.5f, -15.0f))));
	result->AddObject(CreateLightsSphere(defaultParam, glm::translate(defaultMatrix, glm::vec3(0.0f, +2.5f, -15.0f))));

	result->AddObject(CreateAssimpModel(result, glm::translate(defaultMatrix, glm::vec3(0.0f, 0.0f, -15.0f)), "assimpModels/zombie/zombie.obj", "assimpModels/zombie/zombie.png"));
	result->AddObject(CreateAssimpModel(result, glm::translate(defaultMatrix, glm::vec3(0.0f, 0.0f, +10.0f)), "assimpModels/models/house.obj", "assimpModels/models/house.png"));
	result->AddObject(CreateAssimpModel(result, defaultMatrix, "assimpModels/teren/teren.obj", "assimpModels/teren/teren.png"));
	result->AddObject(CreateAssimpModel(result, glm::translate(defaultMatrix, glm::vec3(0.0f, 0.0f, -5.0f)), "assimpModels/tree/tree.obj", "assimpModels/tree/tree.png"));

	return result;
}
#pragma endregion

#pragma region Object Factory Methods
Object* Factory::CreateSphere(FactoryParams params, glm::mat4 matrix)
{
	GeneralModel* gm = new GeneralModel(sphere, 17280);
	ShaderProgram* sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera(), params.scene->ReturnLight());

	return new Object( gm, sp, matrix);
}

Object* Factory::CreateLightsSphere(FactoryParams params, glm::mat4 matrix)
{
	GeneralModel* gm = new GeneralModel(sphere, 17280);
	ShaderProgram* sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera(), params.scene->ReturnLight());

	return new Object(gm, sp, true, matrix);
}

Object* Factory::CreateTexturePlain(FactoryParams params, glm::mat4 matrix, int size)
{
	const float points[] =
	{
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};

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
	ShaderProgram*	sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera(), params.scene->ReturnLight());

	//return new Object(gm, sp, glm::scale(glm::translate(matrix, glm::vec3(0.0f, -10.0f, 0.0f)), glm::vec3(10.0f, 10.0f, 10.0f)), "test.png");

	return new Object(gm, sp, true, matrix);
}

Object* Factory::CreateSkyBox(Scene* sc, glm::mat4 matrix)
{
	ShaderProgram* sp = new ShaderProgram("skybox.vert", "skybox.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(nullptr, sp, matrix, true);
}

Object* Factory::CreateAssimpModel(Scene* sc, glm::mat4 matrix, string filePath, string textureFile)
{
	GeneralAssimpModel* gam = new GeneralAssimpModel();
	gam->Load(filePath.c_str());
	gam->LoadTexture(textureFile.c_str());

	ShaderProgram* sp = new ShaderProgram("textureLights.vert", "textureLights.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(true, (GeneralModel*)gam, sp, matrix);
}

void Factory::SeedTree(Scene* sc, glm::vec3 position)
{
	sc->AddObject(CreateAssimpModel(sc, glm::translate(defaultMatrix, position), "assimpModels/tree/tree.obj", "assimpModels/tree/tree.png"));
}
#pragma endregion
