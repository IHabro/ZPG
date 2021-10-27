#pragma once

#include "Includes.h"

class GeneralModel
{
private:
	PointData* points;
	int size;
	int pointsToRead;
	GLuint VBO;
	GLuint VAO;
	//Transformation Matrix
	//Model Shader

public:
	GeneralModel();
	GeneralModel(PointData points[], int size, int PTR);
	~GeneralModel();
	int GetPointsToRead();
	void BindVAO();
	void UnBindVAO();
};

