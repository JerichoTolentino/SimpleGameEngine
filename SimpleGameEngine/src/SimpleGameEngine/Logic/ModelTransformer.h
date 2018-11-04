#pragma once
#include "../Models/SpaceModel.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Logic
{
	class ModelTransformer
	{
		static void translate(Models::SpaceModel & spaceModel, Math::Vec3 translation);
		static void rotate(Models::SpaceModel & spaceModel, Math::Vec3 rotation);
		static void scale(Models::SpaceModel & spaceModel, Math::Vec3 scaling);
		static void transform(Models::SpaceModel & spaceModel, Math::Vec3 translation, Math::Vec3 rotation, Math::Vec3 scaling);
	};
}
