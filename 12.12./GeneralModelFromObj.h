#pragma once
#include "GeneralModel.h"
#include "PointData.h"

#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

class GeneralModelFromObj : public GeneralModel
{
private:
    GLuint textureId;
	Vertex* points;

public:
	GeneralModelFromObj(const aiScene* scene);
	~GeneralModelFromObj();
};

