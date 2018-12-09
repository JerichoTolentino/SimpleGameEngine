#include "sgepch.h"
#include "WaterReflectionFbo.h"

namespace SimpleGameEngine::OpenGL
{
	WaterReflectionFbo::WaterReflectionFbo()
	{
	}

	WaterReflectionFbo::WaterReflectionFbo(const WaterReflectionFbo & other)
		: WaterReflectionFbo(other.m_fboId, other.m_textureId, other.m_depthBufferId)
	{
	}

	WaterReflectionFbo::WaterReflectionFbo(GLuint fboId, GLuint textureId, GLuint depthBufferId)
		: m_fboId(fboId), m_textureId(textureId), m_depthBufferId(depthBufferId)
	{
	}

	WaterReflectionFbo::~WaterReflectionFbo()
	{
	}



	GLuint WaterReflectionFbo::getFboId() const
	{
		return m_fboId;
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
		m_fboId = other.m_fboId;
		m_textureId = other.m_textureId;
		m_depthBufferId = other.m_depthBufferId;

		return *this;
	}
}
