#pragma once
#include "GuiElement.h"

namespace SimpleGameEngine::Models
{
	class GuiRenderElement
	{
	private:
		std::shared_ptr<GuiElement> m_guiElement;
		unsigned int m_vaoId;
		unsigned int m_textureId;


	public:
		GuiRenderElement();
		GuiRenderElement(const GuiRenderElement & other);
		GuiRenderElement(std::shared_ptr<GuiElement> guiElement, unsigned int vaoId, unsigned int textureId);
		virtual ~GuiRenderElement();



		std::shared_ptr<GuiElement> getGuiElement() const;
		unsigned int getVaoId() const;
		unsigned int getTextureId() const;



		GuiRenderElement & operator=(const GuiRenderElement & other);
	};
}
