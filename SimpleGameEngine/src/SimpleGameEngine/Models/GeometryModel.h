#pragma once
#include <vector>
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class GeometryModel
	{
	private:
		std::vector<Math::Vec3> m_vertices;
		std::vector<Math::Vec2> m_textureUvs;
		std::vector<Math::Vec3> m_normals;
		std::vector<unsigned int> m_indices;



	public:
		GeometryModel();
		GeometryModel(const GeometryModel &other);
		GeometryModel(std::vector<Math::Vec3> vertices, std::vector<Math::Vec2> textureUvs, std::vector<Math::Vec3> normals, std::vector<unsigned int> indices);
		virtual ~GeometryModel();



		std::vector<Math::Vec3> getVertices() const;
		std::vector<Math::Vec2> getTextureUvs() const;
		std::vector<Math::Vec3> getNormals() const;
		std::vector<unsigned int> getIndices() const;



		/// <summary>
		/// Copy assignment override.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		GeometryModel& operator=(const GeometryModel &other);
	};
}