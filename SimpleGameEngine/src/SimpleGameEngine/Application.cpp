#include "Application.h"
#include "Display/Window.h"
#include "Parsers/WavefrontObjParser.h"
#include "Parsers/ParseException.h"
#include "Models/GeometryModel.h"
#include "Log.h"

using namespace SimpleGameEngine::Display;
using namespace SimpleGameEngine::Parsers;
using namespace SimpleGameEngine::Models;

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
		try
		{
			GeometryModel stallModel = WavefrontObjParser::parseFile("D:/Blender Files/stall.obj");
			SGE_CORE_WARNING("Successfully loaded stall model.");
		}
		catch (ParseException e)
		{
			SGE_ERROR("Failed to load stall model." + std::string(e.what()));
		}

		Window window;
		while (true)
		{
			window.clear();
			window.update();
		}
		window.forceClose();
	}
}
