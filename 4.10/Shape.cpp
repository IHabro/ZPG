#include "Shape.h"

Shape::Shape()
{
	this->points = nullptr;
	this->size = -1;
	this->pointsToRead = -1;

	this->VBO = 0;
	this->VAO = 0;
}

Shape::Shape(PointData points[], int size, int PTR)
{
	this->points = new PointData[size];
	this->size = size;
	this->pointsToRead = PTR;

	for (int i = 0; i < size; i++)
	{
		this->points[i] = points[i];
	}

	//vertex buffer object (VBO)
	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointData) * size, this->points, GL_STATIC_DRAW);
	
	//Vertex Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, PTR, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)0);
	glVertexAttribPointer(1, PTR, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)(sizeof(Coordinates)));
}

Shape::~Shape()
{
	delete[] this->points;
}

GLuint Shape::GetVao()
{
	return this->VAO;
}

int Shape::GetPointsToRead()
{
	return this->pointsToRead;
}
