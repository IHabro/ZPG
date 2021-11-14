#pragma once

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
	//Creation Stuff
	string GetShaderFromFile(const char *fileName);
	ShaderProgram(const char* vertFile, const char* fragFile);
	~ShaderProgram();

	//General Functions stuff
	void Activate();
	void Deactivate();
	void CheckStatus();
	GLint GetMatrix(const GLchar* name);

	//Set Methods
	void SetVec3(glm::vec3 vector, const char* name);
	void SetMat4(glm::mat4 matrix, const char* name);
};

