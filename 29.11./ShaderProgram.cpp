#include "ShaderProgram.h"

#include <iostream>

string ShaderProgram::GetShaderFromFile(const char* fileName)
{
	ifstream file(fileName);

	if (!file.is_open())
	{
		cout << "Unable to open file " << fileName << endl;
		//exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

ShaderProgram::ShaderProgram(const char* vertFile, const char* fragFile, Camera* sC, Light* sL)
{
	this->ProgramId = 0;
	this->subjectCamera = sC;
	this->subjectLight = sL;

	string vertCode = this->GetShaderFromFile(vertFile);
	string fragCode = this->GetShaderFromFile(fragFile);

	const char* vertText = vertCode.c_str();
	const char* fragText = fragCode.c_str();

	GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertId, 1, &vertText, NULL);
	glCompileShader(vertId);


	GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragText, NULL);
	glCompileShader(fragId);


	this->ProgramId = glCreateProgram();
	glAttachShader(this->ProgramId, fragId);
	glAttachShader(this->ProgramId, vertId);
	glLinkProgram(this->ProgramId);

	subjectCamera->Attach(*this);
	subjectLight->Attach(*this);
}

ShaderProgram::~ShaderProgram()
{

}

GLint ShaderProgram::GetMatrix(const GLchar* name)
{
	GLint returnedLocation = glGetUniformLocation(this->ProgramId, name);

	if (returnedLocation != -1)
	{
		return returnedLocation;
	}

	return returnedLocation;
}

void ShaderProgram::Activate()
{
	glUseProgram(this->ProgramId);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::CheckStatus()
{
	GLint status;
	glGetProgramiv(this->ProgramId, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->ProgramId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}


#pragma region Set Methods
void ShaderProgram::SetVec3(glm::vec3 vector, const char* name)
{
	GLuint resultVector = this->GetMatrix(name);

	glUniform3fv(resultVector, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetMat4(glm::mat4 matrix, const char* name)
{
	GLuint resultMatrix = this->GetMatrix(name);

	glUniformMatrix4fv(resultMatrix, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::Update(Subject* theChangedSubject)
{
	Camera* cam = nullptr;
	Light* lig = nullptr;

	if (cam = dynamic_cast<Camera*>(theChangedSubject))
	{
		this->SetMat4(cam->GetCamera(), "viewMatrix");
		this->SetVec3(cam->GetCameraPosition(), "viewPosition");
	}
	else if (lig = dynamic_cast<Light*>(theChangedSubject))
	{
		this->SetVec3(lig->GetPosition(), "lightPosition");
	}
}

void ShaderProgram::AddTexture(const char* file)
{
	//2D texture
	GLuint textureID = SOIL_load_OGL_texture(file, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//Cube Map (SkyBox)
	//GLuint textureID = SOIL_load_OGL_cubemap("xpos.jpg","xneg.jpg","ypos.jpg","yneg.jpg","zpos.jpg","zneg.jpg",SOIL_LOAD_RGB,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS    );
	glBindTexture(GL_TEXTURE_2D, textureID);
	//Set texture unit to fragment shader
	GLint uniformID = glGetUniformLocation(this->ProgramId, "textureUnitID");
	glUniform1i(uniformID, 0);
}
#pragma endregion

