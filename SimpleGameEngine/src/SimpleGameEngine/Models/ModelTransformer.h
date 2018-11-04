#pragma once
#include "SpaceModel.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class ModelTransformer
	{
	private:
		ModelTransformer();
	public:
		~ModelTransformer();

		static void translate(SpaceModel & spaceModel, Math::Vec3 translation);
		static void rotate(SpaceModel & spaceModel, Math::Vec3 rotation);
		static void scale(SpaceModel & spaceModel, Math::Vec3 scaling);
		static void transform(SpaceModel & spaceModel, Math::Vec3 translation, Math::Vec3 rotation, Math::Vec3 scaling);
	};
}
