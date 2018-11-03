#include "TextureLoadException.h"

namespace SimpleGameEngine::Loaders
{
	TextureLoadException::TextureLoadException()
	{
	}

	TextureLoadException::TextureLoadException(std::string message)
		: std::exception(message.c_str())
	{
	}

	TextureLoadException::~TextureLoadException()
	{
	}
}
