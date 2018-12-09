#include "sgepch.h"
#include "WaterRefractionFbo.h"

namespace SimpleGameEngine::OpenGL
{
	WaterRefractionFbo::WaterRefractionFbo()
	{
	}

	WaterRefractionFbo::WaterRefractionFbo(const WaterRefractionFbo & other)
		: WaterRefractionFbo(other.m_fboId, other.m_textureId, other.m_depthTextureId)
	{
	}

	WaterRefractionFbo::WaterRefractionFbo(GLuint fboId, GLuint textureId, GLuint depthTextureId)
		: m_fboId(fboId), m_textureId(textureId), m_depthTextureId(depthTextureId)
	{
	}

	WaterRefractionFbo::~WaterRefractionFbo()
	{
	}



	GLuint WaterRefractionFbo::getFboId() const
	{
		return m_fboId;
	}

	GLuint WaterRefractionFbo::getTextureId() const
	{
		return m_textureId;
	}

	GLuint WaterRefractionFbo::getDepthTextureId() const
	{
		return m_depthTextureId;
	}



	WaterRefractionFbo & WaterRefractionFbo::operator=(const WaterRefractionFbo & other)
	{
		m_fboId = other.m_fboId;
		m_textureId = other.m_textureId;
		m_depthTextureId = other.m_depthTextureId;

		return *this;
	}
}
