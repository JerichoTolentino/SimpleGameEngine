#include "Model.h"

namespace SimpleGameEngine::Models
{
	Model::Model()
	{
	}

	Model::Model(const Model & other)
		: Model(other.m_vaoId, other.m_indices)
	{
	}
	
	Model::Model(GLuint vaoId, std::vector<int> indices)
	{
		m_vaoId = vaoId;
		m_indices = indices;
	}
	
	Model::~Model()
	{
	}



	GLuint Model::getVaoId() const
	{
		return m_vaoId;
	}
	
	std::vector<int> Model::getIndices() const
	{
		return m_indices;
	}



	Model & Model::operator=(const Model & other)
	{
		m_vaoId = other.m_vaoId;
		m_indices = other.m_indices;
		return *this;
	}
}
