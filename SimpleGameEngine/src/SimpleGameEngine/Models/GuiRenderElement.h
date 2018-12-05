#pragma once
#include "GuiGeometry.h"
#include "../Math/Vec2.h"

namespace SimpleGameEngine::Models
{
	class GuiRenderElement
	{
	private:
		std::shared_ptr<GuiGeometry> m_guiGeometry;
		unsigned int m_vaoId;
		unsigned int m_textureId;
		Math::Vec2 m_position;
		float m_angle;
		Math::Vec2 m_scale;


	public:
		GuiRenderElement();
		GuiRenderElement(const GuiRenderElement & other);
		GuiRenderElement(std::shared_ptr<GuiGeometry> guiGeometry, unsigned int vaoId, unsigned int textureId, Math::Vec2 position, float angle, Math::Vec2 scale);
		virtual ~GuiRenderElement();



		std::shared_ptr<GuiGeometry> getGuiGeometry() const;
		unsigned int getVaoId() const;
		unsigned int getTextureId() const;
		Math::Vec2 getPosition() const;
		float getAngle() const;
		Math::Vec2 getScale() const;



		GuiRenderElement & operator=(const GuiRenderElement & other);
	};
}
