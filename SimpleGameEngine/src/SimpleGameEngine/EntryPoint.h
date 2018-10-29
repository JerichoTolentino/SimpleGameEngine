#pragma once

#ifdef SGE_PLATFORM_WINDOWS

extern SimpleGameEngine::Application * SimpleGameEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = SimpleGameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif