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



		/// <summary>
		/// Loads a shader program into memory.
		/// </summary>
		/// <param name="vertexFilepath">The vertex shader file.</param>
		/// <param name="fragmentFilepath">The fragment shader file.</param>
		/// <returns></returns>
		static Shader loadShader(std::string vertexFilepath, std::string fragmentFilepath);
		
		/// <summary>
		/// Starts a shader.
		/// </summary>
		/// <param name="shader"></param>
		static void startShader(Shader shader);

		/// <summary>
		/// Stops a shader.
		/// </summary>
		/// <param name="shader"></param>
		static void stopShader(Shader shader);
		
		/// <summary>
		/// Deletes a shader program from memory.
		/// </summary>
		/// <param name="shader"></param>
		static void destroyShader(Shader shader);



		/// <summary>
		/// Loads a float to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniform1f(Shader shader, std::string uniformName, float value);

		/// <summary>
		/// Loads an integer to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniform1i(Shader shader, std::string uniformName, int value);

		/// <summary>
		/// Loads a 2D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniformVec2f(Shader shader, std::string uniformName, Vec2 value);
		
		/// <summary>
		/// Loads a 3D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniformVec3f(Shader shader, std::string uniformName, Vec3 value);
		
		/// <summary>
		/// Loads a 4D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniformVec4f(Shader shader, std::string uniformName, Vec4 value);
		
		/// <summary>
		/// Loads a 4x4 matrix to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static void loadUniformMat4f(Shader shader, std::string uniformName, Mat4 value);
	};
}
