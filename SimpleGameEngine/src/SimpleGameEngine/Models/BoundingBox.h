#pragma once
#include <GL/glew.h>
#include "GeometryModel.h"
#include "SpaceModel.h"

namespace SimpleGameEngine::Models
{
	class BoundingBox
	{
	private:
		SpaceModel m_spaceModel;
		float m_minX;
		float m_minY;
		float m_minZ;
		float m_maxX;
		float m_maxY;
		float m_maxZ;



	public:
		BoundingBox();
		BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		BoundingBox(const BoundingBox & other);
		~BoundingBox();



		SpaceModel getSpaceModel() const;
		float getMinX() const;
		float getMinY() const;
		float getMinZ() const;
		float getMaxX() const;
		float getMaxY() const;
		float getMaxZ() const;



		BoundingBox& operator=(const BoundingBox &other);
	};
}
