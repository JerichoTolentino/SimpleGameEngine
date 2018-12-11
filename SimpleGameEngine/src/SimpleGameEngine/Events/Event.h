#pragma once

#include <string>

namespace SimpleGameEngine::Events
{
	class Event
	{
	private:
		bool m_handled = false;



	protected:
		Event();
		Event(const Event & other);
		~Event();



	public:
		bool isHandled() const;
		void setHandled(bool val);



		Event & operator=(const Event & other);
	};
}
