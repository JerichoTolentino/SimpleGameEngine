#pragma once
#include <memory>
#include <GL/glew.h>
#include "GeometryModel.h"
#include "SpaceModel.h"

namespace SimpleGameEngine::Models
{
	class BoundingBox
	{
	private:
		std::shared_ptr<SpaceModel> m_spaceModel;
		float m_minX;
		float m_minY;
		float m_minZ;
		float m_maxX;
		float m_maxY;
		float m_maxZ;



	public:
		BoundingBox();
		BoundingBox(const std::shared_ptr<SpaceModel> spaceModel, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		BoundingBox(const BoundingBox & other);
		~BoundingBox();



		std::shared_ptr<SpaceModel> getSpaceModel() const;
		float getMinX() const;
		float getMinY() const;
		float getMinZ() const;
		float getMaxX() const;
		float getMaxY() const;
		float getMaxZ() const;



		BoundingBox& operator=(const BoundingBox &other);
	};
}
