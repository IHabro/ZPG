#include "GeneralModel.h"

#pragma region Constructor & Deconstructor
GeneralModel::GeneralModel()
{
	this->pointsToRead = -1;
	this->VAO = 0;
}

//Sphere stuff
GeneralModel::GeneralModel(const float points[], int size)
{
	this->pointsToRead = size / 6;	//17280 / 6 = 2880 | this->size = 2880
	PointData* PD = new PointData[size / 6];	//new PointData[2880]

	// LOAD DATA FROM sphere.h
	for (int i = 0, j = 0; j < size; i++, j = j + 6)
	{
		PD[i].corr.x = points[j + 0];
		PD[i].corr.y = points[j + 1];
		PD[i].corr.z = points[j + 2];

		PD[i].norm.x = points[j + 3];
		PD[i].norm.y = points[j + 4];
		PD[i].norm.z = points[j + 5];
	}

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointData) * this->pointsToRead, &PD[0].corr.x, GL_STATIC_DRAW);

	//Vertex Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	////glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PointData), (GLvoid*)(sizeof(Coordinates)));
}

//Textures
GeneralModel::GeneralModel(PointDataWithTexture* tmp, int size)
{
	this->pointsToRead = size;

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointDataWithTexture) * size, &tmp[0].corr.x, GL_STATIC_DRAW);

	//vertex attribute object(VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PointDataWithTexture), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PointDataWithTexture), (GLvoid*)(sizeof(Coordinates)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PointDataWithTexture), (GLvoid*)(2 * sizeof(Coordinates)));
}

GeneralModel::GeneralModel(Coordinates* tmp, int size)
{
	this->pointsToRead = size;

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Coordinates) * size, &tmp[0].x, GL_STATIC_DRAW);

	//vertex attribute object(VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Coordinates), (GLvoid*)0);
}

GeneralModel::~GeneralModel()
{

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
