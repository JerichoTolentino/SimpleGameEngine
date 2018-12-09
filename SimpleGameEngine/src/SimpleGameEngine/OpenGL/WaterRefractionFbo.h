#pragma once
#include "FrameBufferObject.h"

namespace SimpleGameEngine::OpenGL
{
	class WaterRefractionFbo : public FrameBufferObject
	{
	private:
		GLuint m_textureId;
		GLuint m_depthTextureId;



	public:
		WaterRefractionFbo();
		WaterRefractionFbo(const WaterRefractionFbo & other);
		WaterRefractionFbo(GLuint fboId, GLuint textureId, GLuint depthTextureId, int width, int height);
		virtual ~WaterRefractionFbo();



		GLuint getTextureId() const;
		GLuint getDepthTextureId() const;



		WaterRefractionFbo & operator=(const WaterRefractionFbo & other);
	};
}
