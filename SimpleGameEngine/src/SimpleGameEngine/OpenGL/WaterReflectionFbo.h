#pragma once
#include "FrameBufferObject.h"

namespace SimpleGameEngine::OpenGL
{
	class WaterReflectionFbo : public FrameBufferObject
	{
	private:
		GLuint m_textureId;
		GLuint m_depthBufferId;



	public:
		WaterReflectionFbo();
		WaterReflectionFbo(const WaterReflectionFbo & other);
		WaterReflectionFbo(GLuint fboId, GLuint textureId, GLuint depthBufferId, int width, int height);
		virtual ~WaterReflectionFbo();



		GLuint getTextureId() const;
		GLuint getDepthBufferId() const;



		WaterReflectionFbo & operator=(const WaterReflectionFbo & other);
	};
}
