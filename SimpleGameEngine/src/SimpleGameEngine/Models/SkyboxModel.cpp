#include "SkyboxModel.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	SkyboxModel::SkyboxModel()
	{
	}

	SkyboxModel::SkyboxModel(const SkyboxModel & other)
		: SkyboxModel(other.m_vertices, other.m_textureUvs, other.m_indices)
	{
	}

	SkyboxModel::SkyboxModel(std::vector<Math::Vec3> vertices, std::vector<Math::Vec3> textureUvs, std::vector<unsigned int> indices)
	{
		m_vertices = vertices;
		m_textureUvs = textureUvs;
		m_indices = indices;
	}


	SkyboxModel::~SkyboxModel()
	{
	}



	std::vector<Math::Vec3> SkyboxModel::getVertices() const
	{
		return m_vertices;
	}

	std::vector<Math::Vec3> SkyboxModel::getTextureUvs() const
	{
		return m_textureUvs;
	}

	std::vector<unsigned int> SkyboxModel::getIndices() const
	{
		return m_indices;
	}



	SkyboxModel & SkyboxModel::operator=(const SkyboxModel & other)
	{
		m_vertices = other.m_vertices;
		m_textureUvs = other.m_textureUvs;
		m_indices = other.m_indices;

		return *this;
	}



	SkyboxModel SkyboxModel::CreateSkyboxModel(float size)
	{
		int numVertices = 3 * 4 * 6;

		Vec3 * vertices = new Vec3[numVertices]
		{
			//neg-z square
			Vec3(-size, size, -size),		//0
			Vec3(-size, -size, -size),		//1
			Vec3(size, -size, -size),		//2
			Vec3(size, size, -size),		//3
			// 0, 1, 2, 2, 3, 0,

			//pos-x square
			Vec3(size, size, -size),		//4
			Vec3(size, -size, -size),		//5
			Vec3(size, -size, size),		//6
			Vec3(size, size, size),			//7
			// 4, 5, 6, 6, 7, 4,

			//pos-z square
			Vec3(size, size, size),			//8
			Vec3(size, -size, size),		//9
			Vec3(-size, -size, size),		//10
			Vec3(-size, size, size),		//11
			// 8, 9, 10, 10, 11, 8,

			//neg-x square
			Vec3(-size, size, size),		//12
			Vec3(-size, -size, size),		//13
			Vec3(-size, -size, -size),		//14
			Vec3(-size, size, -size),		//15
			// 12, 13, 14, 14, 15, 12,

			//pos-y square
			Vec3(-size, size, size),		//16
			Vec3(-size, size, -size),		//17
			Vec3(size, size, -size),		//18
			Vec3(size, size, size),			//19
			// 16, 17, 18, 18, 19, 16,

			//neg-y square
			Vec3(-size, -size, -size),		//20
			Vec3(-size, -size, size),		//21
			Vec3(size, -size, size),		//22
			Vec3(size, -size, -size),		//23
			// 20, 21, 22, 22, 23, 20

		};

		Vec3 * textures = new Vec3[numVertices]
		{
			//neg-z square
			Vec3(-1, 1, -1),		//0
			Vec3(-1, -1, -1),		//1
			Vec3(1, -1, -1),		//2
			Vec3(1, 1, -1),			//3
			// 0, 1, 2, 2, 3, 0,

			//pos-x square
			Vec3(1, 1, -1),			//4
			Vec3(1, -1, -1),		//5
			Vec3(1, -1, 1),			//6
			Vec3(1, 1, 1),			//7
			// 4, 5, 6, 6, 7, 4,

			//pos-z square
			Vec3(1, 1, 1),			//8
			Vec3(1, -1, 1),			//9
			Vec3(-1, -1, 1),		//10
			Vec3(-1, 1, 1),			//11
			// 8, 9, 10, 10, 11, 8,

			//neg-x square
			Vec3(-1, 1, 1),			//12
			Vec3(-1, -1, 1),		//13
			Vec3(-1, -1, -1),		//14
			Vec3(-1, 1, -1),		//15
			// 12, 13, 14, 14, 15, 12,

			//pos-y square
			Vec3(-1, 1, 1),			//16
			Vec3(-1, 1, -1),		//17
			Vec3(1, 1, -1),			//18
			Vec3(1, 1, 1),			//19
			// 16, 17, 18, 18, 19, 16,

			//neg-y square
			Vec3(-1, -1, -1),		//20
			Vec3(-1, -1, 1),		//21
			Vec3(1, -1, 1),			//22
			Vec3(1, -1, -1),		//23
			// 20, 21, 22, 22, 23, 20
		};


		int numIndices = 6 * 6;

		unsigned int * indices = new unsigned int[numIndices]
		{
			//neg-z face
			0, 1, 2, 2, 3, 0,

			//pos-x face
			4, 5, 6, 6, 7, 4,

			//pos-z face
			8, 9, 10, 10, 11, 8,

			//neg-x face
			12, 13, 14, 14, 15, 12,

			//pos-y face
			16, 17, 18, 18, 19, 16,

			//neg-y face
			20, 21, 22, 22, 23, 20
		};

		// Assign arrays to vectors
		std::vector<Vec3> verts;
		std::vector<Vec3> texts;
		std::vector<unsigned int> inds;

		verts.assign(vertices, vertices + numVertices);
		texts.assign(textures, textures + numVertices);
		inds.assign(indices, indices + numIndices);

		return SkyboxModel(verts, texts, inds);
	}
}
