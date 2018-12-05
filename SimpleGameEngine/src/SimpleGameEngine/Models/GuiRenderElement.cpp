#include "sgepch.h"
#include "GuiRenderElement.h"

namespace SimpleGameEngine::Models
{
	GuiRenderElement::GuiRenderElement()
	{
	}

	GuiRenderElement::GuiRenderElement(const GuiRenderElement & other)
		: GuiRenderElement(other.m_guiElement, other.m_vaoId, other.m_textureId)
	{
	}

	GuiRenderElement::GuiRenderElement(std::shared_ptr<GuiElement> guiElement, unsigned int vaoId, unsigned int textureId)
	{
		m_guiElement = guiElement;
		m_vaoId = vaoId;
		m_textureId = textureId;
	}

	GuiRenderElement::~GuiRenderElement()
	{
	}



	std::shared_ptr<GuiElement> GuiRenderElement::getGuiElement() const
	{
		return m_guiElement;
	}
	
	unsigned int GuiRenderElement::getVaoId() const
	{
		return m_vaoId;
	}
	
	unsigned int GuiRenderElement::getTextureId() const
	{
		return m_textureId;
	}
	
	
	
	GuiRenderElement & GuiRenderElement::operator=(const GuiRenderElement & other)
	{
		m_guiElement = other.m_guiElement;
		m_vaoId = other.m_vaoId;
		m_textureId = other.m_textureId;

		return *this;
	}
}
