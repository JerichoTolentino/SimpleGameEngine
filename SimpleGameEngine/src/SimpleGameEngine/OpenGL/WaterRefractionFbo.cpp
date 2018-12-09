#include "sgepch.h"
#include "WaterRefractionFbo.h"

namespace SimpleGameEngine::OpenGL
{
	WaterRefractionFbo::WaterRefractionFbo()
	{
	}

	WaterRefractionFbo::WaterRefractionFbo(const WaterRefractionFbo & other)
		: WaterRefractionFbo(other.getFboId(), other.m_textureId, other.m_depthTextureId, other.getWidth(), other.getHeight())
	{
	}

	WaterRefractionFbo::WaterRefractionFbo(GLuint fboId, GLuint textureId, GLuint depthTextureId, int width, int height)
		: FrameBufferObject(fboId, width, height), m_textureId(textureId), m_depthTextureId(depthTextureId)
	{
	}

	WaterRefractionFbo::~WaterRefractionFbo()
	{
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
		FrameBufferObject::operator=(other);

		m_textureId = other.m_textureId;
		m_depthTextureId = other.m_depthTextureId;

		return *this;
	}
}
