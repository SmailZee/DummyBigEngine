#include "Engine.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "../files/LogHandler.h"

#include <assert.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

Big::Engine::Engine()
{}

Big::Engine::~Engine()
{}

bool Big::Engine::Create()
{
	bool success = true;

	LogHandler* logHandler = LogHandler::CreateInstance(logPath);
	success &= logHandler->CreateLog(engineLog);
	if (!success)
	{ return false; }

	success &= Window::InitializeRenderSystem();
	if (!success)
	{
		return false;
	}

	Window::Settings windowSettings;
	windowSettings.width = 1024;
	windowSettings.height = 768;
	windowSettings.title = "Big Engine";
	windowSettings.backgroundColor = Color(0.0f, 1.0f, 1.0f);

	assert(window == nullptr);
	window = new Window();
	success &= window->Create(windowSettings);
	if (!success)
	{
		LogHandler::DoLog("Failed to create a window", LogFile::LogType::Error);
		return false;
	}

	shaderProgram = new ShaderProgram();
	success &= shaderProgram->Create();
	if (success)
	{
		success &= shaderProgram->LoadShader(defaultVertexShader, ShaderProgram::ShaderType::Vertex);
		success &= shaderProgram->LoadShader(defaultFragmentShader, ShaderProgram::ShaderType::Fragment);
	}
	return success;
}

void Big::Engine::Destroy()
{
	if (shaderProgram)
	{
		shaderProgram->Destroy();
		delete shaderProgram;
		shaderProgram = nullptr;
	}

	if (window)
	{
		window->Destroy();
		delete window;
		window = nullptr;
	}

	Window::DeinitializeRenderSystem();
	LogHandler::DestroyInstance();
}

void Big::Engine::Run()
{
	GLfloat vertices[] = {
		0.0f,	  0.5f,	 0.0f,	1.0f,	 0.0f,	 1.0f,
		0.5f,	 -0.5f,	 0.0f,	1.0f,	 1.0f,	 0.0f,
		-0.5f,	 -0.5f,	 0.0f, 	0.0f,	 1.0f,	 1.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);


	while (!window->Closing())
	{

		window->BeginRender();
		// Todo: Create Input Handler.

		shaderProgram->Use();
		glBindVertexArray(vao);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		window->EndRender();

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}