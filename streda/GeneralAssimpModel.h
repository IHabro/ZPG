#pragma once
#include "GeneralModel.h"
#include <string>

using namespace std;

class GeneralAssimpModel : public GeneralModel
{
private:
	int indices;
	GLuint textureUnitId;
	GLuint textureId;
	GLuint IBO;

public:
	GeneralAssimpModel();
	~GeneralAssimpModel();

	void Load(string fileName);
	void LoadTexture(string fileName);

	GLuint GetIBO();
	int GetIndicies();
	GLuint GetTextureId();
	GLuint GetTextureUnit();

	void BindIBO();
	void UnBindIBO();
};

