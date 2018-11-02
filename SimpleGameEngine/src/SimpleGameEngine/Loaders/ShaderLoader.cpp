#include "ShaderLoader.h"

#include <exception>
#include "../IO/FileUtils.h"
#include "ShaderCompileException.h"
#include "LoadUniformException.h"

using namespace SimpleGameEngine::IO;

namespace SimpleGameEngine::Loaders
{
	ShaderLoader::ShaderLoader()
	{
	}

	ShaderLoader::ShaderLoader(const char *vertex, const char *fragment)
	{
		std::string vertexShader = FileUtils::loadFileToString(vertex);
		std::string fragmentShader = FileUtils::loadFileToString(fragment);
		const GLchar *vShader = vertexShader.c_str();
		const GLchar *fShader = fragmentShader.c_str();

		programID = glCreateProgram();

		vShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShaderID, 1, &vShader, NULL);
		fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShaderID, 1, &fShader, NULL);

		GLint vCompileStatus = -1;

		glCompileShader(vShaderID);
		glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &vCompileStatus);
		if (vCompileStatus == GL_FALSE)
		{
			GLint logSize = 0;
			glGetShaderiv(vShaderID, GL_INFO_LOG_LENGTH, &logSize);
			GLchar *log = new GLchar[logSize];
			glGetShaderInfoLog(vShaderID, logSize, NULL, log);
			throw ShaderCompileException("Failed to compile vertex shader.", std::string(log));
		}

		GLint fCompileStatus = -1;

		glCompileShader(fShaderID);
		glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &fCompileStatus);
		if (fCompileStatus == GL_FALSE)
		{
			GLint logSize = 0;
			glGetShaderiv(fShaderID, GL_INFO_LOG_LENGTH, &logSize);
			GLchar *log = new GLchar[logSize];
			glGetShaderInfoLog(fShaderID, logSize, NULL, log);
			throw ShaderCompileException("Failed to compile fragment shader.", std::string(log));
		}

		if (vCompileStatus == 0 || fCompileStatus == 0)
			system("PAUSE");

		glAttachShader(programID, vShaderID);
		glAttachShader(programID, fShaderID);

		glLinkProgram(programID);
	}

	ShaderLoader::~ShaderLoader()
	{
	}




	void ShaderLoader::start() const
	{
		glUseProgram(programID);
	}

	void ShaderLoader::stop() const
	{
		glUseProgram(0);
	}

	void ShaderLoader::destroy() const
	{
		glDeleteShader(vShaderID);
		glDeleteShader(fShaderID);
		glDeleteProgram(programID);
	}




	void ShaderLoader::loadUniform1f(float value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));		
		
		glUniform1f(location, value);
	}

	void ShaderLoader::loadUniform1i(int value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));
		
		glUniform1i(location, value);
	}

	void ShaderLoader::loadUniformVec2f(Vec2 value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));
		
		glUniform2f(location, value.x, value.y);
	}

	void ShaderLoader::loadUniformVec3f(Vec3 value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));
		
		glUniform3f(location, value.x, value.y, value.z);
	}

	void ShaderLoader::loadUniformVec4f(Vec4 value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));
		
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void ShaderLoader::loadUniformMat4f(Mat4 value, const char* uniform) const
	{
		GLint location = glGetUniformLocation(programID, uniform);
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + std::string(uniform));
		
		glUniformMatrix4fv(location, 1, GL_TRUE, value.elements);	//NOTE: GLSL Matrices are ROW MAJOR!!! (MUST TRANPOSE!)
	}
}
