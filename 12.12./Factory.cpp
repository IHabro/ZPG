#include "Factory.h"
#include "IncludeModels.h"
#include "PointData.h"
#include "ModelSkyBox.h"
#include "IncludeLights.h"
#include "GeneralModelFromObj.h"

#include <memory>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags


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
	defaultMatrix = glm::mat4(1.0f);
	defaultLight = glm::vec3(0.0f, 0.0f, 0.0f);
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
	const float texture_plain[] = {
		//vrchol, normala, uv souradnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};

	Scene* result = new Scene(new Light(defaultLight));
	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	
	result->AddObject(CreateTexturePlain(basicTexture, defaultMatrix, texture_plain, 6));

	return result;
}

Scene* Factory::CreateMixedScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	const float texture_plain[] = {
		//vrchol, norm�la, uv sou�adnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};
	FactoryParams basicTexture = { "texture.vert", "texture.frag", result };
	result->AddObject(CreateTexturePlain(basicTexture, defaultMatrix, texture_plain, 6));

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

Scene* Factory::Create4Spheres4LightsScene()
{
	Scene* result = new Scene(new Light(defaultLight));

	PointLight* pl = new PointLight(glm::vec3(5.0f, 5.0f, 0.0f));
	DirectionalLight* dl = new DirectionalLight(glm::vec3(0.0f, 0.0f, 5.0f));
	SpotLight* sl = new SpotLight(result->GetCameraPosition(), result->GetCameraTarget());

	result->AddLight((Light*)pl);
	result->AddLight((Light*)dl);
	result->AddLight((Light*)sl);

	result->AddObject(CreateLightsSphere(result, glm::translate(defaultMatrix, glm::vec3(2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(result, glm::translate(defaultMatrix, glm::vec3(-2.5f, 0.0f, 0.0f))));
	result->AddObject(CreateLightsSphere(result, glm::translate(defaultMatrix, glm::vec3(0.0f, 2.5f, 0.0f))));
	result->AddObject(CreateLightsSphere(result, glm::translate(defaultMatrix, glm::vec3(0.0f, -2.5f, 0.0f))));

	return result;
}

Scene* Factory::CreateExperimentalScene()
{
	Scene* result = new Scene(new Light(defaultLight));



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

Object* Factory::CreateLightsSphere(Scene* sc, glm::mat4 matrix)
{
	GeneralModel* gm = new GeneralModel(sphere, 17280);
	ShaderProgram* sp = new ShaderProgram("lights.vert", "lights.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(gm, sp, true, matrix);
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
	ShaderProgram*	sp = new ShaderProgram(params.shader.vertex, params.shader.fragment, params.scene->ReturnCamera(), params.scene->ReturnLight());

	return new Object(gm, sp, matrix, "test.png");
}

Object* Factory::CreateSkyBox(Scene* sc, glm::mat4 matrix)
{
	//Bordel protoze nemam polimorfismus
	/*
	GeneralModel* parent = (ModelSkyBox*) new ModelSkyBox();
	return new Object(parent, sp, matrix, true);
	*/

	ShaderProgram* sp = new ShaderProgram("skybox.vert", "skybox.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(nullptr, sp, matrix, true);
}
#pragma endregion


#pragma region Import Models
Object* ImportPlane(Scene* sc, glm::mat4 matrix)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // sloučení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

		//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile("models\plane.obj", importOptions);

	GeneralModelFromObj* gmfo = new GeneralModelFromObj(scene);
	ShaderProgram* sp = new ShaderProgram("assimp.vert", "assimp.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(gmfo, sp, matrix);
}

Object* ImportHouse(Scene* sc, glm::mat4 matrix)
{
	int count = 0;

	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // sloučení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

	const aiScene* scene = importer.ReadFile("models\house.obj", importOptions);

	


	GeneralModel* gm = new GeneralModel();
	ShaderProgram* sp = new ShaderProgram("assimp.vert", "assimp.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(gm, sp, matrix);
}

Object* ImportZombie(Scene* sc, glm::mat4 matrix)
{



	GeneralModel* gm = new GeneralModel();
	ShaderProgram* sp = new ShaderProgram("assimp.vert", "assimp.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(gm, sp, matrix);
}

Object* ImportTree(Scene* sc, glm::mat4 matrix)
{



	GeneralModel* gm = new GeneralModel();
	ShaderProgram* sp = new ShaderProgram("assimp.vert", "assimp.frag", sc->ReturnCamera(), sc->ReturnLight());

	return new Object(gm, sp, matrix);
}
#pragma endregion
