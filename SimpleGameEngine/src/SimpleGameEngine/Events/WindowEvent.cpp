#include "sgepch.h"
#include "WindowEvent.h"

namespace SimpleGameEngine::Events
{

#pragma region WindowResizeEvent

	WindowResizeEvent::WindowResizeEvent()
		: Event()
	{
	}

	WindowResizeEvent::WindowResizeEvent(const WindowResizeEvent & other)
		: Event(other), m_width(other.m_width), m_height(other.m_height)
	{
	}

	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
		: Event(), m_width(width), m_height(height)
	{
	}

	WindowResizeEvent::~WindowResizeEvent()
	{
	}



	unsigned int WindowResizeEvent::getWidth() const
	{
		return m_width;
	}

	unsigned int WindowResizeEvent::getHeight() const
	{
		return m_height;
	}



	WindowResizeEvent & WindowResizeEvent::operator=(const WindowResizeEvent & other)
	{
		m_width = other.m_width;
		m_height = other.m_height;

		return *this;
	}

#pragma endregion

}
