#include "TexturePack.h"

namespace SimpleGameEngine::Models
{
	TexturePack::TexturePack()
	{
	}

	TexturePack::TexturePack(GLuint redTextureId, GLuint greenTextureId, GLuint blueTextureId, GLuint backgroundTextureId, GLuint blendMapTextureId)
	{
		m_redTextureId = redTextureId;
		m_greenTextureId = greenTextureId;
		m_blueTextureId = blueTextureId;
		m_backgroundTextureId = backgroundTextureId;
		m_blendMapTextureId = blendMapTextureId;
	}

	TexturePack::TexturePack(const TexturePack & other)
		: TexturePack(other.m_redTextureId, other.m_greenTextureId, other.m_blueTextureId, other.m_backgroundTextureId, other.m_blendMapTextureId)
	{
	}

	TexturePack::~TexturePack()
	{
	}



	GLuint TexturePack::getRedTextureFile() const
	{
		return m_redTextureId;
	}

	GLuint TexturePack::getGreenTextureFile() const
	{
		return m_greenTextureId;
	}

	GLuint TexturePack::getBlueTextureFile() const
	{
		return m_blueTextureId;
	}

	GLuint TexturePack::getBackgroundTextureFile() const
	{
		return m_backgroundTextureId;
	}

	GLuint TexturePack::getBlendMapTextureFile() const
	{
		return m_blendMapTextureId;
	}



	TexturePack TexturePack::operator=(const TexturePack & other)
	{
		m_redTextureId = other.m_redTextureId;
		m_greenTextureId = other.m_greenTextureId;
		m_blueTextureId = other.m_blueTextureId;
		m_backgroundTextureId = other.m_backgroundTextureId;
		m_blendMapTextureId = other.m_blendMapTextureId;

		return *this;
	}

}
