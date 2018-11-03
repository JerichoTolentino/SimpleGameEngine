#include "Model.h"

namespace SimpleGameEngine::Models
{
	Model::Model()
	{
		vaoID = -1;
		numIndices = 0;
		material = new Material;
		baseBoundingBox = new BoundingBox;
	}


	Model::~Model()
	{
		delete baseBoundingBox;
	}

	Model::Model(const Model &other)
	{
		vaoID = other.vaoID;
		numIndices = other.numIndices;
		material = new Material(*(other.material));
		baseBoundingBox = new BoundingBox(*(other.getBaseBoundingBox()));
	}

	Model& Model::operator=(const Model &other)
	{
		vaoID = other.vaoID;
		numIndices = other.numIndices;
		*material = *(other.material);
		*baseBoundingBox = *(other.getBaseBoundingBox());
		return *this;
	}

	bool Model::operator<(const Model & other) const
	{
		bool less = false;

		if (other.getVAO() < vaoID)
			less = true;

		return less;
	}

	Model::Model(GLuint vao, int indices)
	{
		vaoID = vao;
		numIndices = indices;
		material = new Material;
	}

	Model::Model(GLuint vao, int indices, Material* mat)
	{
		vaoID = vao;
		numIndices = indices;
		material = mat;
	}

	Material* Model::getMaterial() const
	{
		return material;
	}


	BoundingBox * Model::getBaseBoundingBox() const
	{
		return baseBoundingBox;
	}


	GLuint Model::getVAO() const
	{
		return vaoID;
	}

	int Model::getNumIndices() const
	{
		return numIndices;
	}

	void Model::setMaterial(Material* m)
	{
		material = m;
	}


	void Model::setBaseBoundingBox(BoundingBox * box)
	{
		this->baseBoundingBox = box;
	}


	std::string Model::toString() const
	{
		return ("--Model--\nVaoID: " + std::to_string(vaoID) + "\nnumIndices: " + std::to_string(numIndices) + "\n" + material->toString() + "\n--End Model--");
	}
}
