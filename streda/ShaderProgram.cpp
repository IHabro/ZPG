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
	ProgramId = 0;
	subjectCamera = sC;
	subjectLight = sL;

	string vertCode = GetShaderFromFile(vertFile);
	string fragCode = GetShaderFromFile(fragFile);

	const char* vertText = vertCode.c_str();
	const char* fragText = fragCode.c_str();

	GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertId, 1, &vertText, NULL);
	glCompileShader(vertId);


	GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragText, NULL);
	glCompileShader(fragId);


	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, fragId);
	glAttachShader(ProgramId, vertId);
	glLinkProgram(ProgramId);

	subjectCamera->Attach(*this);
	subjectLight->Attach(*this);
}

ShaderProgram::~ShaderProgram()
{

}

GLint ShaderProgram::GetMatrix(const GLchar* name)
{
	GLint returnedLocation = glGetUniformLocation(ProgramId, name);

	if (returnedLocation != -1)
	{
		return returnedLocation;
	}

	return returnedLocation;
}

void ShaderProgram::Activate()
{
	glUseProgram(ProgramId);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::CheckStatus()
{
	GLint status;
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(ProgramId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}


#pragma region Set Methods
void ShaderProgram::SetVec3(glm::vec3 vector, string name)
{
	GLuint resultVector = GetMatrix(name.c_str());

	glUniform3fv(resultVector, 1, &vector[0]);
}

void ShaderProgram::SetMat4(glm::mat4 matrix, string name)
{
	GLuint resultMatrix = GetMatrix(name.c_str());

	glUniformMatrix4fv(resultMatrix, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetFloat(float fl, string name)
{
	GLuint resultMatrix = GetMatrix(name.c_str());

	glUniform1f(resultMatrix, fl);
}

void ShaderProgram::SetInt(int in, string name)
{
	GLuint resultMatrix = GetMatrix(name.c_str());

	glUniform1i(resultMatrix, in);
}

void ShaderProgram::Update(Subject* theChangedSubject)
{
	Camera* cam = nullptr;
	Light* lig = nullptr;

	if (cam = dynamic_cast<Camera*>(theChangedSubject))
	{
		SetMat4(cam->GetCamera(), "viewMatrix");
		SetVec3(cam->GetCameraPosition(), "viewPosition");
	}
	else if (lig = dynamic_cast<Light*>(theChangedSubject))
	{
		SetVec3(lig->GetPosition(), "lightPosition");
	}
}

void ShaderProgram::AddTexture(GLuint textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);

	//Set texture unit to fragment shader
	GLint uniformID = glGetUniformLocation(ProgramId, "Texture");
	glUniform1i(uniformID, textureId);
}

void ShaderProgram::AddSkyBox(GLuint textureId)
{
	glUniform1i(glGetUniformLocation(ProgramId, "skybox"), 0);
	glActiveTexture(GL_TEXTURE0 + 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}
#pragma endregion

GLuint ShaderProgram::GetProgramid()
{
	return ProgramId;
}

void ShaderProgram::Assimptexture(GLuint textureUnitId, GLuint textureId)
{
	glActiveTexture(textureUnitId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	GLint idModelTransform = glGetUniformLocation(ProgramId, "Texture");

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", "Texture");
	}

	glUniform1f(idModelTransform, textureUnitId);
}
