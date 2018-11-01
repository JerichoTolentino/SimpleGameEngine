#pragma once
#include <GL/glew.h>
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Vec4.h"
#include "../Math/Mat4.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{
	class ShaderLoader
	{
	private:
		ShaderLoader();
	public:
		ShaderLoader(const char *vertex, const char *fragment);
		~ShaderLoader();



		void start() const;
		void stop() const;
		void destroy() const;



		void loadUniform1f(float value, const char* uniform) const;
		void loadUniform1i(int value, const char* uniform) const;
		void loadUniformVec2f(Vec2 value, const char* uniform) const;
		void loadUniformVec3f(Vec3 value, const char* uniform) const;
		void loadUniformVec4f(Vec4 value, const char* uniform) const;
		void loadUniformMat4f(Mat4 value, const char* uniform) const;
	};
}
