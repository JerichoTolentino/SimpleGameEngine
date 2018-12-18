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
