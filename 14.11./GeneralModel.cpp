#include "GeneralModel.h"

#pragma region Constructor & Deconstructor
GeneralModel::GeneralModel()
{
	this->points = nullptr;
	this->size = -1;
	this->pointsToRead = -1;
	this->VBO = 0;
	this->VAO = 0;
}

/*
//2D
GeneralModel::GeneralModel(PointData points[], int size)
{
	this->points = new PointData[size];
	this->size = size;
	this->pointsToRead = 3;

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)(sizeof(Coordinates)));
}
*/

//Sphere stuff
GeneralModel::GeneralModel(const float points[], int size)
{
	this->size = size / 6;	//17280 / 6 = 2880 | this->size = 2880
	this->points = new PointData[size / 6];	//new PointData[2880]

	// LOAD DATA FROM sphere.h
	for (int i = 0, j = 0; j < size; i++, j = j + 6)
	{
		this->points[i].corr.x = points[j];
		this->points[i].corr.y = points[j + 1];
		this->points[i].corr.z = points[j + 2];
		this->points[i].normal.x = points[j + 3];
		this->points[i].normal.y = points[j + 4];
		this->points[i].normal.z = points[j + 5];
	}

	this->pointsToRead = size / 6;

	//vertex buffer object (VBO)
	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointData) * this->size, &this->points[0].corr.x, GL_STATIC_DRAW);

	//Vertex Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)(sizeof(Coordinates)));
}

GeneralModel::~GeneralModel()
{
	delete[] this->points;
}
#pragma endregion

#pragma region Methods
int GeneralModel::GetPointsToRead()
{
	return this->pointsToRead;
}

void GeneralModel::BindVAO()
{
	glBindVertexArray(this->VAO);
}

void GeneralModel::UnBindVAO()
{
	glBindVertexArray(0);
}
#pragma endregion
