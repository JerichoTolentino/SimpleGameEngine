#include "BoundingBox.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	BoundingBox::BoundingBox()
	{
	}

	BoundingBox::BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	{
	}
	
	BoundingBox::BoundingBox(const BoundingBox & other)
	{
	}
	
	BoundingBox::~BoundingBox()
	{
	}
	
	
	
	float BoundingBox::getMinX() const
	{
		return 0.0f;
	}
	
	float BoundingBox::getMinY() const
	{
		return 0.0f;
	}
	
	float BoundingBox::getMinZ() const
	{
		return 0.0f;
	}
	
	float BoundingBox::getMaxX() const
	{
		return 0.0f;
	}
	
	float BoundingBox::getMaxY() const
	{
		return 0.0f;
	}
	
	float BoundingBox::getMaxZ() const
	{
		return 0.0f;
	}
	
	GLfloat * BoundingBox::generateVertices() const
	{
		return nullptr;
	}
	
	GLuint * BoundingBox::generateIndices() const
	{
		return nullptr;
	}
	


	BoundingBox & BoundingBox::operator=(const BoundingBox & other)
	{
		// TODO: insert return statement here
	}



	GeometryModel BoundingBox::generateGeometryFromPlanes(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	{
		std::vector<Vec3> vertices;
		std::vector<Vec2>

	}
}
