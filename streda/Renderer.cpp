#include "Renderer.h"
#include "ModelSkyBox.h"
#include "IncludeLights.h"
#include "GeneralAssimpModel.h"

#include <string>

#pragma region Constructor & Deconstructor
Renderer::Renderer()
{
	//Protoze nemam polimorfismus, tak nejde prevadet GeneralModel na Child*
	model = new ModelSkyBox();
	sceneToRender = nullptr;
	projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

Renderer::~Renderer()
{
	delete sceneToRender;
}
#pragma endregion


#pragma region Methods
void Renderer::RenderScene(Scene* sc, glm::mat4 matrix)
{
	sceneToRender = sc;
	projMat = matrix;

	int size = sc->GetManager()->GetNumberOfElements();
	
	for (int i = 0; i < size; i++)
	{
		RenderObject(sc->GetManager()->GetThElement(i));
	}

	sceneToRender = nullptr;
	projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Renderer::RenderObject(Object* obj)
{
	glStencilFunc(GL_ALWAYS, obj->GetObjectId(), 0xFF);

	if (obj->GetSkybox())
	{
		RenderSkyBox(obj);
		return;
	}
	else if (obj->GetLights())
	{
		RenderLights(obj);
		return;
	}
	else if (obj->GetTexture())
	{
		RenderTextured(obj);
		return;
	}
	else if (obj->GetAssimp())
	{
		RenderAssimpIBO(obj);
		return;
	}
	else
	{
		RenderNormal(obj);
		return;
	}
}

void Renderer::RenderTextured(Object* obj)
{

	//Check Shader status
	obj->GetShader()->CheckStatus();

	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();

	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "Model");

	//View Matrix
	obj->GetShader()->SetMat4(sceneToRender->GetCamera(), "View");

	//Projection Matrix
	obj->GetShader()->SetMat4(projMat, "Projection");

	//Camera Position
	obj->GetShader()->SetVec3(sceneToRender->GetCameraPosition(), "viewPosition");
	obj->GetShader()->SetVec3(sceneToRender->GetLightPosition(), "lightPosition");

	//Bind Object VAO
	obj->GetObjectModel()->BindVAO();

	obj->GetShader()->AddTexture(obj->GetTextureId());

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}

void Renderer::RenderNormal(Object* obj)
{
	//Check Shader status
	obj->GetShader()->CheckStatus();

	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();

	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "Model");

	//View Matrix
	obj->GetShader()->SetMat4(sceneToRender->GetCamera(), "View");

	//Projection Matrix
	obj->GetShader()->SetMat4(projMat, "Projection");

	//Camera Position
	obj->GetShader()->SetVec3(sceneToRender->GetCameraPosition(), "viewPosition");
	obj->GetShader()->SetVec3(sceneToRender->GetLightPosition(), "lightPosition");

	//Bind Object VAO
	obj->GetObjectModel()->BindVAO();

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}

void Renderer::RenderSkyBox(Object* obj)
{
	// seamless cubemap
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// skybox will be drawn first, so disallow writing into depth buffer
	glDepthMask(GL_FALSE);

	obj->GetShader()->Activate();

	obj->GetShader()->SetMat4(glm::translate(glm::mat4(1.0f), sceneToRender->GetCameraPosition()), "Model");
	obj->GetShader()->SetMat4(sceneToRender->GetCamera(), "View");
	obj->GetShader()->SetMat4(projMat, "Projection");

	obj->GetShader()->AddSkyBox(model->GetTextureId());

	model->BindVAO();
	glDrawArrays(GL_QUADS, 0, model->GetPointsToRead());

	model->UnBindVAO();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	obj->GetShader()->Deactivate();

	glDepthMask(GL_TRUE);
}

void Renderer::RenderLights(Object* obj)
{
	vector<Light*> lights = sceneToRender->GetLights();

	//type
	//1 - Light (calculateLight)
	//2 - Directiona (calculateDirectionLight)
	//3 - Point (calculatePointLight)
	//4 - Spot (calculateSpotLight)

	int size = (int)lights.size();

	//Check Shader status
	obj->GetShader()->CheckStatus();

	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();

	obj->GetShader()->SetInt(size, "lightsCount");

	for (int i = 0; i < size; i++)
	{
		switch (lights[i]->GetType())
		{
		case 0:
		{
			obj->GetShader()->SetInt(lights[i]->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(lights[i]->GetPosition(), "lights[" + std::to_string(i) + "].position");
		}break;
		case 1:
		{
			DirectionalLight* light = (DirectionalLight*)lights[i];
			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetDirection(), "lights[" + std::to_string(i) + "].direction");
		}break;
		case 2:
		{
			PointLight* light = (PointLight*)lights[i];
			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetPosition(), "lights[" + std::to_string(i) + "].position");
			obj->GetShader()->SetFloat(light->GetConstant(), "lights[" + std::to_string(i) + "].constant");
			obj->GetShader()->SetFloat(light->GetLinear(), "lights[" + std::to_string(i) + "].linear");
			obj->GetShader()->SetFloat(light->GetQuadratic(), "lights[" + std::to_string(i) + "].quadratic");
		}break;
		case 3:
		{
			SpotLight* light = (SpotLight*)lights[i];
			light->SetPosition(sceneToRender->GetCameraPosition());
			light->SetDirection(sceneToRender->GetCameraTarget());

			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetPosition(), "lights[" + std::to_string(i) + "].position");
			obj->GetShader()->SetFloat(light->GetConstant(), "lights[" + std::to_string(i) + "].constant");
			obj->GetShader()->SetFloat(light->GetLinear(), "lights[" + std::to_string(i) + "].linear");
			obj->GetShader()->SetFloat(light->GetQuadratic(), "lights[" + std::to_string(i) + "].quadratic");

			obj->GetShader()->SetVec3(light->GetDirection(), "lights[" + std::to_string(i) + "].direction");
			obj->GetShader()->SetFloat(light->GetCutOff(), "lights[" + std::to_string(i) + "].cutoff");
		}break;
		}
	}

	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "Model");

	//View Matrix
	obj->GetShader()->SetMat4(sceneToRender->GetCamera(), "View");

	//Projection Matrix
	obj->GetShader()->SetMat4(projMat, "Projection");

	//Camera Position
	obj->GetShader()->SetVec3(sceneToRender->GetCameraPosition(), "viewPosition");

	//Bind Object VAO
	obj->GetObjectModel()->BindVAO();

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}

void Renderer::RenderAssimpIBO(Object* obj)
{
	GeneralAssimpModel* gam = (GeneralAssimpModel*) obj->GetObjectModel();
	vector<Light*> lights = sceneToRender->GetLights();
	int size = (int)lights.size();

	//Check Shader status
	obj->GetShader()->CheckStatus();
	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();
	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "Model");
	//View Matrix
	obj->GetShader()->SetMat4(sceneToRender->GetCamera(), "View");
	//Projection Matrix
	obj->GetShader()->SetMat4(projMat, "Projection");

	//Bind Object VAO
	gam->BindVAO();
	gam->BindIBO();

	obj->GetShader()->SetInt(size, "lightsCount");

	for (int i = 0; i < size; i++)
	{
		switch (lights[i]->GetType())
		{
		case 0:
		{
			obj->GetShader()->SetInt(lights[i]->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(lights[i]->GetPosition(), "lights[" + std::to_string(i) + "].position");
		}break;
		case 1:
		{
			DirectionalLight* light = (DirectionalLight*)lights[i];
			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetDirection(), "lights[" + std::to_string(i) + "].direction");
		}break;
		case 2:
		{
			PointLight* light = (PointLight*)lights[i];
			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetPosition(), "lights[" + std::to_string(i) + "].position");
			obj->GetShader()->SetFloat(light->GetConstant(), "lights[" + std::to_string(i) + "].constant");
			obj->GetShader()->SetFloat(light->GetLinear(), "lights[" + std::to_string(i) + "].linear");
			obj->GetShader()->SetFloat(light->GetQuadratic(), "lights[" + std::to_string(i) + "].quadratic");
		}break;
		case 3:
		{
			SpotLight* light = (SpotLight*)lights[i];
			light->SetPosition(sceneToRender->GetCameraPosition());
			light->SetDirection(sceneToRender->GetCameraTarget());

			obj->GetShader()->SetInt(light->GetType(), "lights[" + std::to_string(i) + "].type");
			obj->GetShader()->SetVec3(light->GetPosition(), "lights[" + std::to_string(i) + "].position");
			obj->GetShader()->SetFloat(light->GetConstant(), "lights[" + std::to_string(i) + "].constant");
			obj->GetShader()->SetFloat(light->GetLinear(), "lights[" + std::to_string(i) + "].linear");
			obj->GetShader()->SetFloat(light->GetQuadratic(), "lights[" + std::to_string(i) + "].quadratic");

			obj->GetShader()->SetVec3(light->GetDirection(), "lights[" + std::to_string(i) + "].direction");
			obj->GetShader()->SetFloat(light->GetCutOff(), "lights[" + std::to_string(i) + "].cutoff");
		}break;
		}
	}

	obj->GetShader()->Assimptexture(gam->GetTextureUnit(), gam->GetTextureId());

	//Draw Triangles
	glDrawElements(GL_TRIANGLES, gam->GetIndicies(), GL_UNSIGNED_INT, NULL);

	gam->UnBindIBO();

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}
#pragma endregion
