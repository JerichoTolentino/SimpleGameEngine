#include "sgepch.h"
#include "WaterReflectionFbo.h"

namespace SimpleGameEngine::OpenGL
{
	WaterReflectionFbo::WaterReflectionFbo()
	{
	}

	WaterReflectionFbo::WaterReflectionFbo(const WaterReflectionFbo & other)
		: WaterReflectionFbo(other.getFboId(), other.m_textureId, other.m_depthBufferId, other.getWidth(), other.getHeight())
	{
	}

	WaterReflectionFbo::WaterReflectionFbo(GLuint fboId, GLuint textureId, GLuint depthBufferId, int width, int height)
		: FrameBufferObject(fboId, width, height), m_textureId(textureId), m_depthBufferId(depthBufferId)
	{
	}

	WaterReflectionFbo::~WaterReflectionFbo()
	{
	}



	GLuint WaterReflectionFbo::getTextureId() const
	{
		return m_textureId;
	}

	GLuint WaterReflectionFbo::getDepthBufferId() const
	{
		return m_depthBufferId;
	}



	WaterReflectionFbo & WaterReflectionFbo::operator=(const WaterReflectionFbo & other)
	{
		FrameBufferObject::operator=(other);

		m_textureId = other.m_textureId;
		m_depthBufferId = other.m_depthBufferId;

		return *this;
	}
}
