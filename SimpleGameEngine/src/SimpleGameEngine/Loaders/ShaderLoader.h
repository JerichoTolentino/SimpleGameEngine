#pragma once
#include <GL/glew.h>
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"
#include "../Math/Mat4.h"
#include "../Shaders/Shader.h"

namespace SimpleGameEngine::Loaders
{
	class ShaderLoader
	{
	public:
		/// <summary>
		/// Loads a shader program into memory.
		/// </summary>
		/// <param name="vertexFilepath">The vertex shader file.</param>
		/// <param name="fragmentFilepath">The fragment shader file.</param>
		/// <returns></returns>
		static Shaders::Shader loadShader(const std::string & vertexFilepath, const std::string & fragmentFilepath);
		
		/// <summary>
		/// Starts a shader.
		/// </summary>
		/// <param name="shader"></param>
		static void startShader(Shaders::Shader & shader);

		/// <summary>
		/// Stops a shader.
		/// </summary>
		/// <param name="shader"></param>
		static void stopShader(Shaders::Shader & shader);
		
		/// <summary>
		/// Deletes a shader program from memory.
		/// </summary>
		/// <param name="shader"></param>
		static void destroyShader(Shaders::Shader & shader);



		/// <summary>
		/// Loads a float to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniform1f(const Shaders::Shader & shader, const std::string & uniformName, float value);

		/// <summary>
		/// Loads an integer to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniform1i(const Shaders::Shader & shader, const std::string & uniformName, int value);

		/// <summary>
		/// Loads a 2D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniformVec2f(const Shaders::Shader & shader, const std::string & uniformName, const Math::Vec2 & value);
		
		/// <summary>
		/// Loads a 3D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniformVec3f(const Shaders::Shader & shader, const std::string & uniformName, const Math::Vec3 & value);
		
		/// <summary>
		/// Loads a 4D vector to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniformVec4f(const Shaders::Shader & shader, const std::string & uniformName, const Math::Vec4 & value);
		
		/// <summary>
		/// Loads a 4x4 matrix to a uniform variable in a shader.
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="uniformName"></param>
		/// <param name="value"></param>
		static bool loadUniformMat4f(const Shaders::Shader & shader, const std::string & uniformName, const Math::Mat4 & value);
	};
}
