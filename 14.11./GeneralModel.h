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

	//2D Stuff
	//Triangle Stuff
	//GeneralModel(PointData points[], int size);

	//Sphere stuff
	GeneralModel(const float points[], int size);

	~GeneralModel();
	int GetPointsToRead();
	void BindVAO();
	void UnBindVAO();
};

