#include "sgepch.h"
#include "BoundingBox.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	BoundingBox::BoundingBox()
	{
	}

	BoundingBox::BoundingBox(const std::shared_ptr<SpaceModel> spaceModel, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	{
		m_spaceModel = spaceModel;
		m_minX = minX;
		m_minY = minY;
		m_minZ = minZ;
		m_maxX = maxX;
		m_maxY = maxY;
		m_maxZ = maxZ;
	}
	
	BoundingBox::BoundingBox(const BoundingBox & other)
		: BoundingBox(other.m_spaceModel, other.m_minX, other.m_minY, other.m_minZ, other.m_maxX, other.m_maxY, other.m_maxZ)
	{
	}
	
	BoundingBox::~BoundingBox()
	{
	}
	
	
	
	std::shared_ptr<SpaceModel> BoundingBox::getSpaceModel() const
	{
		return m_spaceModel;
	}

	float BoundingBox::getMinX() const
	{
		return m_minX;
	}
	
	float BoundingBox::getMinY() const
	{
		return m_minY;
	}
	
	float BoundingBox::getMinZ() const
	{
		return m_minZ;
	}
	
	float BoundingBox::getMaxX() const
	{
		return m_maxX;
	}
	
	float BoundingBox::getMaxY() const
	{
		return m_maxY;
	}
	
	float BoundingBox::getMaxZ() const
	{
		return m_maxZ;
	}
	


	BoundingBox & BoundingBox::operator=(const BoundingBox & other)
	{
		m_minX = other.m_minX;
		m_minY = other.m_minY;
		m_minZ = other.m_minZ;
		m_maxX = other.m_maxX;
		m_maxY = other.m_maxY;
		m_maxZ = other.m_maxZ;

		return *this;
	}
}
