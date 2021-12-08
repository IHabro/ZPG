#include "Renderer.h"
#include "ModelSkyBox.h"

#pragma region Constructor & Deconstructor
Renderer::Renderer()
{
	this->sceneToRender = nullptr;
	this->projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

Renderer::~Renderer()
{
	delete this->sceneToRender;
}
#pragma endregion


#pragma region Methods
void Renderer::RenderScene(Scene* sc, glm::mat4 matrix)
{
	this->sceneToRender = sc;
	this->projMat = matrix;

	int size = sc->GetManager()->GetNumberOfElements();
	
	for (int i = 0; i < size; i++)
	{
		this->RenderObject(sc->GetManager()->GetThElement(i));
	}

	this->sceneToRender = nullptr;
	this->projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Renderer::RenderObject(Object* obj)
{
	if (obj->GetSkybox())
	{
		this->RenderSkyBox(obj);
		return;
	}

	//Check Shader status
	obj->GetShader()->CheckStatus();

	//Activate Shader - glUseProgram(shaderID);
	obj->GetShader()->Activate();

	//View Matrix
	obj->GetShader()->SetMat4(this->sceneToRender->GetCamera(), "viewMatrix");

	//Projection Matrix
	obj->GetShader()->SetMat4(this->projMat, "projectionMatrix");

	//Model Matrix
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "modelMatrix");

	//Camera Position
	obj->GetShader()->SetVec3(this->sceneToRender->GetCameraPosition(), "viewPosition");
	obj->GetShader()->SetVec3(this->sceneToRender->GetLightPosition(), "lightPosition");

	//Bind Object VAO
	obj->GetObjectModel()->BindVAO();

	if (obj->GetTexture())
	{
		obj->GetShader()->AddTexture(obj->GetTextureId());
	}

	//Draw Triangles
	glDrawArrays(GL_TRIANGLES, 0, obj->GetObjectModel()->GetPointsToRead());

	//Deactivate Shader - glUseProgram(0);
	obj->GetShader()->Deactivate();
}

string FromFile(const char* fileName)
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

GLuint Shader(const char* vert, const char* frag)
{
	GLuint ProgramId = 0;

	string vertCode = FromFile(vert);
	string fragCode = FromFile(frag);

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

	return ProgramId;
}

void Renderer::RenderSkyBox(Object* obj)
{
	/*
	//SHOULD WORK - BUT IT DOES NOT
	GeneralModel* model = obj->GetObjectModel();
	ModelSkyBox* skybox = (ModelSkyBox*) &model;

	// seamless cubemap
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// skybox will be drawn first, so disallow writing into depth buffer
	glDepthMask(GL_FALSE);

	obj->GetShader()->Activate();


	//glUniformMatrix4fv(glGetUniformLocation(m_shader, "Model"), 1, false, &glm::translate(camera.Position())[0][0]);
	// render cube around the view position
	obj->GetShader()->SetMat4(obj->GetObjectModelMatrix(), "Model");

	//	glUniformMatrix4fv(glGetUniformLocation(m_shader, "View"), 1, false, &camera.View()[0][0]);
	// use instead glm::lookAt(...)
	obj->GetShader()->SetMat4(this->sceneToRender->GetCamera(), "View");

	//glUniformMatrix4fv(glGetUniformLocation(m_shader, "Projection"), 1, false, &projection[0][0]);
	obj->GetShader()->SetMat4(this->projMat, "Projection");
	
	obj->GetShader()->AddSkyBox(skybox->GetTextureId());

	skybox->BindVAO();

	//glDrawArrays(GL_QUADS, 0, 24);
	glDrawArrays(GL_QUADS, 0, skybox->GetPointsToRead());
	
	//glBindVertexArray(0);
	skybox->UnBindVAO();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	obj->GetShader()->Deactivate();

	glDepthMask(GL_TRUE);
	*/

	float vertices[] = {
		//                    vertex1            vertex2            vertex3            vertex4
		/* xpos */		+1, -1, +1,		+1, +1, +1,		+1, +1, -1,		+1, -1, -1,
		/* xneg */		-1, -1, -1,			-1, +1, -1,			-1, +1, +1,		-1, -1, +1,
		/* ypos */		-1, +1, -1,			+1, +1, -1,		+1, +1, +1,		-1, +1, +1,
		/* yneg */		-1, -1, +1,			+1, -1, +1,		+1, -1, -1,			-1, -1, -1,
		/* zpos */		+1, -1, +1,		-1, -1, +1,			-1, +1, +1,		+1, +1, +1,
		/* zneg */		-1, -1, -1,			+1, -1, -1,			+1, +1, -1,		-1, +1, -1,
	};


	//creation part
	// vertexarray
	GLuint VAO = 0;
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

	// cubemap
	GLuint m_texture = SOIL_load_OGL_cubemap
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

	ShaderProgram shader = ShaderProgram("skybox.vert", "skybox.frag", sceneToRender->ReturnCamera(), sceneToRender->ReturnLight());

	//render part
	
	// seamless cubemap
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// skybox will be drawn first, so disallow writing into depth buffer
	glDepthMask(GL_FALSE);

	shader.Activate();

	glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), this->sceneToRender->GetCameraPosition());

	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramid(), "Model"), 1, false, &modelMat[0][0]);   // render cube around the view position
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramid(), "View"), 1, false, &this->sceneToRender->GetCamera()[0][0]);	    // use instead glm::lookAt(...)
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramid(), "Projection"), 1, false, &this->projMat[0][0]);

	/*
	glUniform1i(glGetUniformLocation(shader.GetProgramid(), "skybox"), 0);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	*/
	shader.AddSkyBox(m_texture);

	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 24);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	shader.Deactivate();

	glDepthMask(GL_TRUE);

}
#pragma endregion
