#include "sgepch.h"
#include "FboLoader.h"

#include "FboLoadException.h"

using namespace SimpleGameEngine::OpenGL;

namespace SimpleGameEngine::Loaders
{
	void FboLoader::BindFrameBuffer(const OpenGL::FrameBufferObject & fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo.getFboId());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, fbo.getWidth(), fbo.getHeight());
	}

	GLuint FboLoader::GenerateFrameBuffer()
	{
		GLuint id;
		glGenFramebuffers(1, &id);

		// Attach color attachment slot 0
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		SGE_CORE_TRACE("Generated an FBO with ID {0}", id);

		return id;
	}

	GLuint FboLoader::GenerateFboColorTexture(int width, int height)
	{
		GLuint id;
		glGenTextures(1, &id);

		// Set texture parameters
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Switch back to GL_LINEAR if probs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Switch back to GL_LINEAR if probs

		// Might be a bug with NVIDIA OpenGL drivers not liking FBO textures w/o mipmaps...
		// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes#Render_To_Texture

		// Attach to current FBO
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);

		SGE_CORE_TRACE("Generated a {0}x{1} FBO color texture with ID {2}", width, height, id);

		return id;
	}
	
	GLuint FboLoader::GenerateFboDepthTexture(int width, int height)
	{
		GLuint id;
		glGenTextures(1, &id);

		// Set texture parameters
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Attach to current FBO
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0);

		SGE_CORE_TRACE("Generated a {0}x{1} FBO depth texture with ID {2}", width, height, id);

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

		SGE_CORE_TRACE("Generated a {0}x{1} FBO depth buffer with ID {2}", width, height, id);

		return id;
	}



	OpenGL::WaterReflectionFbo FboLoader::CreateWaterReflectionFbo(int width, int height)
	{
		GLuint fboId = FboLoader::GenerateFrameBuffer();
		GLuint textureId = FboLoader::GenerateFboColorTexture(width, height);
		GLuint depthBufferId = FboLoader::GenerateFboDepthBuffer(width, height);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw FboLoadException("Failed to create water reflection FBO.");
		}

		return WaterReflectionFbo(fboId, textureId, depthBufferId, width, height);
	}

	OpenGL::WaterRefractionFbo FboLoader::CreateWaterRefractionFbo(int width, int height)
	{
		GLuint fboId = FboLoader::GenerateFrameBuffer();
		GLuint textureId = FboLoader::GenerateFboColorTexture(width, height);
		GLuint depthTextureId = FboLoader::GenerateFboDepthTexture(width, height);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw FboLoadException("Failed to create water refraction FBO.");
		}

		return WaterRefractionFbo(fboId, textureId, depthTextureId, width, height);
	}
}
