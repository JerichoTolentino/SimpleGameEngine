#include "Application.h"
#include "Display/Window.h"

using namespace SimpleGameEngine::Display;

namespace SimpleGameEngine
{
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		Window window;
		while (true)
		{
			window.clear();
			window.update();
		}
		window.forceClose();
	}
}
