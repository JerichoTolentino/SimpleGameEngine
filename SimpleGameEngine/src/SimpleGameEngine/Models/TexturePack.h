#pragma once
#include <string>
#include <GL/glew.h>

namespace SimpleGameEngine::Models
{
	class TexturePack
	{
	private:
		GLuint m_redTextureId;
		GLuint m_greenTextureId;
		GLuint m_blueTextureId;
		GLuint m_backgroundTextureId;
		GLuint m_blendMapTextureId;



	public:
		TexturePack();
		TexturePack(GLuint redTextureId, GLuint greenTextureId, GLuint blueTextureId, GLuint backgroundTextureId, GLuint blendMapTextureId);
		TexturePack(const TexturePack & other);
		virtual ~TexturePack();



		GLuint getRedTextureId() const;
		GLuint getGreenTextureId() const;
		GLuint getBlueTextureId() const;
		GLuint getBackgroundTextureId() const;
		GLuint getBlendMapTextureId() const;



		TexturePack & operator=(const TexturePack & other);
	};
}
