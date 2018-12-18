#include "sgepch.h"
#include "OrthoProjectionBox.h"

#include "../Math/MathUtils.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Projection
{
	const float OrthoProjectionBox::SHADOW_DISTANCE = 100;
	const float OrthoProjectionBox::OFFSET = 10;

	OrthoProjectionBox::OrthoProjectionBox()
	{
	}

	OrthoProjectionBox::OrthoProjectionBox(const OrthoProjectionBox & other)
		: OrthoProjectionBox(other.m_minX, other.m_minY, other.m_minZ,
							 other.m_maxX, other.m_maxY, other.m_maxZ,
							 other.m_nearWidth, other.m_nearHeight,
							 other.m_farWidth, other.m_farHeight,
							 other.m_viewMatrix)
	{
	}

	OrthoProjectionBox::OrthoProjectionBox(float minX, float minY, float minZ, 
										   float maxX, float maxY, float maxZ, 
										   float nearWidth, float nearHeight, 
										   float farWidth, float farHeight, 
										   const Math::Mat4 & viewMatrix)
		:
		m_minX(minX), m_minY(minY), m_minZ(minZ),
		m_maxX(maxX), m_maxY(maxY), m_maxZ(maxZ),
		m_nearWidth(nearWidth), m_nearHeight(nearHeight),
		m_farWidth(farWidth), m_farHeight(farHeight),
		m_viewMatrix(viewMatrix)
	{
	}

	OrthoProjectionBox::~OrthoProjectionBox()
	{
	}



	void OrthoProjectionBox::update(const Math::Vec3 & eyePosition, const Math::Vec3 & eyeRotation, float nearPlane)
	{
		Mat4 rotation = calculateCameraRotationMatrix(eyeRotation.y, eyeRotation.x);
		Vec3 forward = (rotation * Vec4(0, 0, -1, 1)).xyz();

		Vec3 toFar = forward * SHADOW_DISTANCE;
		Vec3 toNear = forward * nearPlane;
		Vec3 centerFar = toFar + eyePosition;
		Vec3 centerNear = toNear + eyePosition;

		std::vector<Vec4> points = calculateFrustumVertices(rotation, forward, centerNear, centerFar);

		// Initialize bounds to first point
		Vec4 firstPoint = points.at(0);
		m_minX = firstPoint.x;
		m_maxX = firstPoint.x;
		m_minY = firstPoint.y;
		m_maxY = firstPoint.y;
		m_minZ = firstPoint.z;
		m_maxZ = firstPoint.z;

		// Update min and max points
		int n = points.size();
		for (int i = 1; i < n; i++)
		{
			Vec4 point = points.at(i);

			if (point.x > m_maxX)
				m_maxX = point.x;

			if (point.x < m_minX)
				m_minX = point.x;

			if (point.y > m_maxY)
				m_maxY = point.y;

			if (point.y < m_minY)
				m_minY = point.y;

			if (point.z > m_maxZ)
				m_maxZ = point.z;

			if (point.z < m_minZ)
				m_minZ = point.z;
		}

		m_maxZ += OFFSET;
	}

	Math::Vec3 OrthoProjectionBox::getWorldSpaceCenter() const
	{
		float x = (m_minX + m_maxX) / 2.0f;
		float y = (m_minY + m_maxY) / 2.0f;
		float z = (m_minZ + m_maxZ) / 2.0f;
		Vec4 center(x, y, z, 1);

		Mat4 lightViewMatrix(m_viewMatrix);
		lightViewMatrix.inverse();

		return (lightViewMatrix * center).xyz();

	}

	float OrthoProjectionBox::getWidth() const
	{
		return m_maxX - m_minX;
	}

	float OrthoProjectionBox::getHeight() const
	{
		return m_maxY - m_minY;
	}

	float OrthoProjectionBox::getLength() const
	{
		return m_maxZ - m_minZ;
	}



	OrthoProjectionBox & OrthoProjectionBox::operator=(const OrthoProjectionBox & other)
	{
		m_farHeight = other.m_farHeight;
		m_farWidth = other.m_farWidth;
		m_maxX = other.m_maxX;
		m_maxY = other.m_maxY;
		m_maxZ = other.m_maxZ;
		m_minX = other.m_minX;
		m_minY = other.m_minY;
		m_minZ = other.m_minZ;
		m_nearHeight = other.m_nearHeight;
		m_nearWidth = other.m_nearWidth;
		m_viewMatrix = other.m_viewMatrix;

		return *this;
	}



	OrthoProjectionBox OrthoProjectionBox::GenerateOrthoProjectionBox(const Math::Mat4 & viewMatrix, float fov, float nearPlane, float aspectRatio)
	{
		float farWidth = SHADOW_DISTANCE * std::tan(MathUtils::toRadians(fov));
		float nearWidth = nearPlane * std::tan(MathUtils::toRadians(fov));
		float farHeight = farWidth / aspectRatio;
		float nearHeight = nearWidth / aspectRatio;

		return OrthoProjectionBox(0, 0, 0, 0, 0, 0, nearWidth, nearHeight, farWidth, farHeight, viewMatrix);
	}



	std::vector<Math::Vec4> OrthoProjectionBox::calculateFrustumVertices(const Math::Mat4 & rotation,
																		 const Math::Vec3 & forward, 
																		 const Math::Vec3 & centerNear, 
																		 const Math::Vec3 & centerFar) const
	{
		Vec3 up = (rotation * Vec4(0, 1, 0, 1)).xyz();
		Vec3 right = Vec3::cross(forward, up);
		Vec3 down = Vec3(-up.x, -up.y, -up.z);
		Vec3 left = Vec3(-right.x, -right.y, -right.z);

		Vec3 farTop = centerFar + up.multiply(m_farHeight);
		Vec3 farBot = centerFar + down.multiply(m_farHeight);
		Vec3 nearTop = centerNear + up.multiply(m_nearHeight);
		Vec3 nearBot = centerNear + down.multiply(m_nearHeight);

		std::vector<Vec4> frustumVertices;
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(farTop, right, m_farWidth));
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(farTop, left, m_farWidth));
		
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(farBot, right, m_farWidth));
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(farBot, left, m_farWidth));
		
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(nearTop, right, m_nearWidth));
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(nearTop, left, m_nearWidth));
		
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(nearBot, right, m_nearWidth));
		frustumVertices.push_back(calculateLightSpaceFrustumCorner(nearBot, left, m_nearWidth));

		return frustumVertices;
	}

	Math::Vec4 OrthoProjectionBox::calculateLightSpaceFrustumCorner(const Math::Vec3 & startPoint, const Math::Vec3 & direction, float width) const
	{
		Vec3 point = startPoint + (direction * width);
		return m_viewMatrix * Vec4(point.x, point.y, point.z, 1);
	}

	Math::Mat4 OrthoProjectionBox::calculateCameraRotationMatrix(float yaw, float pitch) const
	{
		Mat4 rotation;

		rotation.transform(Vec3(0, 0, 0), Vec3(0, MathUtils::toRadians(-yaw), 0), Vec3(1, 1, 1));
		rotation.transform(Vec3(0, 0, 0), Vec3(MathUtils::toRadians(-pitch), 0, 0), Vec3(1, 1, 1));

		return rotation;
	}
}
