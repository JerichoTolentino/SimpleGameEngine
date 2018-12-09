#pragma once
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"

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


		
		static OpenGL::WaterReflectionFbo CreateWaterReflectionFbo(int width, int height);
		static OpenGL::WaterRefractionFbo CreateWaterRefractionFbo(int width, int height);
	};
}
