#pragma once
#include "../Shaders/Shader.h"
#include "../Models/GuiRenderElement.h"

namespace SimpleGameEngine::Renderers
{
	class GuiRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		GuiRenderer();
		GuiRenderer(const GuiRenderer & other);
		GuiRenderer(const std::shared_ptr<Shaders::Shader> shader);
		~GuiRenderer();



		void loadGuiRenderElement(const Models::GuiRenderElement & guiRenderElement) const;
		void loadGuiElement(const Models::GuiElement & guiElement) const;
		void render(const Models::GuiRenderElement & guiRenderElement) const;
		void unloadGuiRenderElement() const;



		GuiRenderer & operator=(const GuiRenderer & other);
	};
}
