#include "ModelTransformer.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Logic
{
	void ModelTransformer::translate(SpaceModel & spaceModel, const Math::Vec3 & translation)
	{
		Vec3 pos = spaceModel.getPosition();
		pos += translation;

		spaceModel.setPosition(pos);
	}

	void ModelTransformer::rotate(SpaceModel & spaceModel, const Math::Vec3 & rotation)
	{
		Vec3 rot = spaceModel.getRotation();
		rot += rotation;

		spaceModel.setRotation(rot);
	}

	void ModelTransformer::scale(SpaceModel & spaceModel, const Math::Vec3 & scaling)
	{
		Vec3 scale = spaceModel.getScale();
		scale *= scaling;

		spaceModel.setScale(scale);
	}

	void ModelTransformer::transform(SpaceModel & spaceModel, const Math::Vec3 & translation, const Math::Vec3 & rotation, const Math::Vec3 & scaling)
	{
		scale(spaceModel, scaling);
		rotate(spaceModel, rotation);
		translate(spaceModel, translation);
	}
}
