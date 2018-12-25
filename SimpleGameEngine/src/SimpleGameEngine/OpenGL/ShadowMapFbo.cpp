#include "sgepch.h"
#include "ShadowMapFbo.h"

namespace SimpleGameEngine::OpenGL
{
	ShadowMapFbo::ShadowMapFbo()
	{
	}

	ShadowMapFbo::ShadowMapFbo(const ShadowMapFbo & other)
		: ShadowMapFbo(other.getFboId(), other.getWidth(), other.getHeight(), other.m_depthTextureId)
	{
	}

	ShadowMapFbo::ShadowMapFbo(GLuint fboId, int width, int height, GLuint depthTextureId)
		: FrameBufferObject(fboId, width, height), m_depthTextureId(depthTextureId)
	{
	}

	ShadowMapFbo::~ShadowMapFbo()
	{
	}



	void ShadowMapFbo::bind() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBufferObject::getFboId());
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, FrameBufferObject::getWidth(), FrameBufferObject::getHeight());
	}

	GLuint ShadowMapFbo::getDepthTextureId() const
	{
		return m_depthTextureId;
	}



	ShadowMapFbo & ShadowMapFbo::operator=(const ShadowMapFbo & other)
	{
		FrameBufferObject::operator=(other);

		m_depthTextureId = other.m_depthTextureId;

		return *this;
	}
}
