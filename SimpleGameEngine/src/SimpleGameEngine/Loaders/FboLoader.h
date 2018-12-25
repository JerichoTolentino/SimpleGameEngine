#pragma once
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"
#include "../OpenGL/ShadowMapFbo.h"

namespace SimpleGameEngine::Loaders
{
	class FboLoader
	{
	public:
		/// <summary>
		/// Creates a <see cref="WaterReflectionFbo"/>.
		/// </summary>
		/// <exception cref="FboLoadException"></exception>
		static OpenGL::WaterReflectionFbo CreateWaterReflectionFbo(int width, int height);

		/// <summary>
		/// Creates a <see cref="WaterRefractionFbo"/>.
		/// </summary>
		/// <exception cref="FboLoadException"></exception>
		static OpenGL::WaterRefractionFbo CreateWaterRefractionFbo(int width, int height);

		/// <summary>
		/// Creates a <see cref="ShadowMapFbo"/>.
		/// </summary>
		/// <exception cref="FboLoadException"></exception>
		static OpenGL::ShadowMapFbo CreateShadowMapFbo(int width, int height);
	};
}
