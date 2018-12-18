#pragma once
#include "FrameBufferObject.h"

namespace SimpleGameEngine::OpenGL
{
	class ShadowMapFbo : public FrameBufferObject
	{
	private:
		GLuint m_depthTextureId;



	public:
		ShadowMapFbo();
		ShadowMapFbo(const ShadowMapFbo & other);
		ShadowMapFbo(GLuint fboId, int width, int height, GLuint depthTextureId);
		virtual ~ShadowMapFbo();



		GLuint getDepthTextureId() const;



		ShadowMapFbo & operator=(const ShadowMapFbo & other);
	};
}
