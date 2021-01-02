#include "engine.h"

#include "utils/gl_utils.h"
#include "utils/window_utils.h"

#include "core/managers/texture_manager.h"

#include <iostream>

using namespace std;


WindowObject* Engine::window = nullptr;

WindowObject* Engine::Init(WindowProperties & props)
{
	/* Initialize the library */
	if (!glfwInit())
		exit(0);

	window = new WindowObject(props);

	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Serious problem
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(0);
	}

	TextureManager::Init(window->props.selfDirPath);

	return window;
}

WindowObject* Engine::GetWindow()
{
	return window;
}

void Engine::Exit()
{
	cout << "=====================================================" << endl;
	cout << "Engine closed. Exit" << endl;
	glfwTerminate();
}

double Engine::GetElapsedTime()
{
	return glfwGetTime();
}
