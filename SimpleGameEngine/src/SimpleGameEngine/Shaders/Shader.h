#pragma once
#include <GL/glew.h>

namespace SimpleGameEngine::Shaders
{
	class Shader
	{
	private:
		GLuint programID, vShaderID, fShaderID;
	public:
		Shader();
		virtual ~Shader();
	};
}
