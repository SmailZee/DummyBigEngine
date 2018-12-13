#include "Window.h"
#include "../files/LogHandler.h"
#include "../files/LogFile.h"

#include <GL/glew.h>	// Must include before glfw3.h
#include <GLFW/glfw3.h>

Big::Window::Window()
{}


Big::Window::~Window()
{}

Big::Window::Settings::Settings()
{

}
Big::Window::Settings::Settings(const Settings& copySettings)
{
	width = copySettings.width;
	height = copySettings.height;
	title = copySettings.title;
	backgroundColor = copySettings.backgroundColor;
}



bool Big::Window::InitializeRenderSystem()
{
	if (glfwInit())
	{/*
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

		return true;
	}

	LogHandler::DoLog("Failed to initialize OpenGL.", LogFile::LogType::Error);
	return false;
}

void Big::Window::DeinitializeRenderSystem()
{
	glfwTerminate();
}

bool Big::Window::Create(Settings windowSettings)
{
	settings = windowSettings;
	glWindow = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
	if (!glWindow)
	{

		LogHandler::DoLog("Failed to create window", LogFile::LogType::Error);
		// Todo: Log error.
		return false;
	}

	/*
	GLEW obtains information on the supported extensions from the graphics driver.
	Experimental or pre-release drivers, however, might not report every available extension through the standard mechanism, in which case GLEW will report it unsupported.
	To circumvent this situation, the glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(),
	which ensures that all extensions with valid entry points will be exposed.
	*/

	glfwMakeContextCurrent(glWindow);

	glewExperimental = GLEW_OK;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		// Todo: Log error
		LogHandler::DoLog((const char*)glewGetErrorString(error), LogFile::LogType::Error);

		return false;
	}

	
	glClearColor(settings.backgroundColor[0], settings.backgroundColor[1], settings.backgroundColor[2], settings.backgroundColor[3]);

	return true;
}

void Big::Window::Destroy()
{
	if (glWindow)
	{
		glfwDestroyWindow(glWindow);
		glWindow = nullptr;
	}
}

bool Big::Window::Closing()
{
	return glfwWindowShouldClose(glWindow);
}

void Big::Window::BeginRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Big::Window::EndRender()
{
	glfwSwapBuffers(glWindow);
}

