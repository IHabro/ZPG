#pragma once
#include "GeneralModel.h"

using namespace std;

class ModelSkyBox : public GeneralModel
{
	GLuint textureId;
public:
	ModelSkyBox();

	GLuint GetTextureId();

	//Debug Methods
	GLuint GetVAO();
};

