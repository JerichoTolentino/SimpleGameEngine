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



		virtual GLuint getFboId() const;
		virtual int getWidth() const;
		virtual int getHeight() const;

		virtual void setWidth(int width);
		virtual void setHeight(int height);



		FrameBufferObject & operator=(const FrameBufferObject & other);
	};
}
