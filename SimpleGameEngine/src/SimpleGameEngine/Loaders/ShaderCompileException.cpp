#include "sgepch.h"
#include "ShaderCompileException.h"

namespace SimpleGameEngine::Loaders
{
	ShaderCompileException::ShaderCompileException()
	{
	}

	SimpleGameEngine::Loaders::ShaderCompileException::ShaderCompileException(std::string message)
		: std::exception(message.c_str())
	{
	}

	ShaderCompileException::ShaderCompileException(std::string message, std::string logMessage)
		: std::exception(message.c_str())
	{
		m_logMessage = logMessage;
	}


	ShaderCompileException::~ShaderCompileException()
	{
	}



	std::string ShaderCompileException::getLogMessage() const
	{
		return m_logMessage;
	}
}
