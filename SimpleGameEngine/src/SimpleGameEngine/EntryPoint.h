#pragma once

#ifdef SGE_PLATFORM_WINDOWS

extern SimpleGameEngine::Application * SimpleGameEngine::CreateApplication();

int main(int argc, char** argv)
{
	SimpleGameEngine::Log::init();
	SGE_CORE_WARNING("What");
	SGE_ERROR("Oh no");

	auto app = SimpleGameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif