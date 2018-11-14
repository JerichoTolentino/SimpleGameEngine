#pragma once
#include <vector>
#include <memory>
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class GeometryModel
	{
	private:
		std::shared_ptr<std::vector<Math::Vec3>> m_vertices;
		std::shared_ptr<std::vector<Math::Vec2>> m_textureUvs;
		std::shared_ptr<std::vector<Math::Vec3>> m_normals;
		std::shared_ptr<std::vector<unsigned int>> m_indices;



	public:
		GeometryModel();
		GeometryModel(const GeometryModel &other);
		GeometryModel(
			const std::shared_ptr<std::vector<Math::Vec3>> vertices,
			const std::shared_ptr<std::vector<Math::Vec2>> textureUvs, 
			const std::shared_ptr<std::vector<Math::Vec3>> normals, 
			const std::shared_ptr<std::vector<unsigned int>> indices);
		virtual ~GeometryModel();



		std::shared_ptr<std::vector<Math::Vec3>> getVertices() const;
		std::shared_ptr<std::vector<Math::Vec2>> getTextureUvs() const;
		std::shared_ptr<std::vector<Math::Vec3>> getNormals() const;
		std::shared_ptr<std::vector<unsigned int>> getIndices() const;



		/// <summary>
		/// Copy assignment override.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		GeometryModel & operator=(const GeometryModel &other);
	};
}
