#pragma once

namespace SimpleGameEngine::OpenGL
{
	class WaterReflectionFbo
	{
	private:
		GLuint m_fboId;
		GLuint m_textureId;
		GLuint m_depthBufferId;



	public:
		WaterReflectionFbo();
		WaterReflectionFbo(const WaterReflectionFbo & other);
		WaterReflectionFbo(GLuint fboId, GLuint textureId, GLuint depthBufferId);
		virtual ~WaterReflectionFbo();



		GLuint getFboId() const;
		GLuint getTextureId() const;
		GLuint getDepthBufferId() const;



		WaterReflectionFbo & operator=(const WaterReflectionFbo & other);
	};
}
