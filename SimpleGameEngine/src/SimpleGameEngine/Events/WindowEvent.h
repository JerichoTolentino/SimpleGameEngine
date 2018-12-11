#pragma once
#include "Event.h"

namespace SimpleGameEngine::Events
{
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_width;
		unsigned int m_height;



	public:
		WindowResizeEvent();
		WindowResizeEvent(const WindowResizeEvent & other);
		WindowResizeEvent(unsigned int width, unsigned int height);
		~WindowResizeEvent();



		unsigned int getWidth() const;
		unsigned int getHeight() const;



		WindowResizeEvent & operator=(const WindowResizeEvent & other);
	};
}