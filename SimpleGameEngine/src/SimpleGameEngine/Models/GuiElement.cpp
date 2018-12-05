#include "sgepch.h"
#include "GuiElement.h"

namespace SimpleGameEngine::Models
{
	int GuiElement::VERTICES_COUNT = 8;
	int GuiElement::TEXTURE_UVS_COUNT = 8;
	int GuiElement::INDICES_COUNT = 6;

	float * GuiElement::VERTICES = new float[8]
	{
		-1,  1,
		-1,	-1,
		 1,	 1,
		 1,	-1
	};

	float * GuiElement::TEXTURE_UVS = new float[8]
	{
		0, 0,
		0, 1,
		1, 0,
		1, 1
	};

	unsigned int * GuiElement::INDICES = new unsigned int[6]
	{
		0, 1, 2,
		2, 1, 3
	};

	GuiElement::GuiElement()
	{
	}

	GuiElement::GuiElement(const GuiElement & other)
		: GuiElement(other.m_position, other.m_angle, other.m_scale)
	{
	}

	GuiElement::GuiElement(Math::Vec2 position, float angle, Math::Vec2 scale)
	{
		m_position = position;
		m_angle = angle;
		m_scale = scale;
	}

	GuiElement::~GuiElement()
	{
	}



	Math::Vec2 GuiElement::getPosition() const
	{
		return m_position;
	}

	float GuiElement::getAngle() const
	{
		return m_angle;
	}

	Math::Vec2 GuiElement::getScale() const
	{
		return m_scale;
	}



	GuiElement & GuiElement::operator=(const GuiElement & other)
	{
		m_position = other.m_position;
		m_angle = other.m_angle;
		m_scale = other.m_scale;

		return *this;
	}
}
