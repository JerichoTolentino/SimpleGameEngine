#pragma once
#include "../Math/Vec2.h"

namespace SimpleGameEngine::Models
{
	class GuiElement
	{
	public:
		static int VERTICES_COUNT;
		static int TEXTURE_UVS_COUNT;
		static int INDICES_COUNT;
		static float * VERTICES;
		static float * TEXTURE_UVS;
		static unsigned int * INDICES;



	private:
		Math::Vec2 m_position;
		float m_angle;
		Math::Vec2 m_scale;



	public:
		GuiElement();
		GuiElement(const GuiElement & other);
		GuiElement(Math::Vec2 position, float angle, Math::Vec2 scale);
		virtual ~GuiElement();



		Math::Vec2 getPosition() const;
		float getAngle() const;
		Math::Vec2 getScale() const;



		GuiElement & operator=(const GuiElement & other);
	};
}
