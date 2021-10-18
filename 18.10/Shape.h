#pragma once

#include "Includes.h"

class Shape
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
	Shape();
	Shape(PointData points[], int size, int PTR);
	~Shape();
	GLuint GetVao();
	int GetPointsToRead();
};

