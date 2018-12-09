#pragma once

namespace SimpleGameEngine::OpenGL
{
	class WaterRefractionFbo
	{
	private:
		GLuint m_fboId;
		GLuint m_textureId;
		GLuint m_depthTextureId;



	public:
		WaterRefractionFbo();
		WaterRefractionFbo(const WaterRefractionFbo & other);
		WaterRefractionFbo(GLuint fboId, GLuint textureId, GLuint depthTextureId);
		virtual ~WaterRefractionFbo();



		GLuint getFboId() const;
		GLuint getTextureId() const;
		GLuint getDepthTextureId() const;



		WaterRefractionFbo & operator=(const WaterRefractionFbo & other);
	};
}
