#include "sgepch.h"
#include "Event.h"

namespace SimpleGameEngine::Events
{
	Event::Event()
	{
		m_handled = false;
	}

	Event::Event(const Event & other)
	{
		m_handled = other.m_handled;
	}
	
	Event::~Event()
	{
	}
	
	
	
	bool Event::isHandled() const
	{
		return m_handled;
	}
	
	void Event::setHandled(bool val)
	{
		m_handled = val;
	}
	
	
	
	Event & Event::operator=(const Event & other)
	{
		m_handled = other.m_handled;

		return *this;
	}
}