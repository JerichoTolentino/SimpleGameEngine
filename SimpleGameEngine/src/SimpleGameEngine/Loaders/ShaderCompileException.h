#pragma once
#include <string>
#include <exception>

namespace SimpleGameEngine::Loaders
{
	class ShaderCompileException : public std::exception
	{
	private:
		std::string m_logMessage;



	public:
		ShaderCompileException();
		ShaderCompileException(std::string message);
		ShaderCompileException(std::string message, std::string logMessage);
		virtual ~ShaderCompileException();


		/// <summary>
		/// Gets the log message of the shader compiler.
		/// </summary>
		/// <returns></returns>
		std::string getLogMessage() const;
	};
}
