#pragma once

namespace SimpleGameEngine::OpenGL
{
	class FrameBufferObject
	{
	private:
		GLuint m_fboId;
		int m_width;
		int m_height;



	public:
		FrameBufferObject();
		FrameBufferObject(const FrameBufferObject & other);
		FrameBufferObject(GLuint fboId, int width, int height);
		virtual ~FrameBufferObject();



		GLuint getFboId() const;
		int getWidth() const;
		int getHeight() const;



		FrameBufferObject & operator=(const FrameBufferObject & other);
	};
}
