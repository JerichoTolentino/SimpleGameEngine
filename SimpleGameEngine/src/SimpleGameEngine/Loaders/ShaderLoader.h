#pragma once
#include <GL/glew.h>
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"
#include "../Math/Mat4.h"
#include "../Shaders/Shader.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Loaders
{
	class ShaderLoader
	{
	private:
		ShaderLoader();
	public:
		~ShaderLoader();



		static Shader loadShader(std::string vertexFilepath, std::string fragmentFilepath);
		static void startShader(Shader shader);
		static void stopShader(Shader shader);
		static void destroyShader(Shader shader);



		static void loadUniform1f(Shader shader, std::string uniformName, float value);
		static void loadUniform1i(Shader shader, std::string uniformName, int value);
		static void loadUniformVec2f(Shader shader, std::string uniformName, Vec2 value);
		static void loadUniformVec3f(Shader shader, std::string uniformName, Vec3 value);
		static void loadUniformVec4f(Shader shader, std::string uniformName, Vec4 value);
		static void loadUniformMat4f(Shader shader, std::string uniformName, Mat4 value);
	};
}
