#pragma once
#include "../Models/SpaceModel.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Logic
{
	class ModelTransformer
	{
	public:
		static void translate(Models::SpaceModel & spaceModel, const Math::Vec3 & translation);
		static void rotate(Models::SpaceModel & spaceModel, const Math::Vec3 & rotation);
		static void scale(Models::SpaceModel & spaceModel, const Math::Vec3 & scaling);
		static void transform(Models::SpaceModel & spaceModel, const Math::Vec3 & translation, const Math::Vec3 & rotation, const Math::Vec3 & scaling);
	};
}
