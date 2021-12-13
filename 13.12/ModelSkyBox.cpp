#include "ModelSkyBox.h"

float vertices[] = {
	//               vertex1          vertex2             vertex3         vertex4
	/* xpos */		+1, -1, +1,		+1, +1, +1,			+1, +1, -1,		+1, -1, -1,
	/* xneg */		-1, -1, -1,		-1, +1, -1,			-1, +1, +1,		-1, -1, +1,
	/* ypos */		-1, +1, -1,		+1, +1, -1,			+1, +1, +1,		-1, +1, +1,
	/* yneg */		-1, -1, +1,		+1, -1, +1,			+1, -1, -1,		-1, -1, -1,
	/* zpos */		+1, -1, +1,		-1, -1, +1,			-1, +1, +1,		+1, +1, +1,
	/* zneg */		-1, -1, -1,		+1, -1, -1,			+1, +1, -1,		-1, +1, -1,
};

ModelSkyBox::ModelSkyBox()
{
	pointsToRead = 24;

	//ModelSkyBox
	VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	//ModelSkyBox - end

	// cubemap
	textureId = SOIL_load_OGL_cubemap
	(
		"xpos.jpg",
		"xneg.jpg",
		"ypos.jpg",
		"yneg.jpg",
		"zpos.jpg",
		"zneg.jpg",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
}

GLuint ModelSkyBox::GetTextureId()
{
	return textureId;
}


GLuint ModelSkyBox::GetVAO()
{
	return VAO;
}