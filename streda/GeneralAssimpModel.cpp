#include "GeneralAssimpModel.h"
#include "PointData.h"
#include "Includes.h"

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags



GeneralAssimpModel::GeneralAssimpModel()
{
    indices = 0;
    IBO = 0;
    textureId = 0;
    textureUnitId = 0;
}

GeneralAssimpModel::~GeneralAssimpModel()
{

}

void GeneralAssimpModel::Load(std::string fileName)
{
    GLuint err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "GL ERROR: " << err << std::endl;
    }

    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) 
    { 
        //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);

        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions())
                {
                    pVertices[i].posi[0] = mesh->mVertices[i].x;
                    pVertices[i].posi[1] = mesh->mVertices[i].y;
                    pVertices[i].posi[2] = mesh->mVertices[i].z;
                }
                if (mesh->HasNormals())
                {
                    pVertices[i].norm[0] = mesh->mNormals[i].x;
                    pVertices[i].norm[1] = mesh->mNormals[i].y;
                    pVertices[i].norm[2] = mesh->mNormals[i].z;
                }
                if (mesh->HasTextureCoords(0))
                {
                    pVertices[i].text[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].text[1] = mesh->mTextureCoords[0][i].y;
                }
            }

            unsigned int* pIndices = nullptr;

            if (mesh->HasFaces())
            {
                pIndices = new unsigned int[mesh->mNumFaces * 3];

                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    pIndices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            GLuint VBO = 0;

            glGenBuffers(1, &VBO); // generate the VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, &pVertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &IBO);    // generate the IBO
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, &pIndices[0], GL_STATIC_DRAW);

            glGenVertexArrays(1, &VAO); //generate the VAO
            glBindVertexArray(VAO); //bind the VAO

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 3));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 6));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            err = glGetError();
            if (err != GL_NO_ERROR)
            {
                std::cout << "GL ERROR: " << err << std::endl; return;
            }

            indices = mesh->mNumFaces * 3;
            pointsToRead = mesh->mNumFaces * 3;

        }
    }
    else 
    {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }

    glBindVertexArray(0);
}

void GeneralAssimpModel::LoadTexture(string fileName)
{
    GLuint err;

    glGenTextures(1, &textureId);
    textureUnitId = textureId;
    glActiveTexture(textureUnitId); // activate the texture unit first before binding texture

    err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "GL ERROR: " << err << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, textureId);

    textureId = SOIL_load_OGL_texture(static_cast<const char*>(fileName.c_str()), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textureId == -1)
    {
        fprintf(stderr, "Failed to load texture %s\n", fileName.c_str());
        exit(-1);
    }
}

GLuint GeneralAssimpModel::GetIBO()
{
    return IBO;
}

int GeneralAssimpModel::GetIndicies()
{
    return indices;
}


void GeneralAssimpModel::BindIBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void GeneralAssimpModel::UnBindIBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint GeneralAssimpModel::GetTextureId()
{
    return textureId;
}

GLuint GeneralAssimpModel::GetTextureUnit()
{
    return textureUnitId;
}
