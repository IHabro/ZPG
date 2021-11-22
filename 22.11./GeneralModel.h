#pragma once

#include "Includes.h"

class GeneralModel
{
private:
	int pointsToRead;
	GLuint VAO;

public:
	GeneralModel();
	GeneralModel(const float points[], int size);
	GeneralModel(PointDataWithTexture* tmp, int size);
	~GeneralModel();

	//void CreateGeneralModel();
	//void CreateGeneralModelWithTextures();
	int GetPointsToRead();
	void BindVAO();
	void UnBindVAO();
};

