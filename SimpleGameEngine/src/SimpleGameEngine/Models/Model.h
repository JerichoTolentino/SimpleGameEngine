#pragma once
#include <GL/glew.h>
#include "BoundingBox.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{
	class Model
	{
	private:
		GLuint vaoID;
		int numIndices;
		Material* material;
		BoundingBox* baseBoundingBox;
	public:
		Model();
		~Model();

		Model(const Model &other);
		Model& operator=(const Model &other);
		bool operator<(const Model &other) const;

		Model(GLuint vao, int indices);
		Model(GLuint vao, int indices, Material* mat);

		Material* getMaterial() const;
		BoundingBox* getBaseBoundingBox() const;
		GLuint getVAO() const;
		int getNumIndices() const;

		void setMaterial(Material* m);
		void setBaseBoundingBox(BoundingBox* box);

		std::string toString() const;
	};
}
