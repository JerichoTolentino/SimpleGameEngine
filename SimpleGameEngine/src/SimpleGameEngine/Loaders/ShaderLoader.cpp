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

	ShaderLoader::~ShaderLoader()
	{
	}




	Shader ShaderLoader::loadShader(std::string vertexFilepath, std::string fragmentFilepath)
	{
		// Load shader files
		std::string vertexShader = FileUtils::loadFileToString(vertexFilepath);
		std::string fragmentShader = FileUtils::loadFileToString(fragmentFilepath);
		const GLchar *vShader = vertexShader.c_str();
		const GLchar *fShader = fragmentShader.c_str();

		// Create shader program
		GLuint programId = glCreateProgram();
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vShader, NULL);
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fShader, NULL);

		// Compile vertex shader
		GLint vCompileStatus = GL_FALSE;
		glCompileShader(vertexShaderId);
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &vCompileStatus);
		if (vCompileStatus == GL_FALSE)
		{
			// Get compiler error log
			GLint logSize = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &logSize);
			GLchar *log = new GLchar[logSize];
			glGetShaderInfoLog(vertexShaderId, logSize, NULL, log);

			throw ShaderCompileException("Failed to compile vertex shader.", std::string(log));
		}

		// Compile fragment shader
		GLint fCompileStatus = GL_FALSE;
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &fCompileStatus);
		if (fCompileStatus == GL_FALSE)
		{
			// Get compiler error log
			GLint logSize = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &logSize);
			GLchar *log = new GLchar[logSize];
			glGetShaderInfoLog(fragmentShaderId, logSize, NULL, log);

			throw ShaderCompileException("Failed to compile fragment shader.", std::string(log));
		}

		// Attach shaders and link program
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);
		glLinkProgram(programId);

		return Shader(programId, vertexShaderId, fragmentShaderId);
	}

	void ShaderLoader::startShader(Shader shader)
	{
		glUseProgram(shader.getProgramId());
	}

	void ShaderLoader::stopShader()
	{
		glUseProgram(0);
	}

	void ShaderLoader::destroyShader(Shader shader)
	{
		glDeleteShader(shader.getVertexShaderId());
		glDeleteShader(shader.getFragmentShaderId());
		glDeleteProgram(shader.getProgramId());
	}




	void ShaderLoader::loadUniform1f(Shader shader, std::string uniformName, float value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		glUniform1f(location, value);
	}

	void ShaderLoader::loadUniform1i(Shader shader, std::string uniformName, int value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		glUniform1i(location, value);
	}

	void ShaderLoader::loadUniformVec2f(Shader shader, std::string uniformName, Vec2 value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		glUniform2f(location, value.x, value.y);
	}

	void ShaderLoader::loadUniformVec3f(Shader shader, std::string uniformName, Vec3 value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		glUniform3f(location, value.x, value.y, value.z);
	}

	void ShaderLoader::loadUniformVec4f(Shader shader, std::string uniformName, Vec4 value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void ShaderLoader::loadUniformMat4f(Shader shader, std::string uniformName, Mat4 value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
			throw LoadUniformException("Failed to get location of uniform variable " + uniformName);
		
		// GLSL matrices are row-major - must transpose matrices passed in
		glUniformMatrix4fv(location, 1, GL_TRUE, value.elements);
	}
}
