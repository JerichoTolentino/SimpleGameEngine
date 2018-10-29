#include <SimpleGameEngine.h>

class Sandbox : public SimpleGameEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

SimpleGameEngine::Application * SimpleGameEngine::CreateApplication()
{
	return new Sandbox();
}