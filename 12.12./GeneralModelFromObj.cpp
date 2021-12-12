#include "GeneralModelFromObj.h"

GeneralModelFromObj::GeneralModelFromObj(const aiScene* scene)
{
	int count = 0;

	if (scene)
	{
		aiMesh* mesh = scene->mMeshes[0];
		pointsToRead = mesh->mNumVertices;

		points = new Vertex[mesh->mNumVertices];
		std::memset(points, 0, sizeof(Vertex) * mesh->mNumVertices);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			if (mesh->HasPositions())
			{
				points[i].corr.x = mesh->mVertices[i].x;
				points[i].corr.y = mesh->mVertices[i].y;
				points[i].corr.z = mesh->mVertices[i].z;
			}
			if (mesh->HasNormals())
			{
				points[i].norm.x = mesh->mNormals[i].x;
				points[i].norm.y = mesh->mNormals[i].y;
				points[i].norm.z = mesh->mNormals[i].z;
			}
			if (mesh->HasTextureCoords(0))
			{
				points[i].text.u = mesh->mTextureCoords[0][i].x;
				points[i].text.v = mesh->mTextureCoords[0][i].y;
			}
			/*
			if (mesh->HasTangentsAndBitangents())
			{
				points[i].tang.x = mesh->mTangents[i].x;
				points[i].tang.y = mesh->mTangents[i].y;
				points[i].tang.z = mesh->mTangents[i].z;
			}
			*/

			count++;
		}
	}
	else
	{
		printf("Error, scene does not exist (error: -5)");
		exit(-5);
	}

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->pointsToRead, &points[0].corr.x, GL_STATIC_DRAW);

	//Vertex Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	////glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Coordinates)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Coordinates) + sizeof(Vector)));

	glActiveTexture(GL_TEXTURE0);
	GLuint image = SOIL_load_OGL_texture("model.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (image == NULL)
	{
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_2D, image);
}

GeneralModelFromObj::~GeneralModelFromObj()
{
	delete[] points;
}
