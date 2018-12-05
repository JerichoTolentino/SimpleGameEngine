#include "sgepch.h"
#include "GuiRenderElement.h"

namespace SimpleGameEngine::Models
{
	GuiRenderElement::GuiRenderElement()
	{
	}

	GuiRenderElement::GuiRenderElement(const GuiRenderElement & other)
		: GuiRenderElement(other.m_guiGeometry, other.m_vaoId, other.m_textureId, other.m_position, other.m_angle, other.m_scale)
	{
	}

	GuiRenderElement::GuiRenderElement(std::shared_ptr<GuiGeometry> guiGeometry, unsigned int vaoId, unsigned int textureId, Math::Vec2 position, float angle, Math::Vec2 scale)
	{
		m_guiGeometry = guiGeometry;
		m_vaoId = vaoId;
		m_textureId = textureId;
		m_position = position;
		m_angle = angle;
		m_scale = scale;
	}

	GuiRenderElement::~GuiRenderElement()
	{
	}



	std::shared_ptr<GuiGeometry> GuiRenderElement::getGuiGeometry() const
	{
		return m_guiGeometry;
	}
	
	unsigned int GuiRenderElement::getVaoId() const
	{
		return m_vaoId;
	}
	
	unsigned int GuiRenderElement::getTextureId() const
	{
		return m_textureId;
	}

	Math::Vec2 GuiRenderElement::getPosition() const
	{
		return m_position;
	}

	float GuiRenderElement::getAngle() const
	{
		return m_angle;
	}

	Math::Vec2 GuiRenderElement::getScale() const
	{
		return m_scale;
	}
	
	
	
	GuiRenderElement & GuiRenderElement::operator=(const GuiRenderElement & other)
	{
		m_guiGeometry = other.m_guiGeometry;
		m_vaoId = other.m_vaoId;
		m_textureId = other.m_textureId;
		m_position = other.m_position;
		m_angle = other.m_angle;
		m_scale = other.m_scale;

		return *this;
	}
}
