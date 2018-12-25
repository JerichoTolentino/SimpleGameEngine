#include "sgepch.h"
#include "FboLoader.h"

#include "FboLoadException.h"

using namespace SimpleGameEngine::OpenGL;

namespace SimpleGameEngine::Loaders
{
	OpenGL::WaterReflectionFbo FboLoader::CreateWaterReflectionFbo(int width, int height)
	{
		// Generate FBO
		GLuint fboId;
		glGenFramebuffers(1, &fboId);
		glBindFramebuffer(GL_FRAMEBUFFER, fboId);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		// Generate color texture attachment
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);

		// Generate depth buffer attachment
		GLuint depthBufferId;
		glGenRenderbuffers(1, &depthBufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);

		// Ensure FBO is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw FboLoadException("Failed to create water reflection FBO.");
		}

		SGE_CORE_TRACE("Generated a {0}x{1} WaterReflectionFBO with ID: {2}\tColorTextureID: {3}\tDepthBufferId: {4}",
					   width, height, fboId, textureId, depthBufferId);

		return WaterReflectionFbo(fboId, textureId, depthBufferId, width, height);
	}

	OpenGL::WaterRefractionFbo FboLoader::CreateWaterRefractionFbo(int width, int height)
	{
		// Generate FBO
		GLuint fboId;
		glGenFramebuffers(1, &fboId);
		glBindFramebuffer(GL_FRAMEBUFFER, fboId);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		// Generate color texture attachment
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);

		// Generate depth texture attachment
		GLuint depthTextureId;
		glGenTextures(1, &depthTextureId);
		glBindTexture(GL_TEXTURE_2D, depthTextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);

		// Ensure FBO is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw FboLoadException("Failed to create water refraction FBO.");
		}

		SGE_CORE_TRACE("Generated a {0}x{1} WaterRefractionFBO with ID: {2}\tColorTextureID: {3}\tDepthTextureId: {4}",
					   width, height, fboId, textureId, depthTextureId);

		return WaterRefractionFbo(fboId, textureId, depthTextureId, width, height);
	}

	OpenGL::ShadowMapFbo FboLoader::CreateShadowMapFbo(int width, int height)
	{
		// Generate FBO
		GLuint fboId;
		glGenFramebuffers(1, &fboId);
		glBindFramebuffer(GL_FRAMEBUFFER, fboId);

		// Generate depth texture attachment
		GLuint depthTextureId;
		glGenTextures(1, &depthTextureId);
		glBindTexture(GL_TEXTURE_2D, depthTextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		// Ensure FBO is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw FboLoadException("Failed to create water refraction FBO.");
		}

		SGE_CORE_TRACE("Generated a {0}x{1} ShadowMapFBO with ID: {2}\DepthTextureID: {3}",
					   width, height, fboId, depthTextureId);

		return ShadowMapFbo(fboId, width, height, depthTextureId);
	}
}
