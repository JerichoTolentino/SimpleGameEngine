#include "sgepch.h"
#include "FboLoader.h"

using namespace SimpleGameEngine::OpenGL;

namespace SimpleGameEngine::Loaders
{
	void FboLoader::BindFrameBuffer(const OpenGL::FrameBufferObject & fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo.getFboId());
		glViewport(0, 0, fbo.getWidth(), fbo.getHeight());
	}

	GLuint FboLoader::GenerateFrameBuffer()
	{
		GLuint id;
		glGenFramebuffers(1, &id);

		// Attach color attachment slot 0
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		return id;
	}

	GLuint FboLoader::GenerateFboColorTexture(int width, int height)
	{
		GLuint id;
		glGenTextures(1, &id);

		// Set texture parameters
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		// Attach to current FBO
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);

		return id;
	}
	
	GLuint FboLoader::GenerateFboDepthTexture(int width, int height)
	{
		GLuint id;
		glGenTextures(1, &id);

		// Set texture parameters
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Attach to current FBO
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0);

		return id;
	}
	
	GLuint FboLoader::GenerateFboDepthBuffer(int width, int height)
	{
		GLuint id;
		glGenRenderbuffers(1, &id);

		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		
		// Attach to current FBO
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);

		return id;
	}



	OpenGL::WaterReflectionFbo FboLoader::CreateWaterReflectionFbo(int width, int height)
	{
		GLuint fboId = FboLoader::GenerateFrameBuffer();
		GLuint textureId = FboLoader::GenerateFboColorTexture(width, height);
		GLuint depthBufferId = FboLoader::GenerateFboDepthBuffer(width, height);

		return WaterReflectionFbo(fboId, textureId, depthBufferId, width, height);
	}

	OpenGL::WaterRefractionFbo FboLoader::CreateWaterRefractionFbo(int width, int height)
	{
		GLuint fboId = FboLoader::GenerateFrameBuffer();
		GLuint textureId = FboLoader::GenerateFboColorTexture(width, height);
		GLuint depthTextureId = FboLoader::GenerateFboDepthTexture(width, height);

		return WaterRefractionFbo(fboId, textureId, depthTextureId, width, height);
	}
}
