#include "sgepch.h"
#include "FrameBufferObject.h"

namespace SimpleGameEngine::OpenGL
{
	FrameBufferObject::FrameBufferObject()
	{
	}

	FrameBufferObject::FrameBufferObject(const FrameBufferObject & other)
		: FrameBufferObject(other.m_fboId, other.m_width, other.m_height)
	{
	}

	FrameBufferObject::FrameBufferObject(GLuint fboId, int width, int height)
		: m_fboId(fboId), m_width(width), m_height(height)
	{
	}

	FrameBufferObject::~FrameBufferObject()
	{
	}
	
	
	
	GLuint FrameBufferObject::getFboId() const
	{
		return m_fboId;
	}
	
	int FrameBufferObject::getWidth() const
	{
		return m_width;
	}
	
	int FrameBufferObject::getHeight() const
	{
		return m_height;
	}

	void FrameBufferObject::setWidth(int width)
	{
		m_width = width;
	}

	void FrameBufferObject::setHeight(int height)
	{
		m_height = height;
	}
	
	
	
	FrameBufferObject & FrameBufferObject::operator=(const FrameBufferObject & other)
	{
		m_fboId = other.m_fboId;
		m_width = other.m_width;
		m_height = other.m_height;

		return *this;
	}
}
