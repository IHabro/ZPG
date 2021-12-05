#include "Renderer.h"

#pragma region Constructor & Deconstructor
Renderer::Renderer()
{
	this->sceneToRender = nullptr;
	this->projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

Renderer::~Renderer()
{
	delete this->sceneToRender;
}
#pragma endregion


#pragma region Methods
void Renderer::RenderScene(Scene* sc, glm::mat4 matrix)
{
	this->sceneToRender = sc;
	this->projMat = matrix;

	int size = sc->GetManager()->GetNumberOfElements();
	
	for (int i = 0; i < size; i++)
	{
		this->RenderObject(sc->GetManager()->GetThElement(i));
	}

	this->sceneToRender = nullptr;
	this->projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Renderer::RenderObject(Object* obj)
{
	if (obj->GetSkybox())
	{
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
	}

	//Check Shader status
	obj->GetShader()->CheckStatus();

	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();

	//View Matrix
	obj->GetShader()->SetMat4(this->sceneToRender->GetCamera(), "viewMatrix");

	//Projection Matrix
	obj->GetShader()->SetMat4(this->projMat, "projectionMatrix");

	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "modelMatrix");

	//Camera Position
	obj->GetShader()->SetVec3(this->sceneToRender->GetCameraPosition(), "viewPosition");
	obj->GetShader()->SetVec3(this->sceneToRender->GetLightPosition(), "lightPosition");

	//Bind Object VAO
	obj->GetObjectModel()->BindVAO();

	if (obj->GetTexture())
	{
		if (obj->GetSkybox())
		{
			obj->GetShader()->AddSkyBox(obj->GetTextureId());
		}
		else
		{
			obj->GetShader()->AddTexture(obj->GetTextureId());
		}
	}

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}
#pragma endregion
