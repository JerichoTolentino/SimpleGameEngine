#pragma once
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"

namespace SimpleGameEngine::Loaders
{
	class FboLoader
	{
	public:
		/// <summary>
		/// Binds an OpenGL FrameBufferObject.
		/// Pass in 0 to <paramref name="fboId"/> to use the default FBO.
		/// </summary>
		static void BindFrameBuffer(GLuint fboId, int width, int height);

		static GLuint GenerateFrameBuffer();
		static GLuint GenerateFboColorTexture(int width, int height);
		static GLuint GenerateFboDepthTexture(int width, int height);
		static GLuint GenerateFboDepthBuffer(int width, int height);


		
		static OpenGL::WaterReflectionFbo CreateWaterReflectionFbo(int width, int height);
		static OpenGL::WaterRefractionFbo CreateWaterRefractionFbo(int width, int height);
	};
}
