#include "ShaderLoader.h"

#include <exception>
#include "../IO/FileUtils.h"
#include "ShaderCompileException.h"
#include "LoadUniformException.h"
#include "../Log.h"

using namespace SimpleGameEngine::IO;
using namespace SimpleGameEngine::Shaders;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{
	Shader ShaderLoader::loadShader(const std::string & vertexFilepath, const std::string & fragmentFilepath)
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

		SGE_CORE_TRACE("Created shader program.\nProgram ID: {0}\nVertex Shader ID: {1}\nVertex Shader File: {2}\nFragment Shader ID: {3}\nFragment Shader File: {4}",
			programId, vertexShaderId, vertexFilepath, fragmentShaderId, fragmentFilepath);

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

		// Create shader object
		Shader shader(programId, vertexShaderId, fragmentShaderId);
		shader.setLoaded(true);

		return shader;
	}

	void ShaderLoader::startShader(Shader & shader)
	{
		glUseProgram(shader.getProgramId());
		shader.setRunning(true);
	}

	void ShaderLoader::stopShader(Shader & shader)
	{
		glUseProgram(0);
		shader.setRunning(false);
	}

	void ShaderLoader::destroyShader(Shader & shader)
	{
		glDeleteShader(shader.getVertexShaderId());
		glDeleteShader(shader.getFragmentShaderId());
		glDeleteProgram(shader.getProgramId());

		shader.setLoaded(false);

		SGE_CORE_TRACE("Destroyed shader ID {0}, vertex shader ID {1}, fragment shader ID {2}",
			shader.getProgramId(), shader.getVertexShaderId(), shader.getFragmentShaderId());
	}




	bool ShaderLoader::loadUniform1f(const Shader & shader, const std::string & uniformName, float value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		glUniform1f(location, value);
		return true;
	}

	bool ShaderLoader::loadUniform1i(const Shader & shader, const std::string & uniformName, int value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		glUniform1i(location, value);
		return true;
	}

	bool ShaderLoader::loadUniformVec2f(const Shader & shader, const std::string & uniformName, const Vec2 & value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		glUniform2f(location, value.x, value.y);
		return true;
	}

	bool ShaderLoader::loadUniformVec3f(const Shader & shader, const std::string & uniformName, const Vec3 & value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		glUniform3f(location, value.x, value.y, value.z);
		return true;
	}

	bool ShaderLoader::loadUniformVec4f(const Shader & shader, const std::string & uniformName, const Vec4 & value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		glUniform4f(location, value.x, value.y, value.z, value.w);
		return true;
	}

	bool ShaderLoader::loadUniformMat4f(const Shader & shader, const std::string & uniformName, const Mat4 & value)
	{
		GLint location = glGetUniformLocation(shader.getProgramId(), uniformName.c_str());
		if (location == -1)
		{
			SGE_CORE_WARNING("Failed to load uniform {0} to shader ID {0}", uniformName, shader.getProgramId());
			return false;
		}
		
		// GLSL matrices are row-major - must transpose matrices passed in
		glUniformMatrix4fv(location, 1, GL_TRUE, value.elements);
		return true;
	}
}
