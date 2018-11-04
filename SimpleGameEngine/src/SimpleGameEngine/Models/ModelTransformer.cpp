#include "ModelTransformer.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	ModelTransformer::ModelTransformer()
	{
	}

	ModelTransformer::~ModelTransformer()
	{
	}



	void ModelTransformer::translate(SpaceModel & spaceModel, Math::Vec3 translation)
	{
		Vec3 pos = spaceModel.getPosition();
		pos += translation;

		spaceModel.setPosition(pos);
	}

	void ModelTransformer::rotate(SpaceModel & spaceModel, Math::Vec3 rotation)
	{
		Vec3 rot = spaceModel.getRotation();
		rot += rotation;

		spaceModel.setRotation(rot);
	}

	void ModelTransformer::scale(SpaceModel & spaceModel, Math::Vec3 scaling)
	{
		Vec3 scale = spaceModel.getScale();
		scale *= scaling;

		spaceModel.setScale(scale);
	}

	void ModelTransformer::transform(SpaceModel & spaceModel, Math::Vec3 translation, Math::Vec3 rotation, Math::Vec3 scaling)
	{
		scale(spaceModel, scaling);
		rotate(spaceModel, rotation);
		translate(spaceModel, translation);
	}
}
