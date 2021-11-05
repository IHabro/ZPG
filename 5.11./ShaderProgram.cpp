#include "ShaderProgram.h"

string ShaderProgram::getShaderFromFile(const char* fileName)
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

ShaderProgram::ShaderProgram(const char * vertFile, const char *fragFile)
{
	this->camera = nullptr;

	string vertCode = this->getShaderFromFile(vertFile);
	string fragCode = this->getShaderFromFile(fragFile);

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
}

ShaderProgram::~ShaderProgram()
{
	delete this->camera;
}

GLuint ShaderProgram::GetShaderProgramId()
{
	return this->ProgramId;
}

GLint ShaderProgram::GetModelMatrix(const GLchar* name)
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

void ShaderProgram::SetLightPosition(glm::vec3 position)
{
	glUniform3fv(glGetUniformLocation(this->ProgramId, "lightPosition"), 1, glm::value_ptr(position));
}

void ShaderProgram::SetCameraPosition(glm::vec3 position)
{
	glUniform3fv(glGetUniformLocation(this->ProgramId, "viewPosition"), 1, glm::value_ptr(position));
}

