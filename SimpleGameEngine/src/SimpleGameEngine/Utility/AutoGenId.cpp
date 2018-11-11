#include "AutoGenId.h"

namespace SimpleGameEngine::Utility
{
	unsigned int AutoGenId::s_id = 0;



	AutoGenId::AutoGenId()
	{
		m_id = s_id++;
	}

	AutoGenId::AutoGenId(const AutoGenId & other)
		: AutoGenId(other.m_id)
	{
	}


	AutoGenId::~AutoGenId()
	{
	}



	unsigned int AutoGenId::___getObjectId() const
	{
		return m_id;
	}

	AutoGenId & AutoGenId::operator=(const AutoGenId & other)
	{
		m_id = other.m_id;

		return *this;
	}
}
