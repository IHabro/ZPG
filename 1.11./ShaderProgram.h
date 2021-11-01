#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Includes.h"
#include "Camera.h"

class Camera;

class ShaderProgram
{
private:
	VertexShader* vertex;
	FragmentShader* fragment;
	Camera* camera;
	GLuint ProgramId;

public:
	//ShaderProgram(Camera* cam);
	ShaderProgram();
	~ShaderProgram();
	GLuint GetShaderProgramId();
	GLint GetModelMatrix(const GLchar* name);
	void Activate();
	void Deactivate();
	void CheckStatus();
	void SetLightPosition(glm::vec3 position);
	void SetCameraPosition(glm::vec3 position);
};

