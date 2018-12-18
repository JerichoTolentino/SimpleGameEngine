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
		/// Binds a <see cref="FrameBufferObject"/>.
		/// </summary>
		static void BindFrameBuffer(const OpenGL::FrameBufferObject & fbo);

		static GLuint GenerateFrameBuffer();
		static GLuint GenerateFboColorTexture(int width, int height);
		static GLuint GenerateFboDepthTexture(int width, int height);
		static GLuint GenerateFboDepthBuffer(int width, int height);


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
