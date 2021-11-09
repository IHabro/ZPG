#include "Renderer.h"

#pragma region Constructor & Deconstructor
Renderer::Renderer()
{
	this->sceneToRender = nullptr;
	this->sceneManager = nullptr;
	this->projMat = glm::mat4(1.0f);
}

Renderer::~Renderer()
{
	delete this->sceneToRender;
	delete this->sceneManager;
}
#pragma endregion


#pragma region Methods
void Renderer::RenderScene(Scene* sc, glm::mat4 matrix)
{
	this->sceneToRender = sc;
	this->projMat = matrix;
	this->sceneManager = sc->GetManager();

	int size = this->sceneManager->GetNumberOfElements();
	
	for (int i = 0; i < size; i++)
	{
		this->RenderObject(this->sceneManager->GetThElement(i));
	}
}

void Renderer::RenderObject(Object* obj)
{
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

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}
#pragma endregion