#pragma once

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Includes.h"
#include "Camera.h"

#include <GL/glew.h>

#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Camera;

class ShaderProgram
{
private:
	GLuint ProgramId;
	Camera* camera;

public:
	string getShaderFromFile(const char *fileName);
	ShaderProgram(const char* vertFile, const char* fragFile);
	~ShaderProgram();

	void Activate();
	void Deactivate();
	void CheckStatus();
	GLint GetModelMatrix(const GLchar* name);
	void SetLightPosition(glm::vec3 position);
	void SetCameraPosition(glm::vec3 position);

	//Unused functions
	GLuint GetShaderProgramId();
};

