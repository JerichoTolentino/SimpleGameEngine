#pragma once
#include "../Math/Mat4.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Projection
{
	class OrthoProjectionBox
	{
	private:
		static const float SHADOW_DISTANCE;
		static const float OFFSET;

	private:
		float m_minX;
		float m_minY;
		float m_minZ;

		float m_maxX;
		float m_maxY;
		float m_maxZ;

		float m_nearWidth;
		float m_nearHeight;
		float m_farWidth;
		float m_farHeight;

		Math::Mat4 m_lightViewMatrix;



	public:
		OrthoProjectionBox();
		OrthoProjectionBox(const OrthoProjectionBox & other);
		OrthoProjectionBox(float minX, float minY, float minZ, 
						   float maxX, float maxY, float maxZ, 
						   float nearWidth, float nearHeight,
						   float farWidth, float farHeight,
						   const Math::Mat4 & lightViewMatrix);
		virtual ~OrthoProjectionBox();



		void update(const Math::Vec3 & eyePosition, const Math::Vec3 & eyeRotation, float nearPlane);

		Math::Vec3 getWorldSpaceCenter() const;
		float getWidth() const;
		float getHeight() const;
		float getLength() const;



		OrthoProjectionBox & operator=(const OrthoProjectionBox & other);



		static OrthoProjectionBox GenerateOrthoProjectionBox(const Math::Mat4 & lightViewMatrix, float fov, float nearPlane, float aspectRatio);



	private:
		std::vector<Math::Vec4> calculateFrustumVertices(const Math::Mat4 & rotation, 
														 const Math::Vec3 & forward, 
														 const Math::Vec3 & centerNear, 
														 const Math::Vec3 & centerFar) const;
		Math::Vec4 calculateLightSpaceFrustumCorner(const Math::Vec3 & startPoint, const Math::Vec3 & direction, float width) const;
		Math::Mat4 calculateCameraRotationMatrix(float yaw, float pitch) const;
	};
}
