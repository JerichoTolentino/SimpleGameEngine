#pragma once
#include <vector>
#include <memory>
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class SkyboxModel
	{
	private:
		std::shared_ptr<std::vector<Math::Vec3>> m_vertices;
		std::shared_ptr<std::vector<Math::Vec3>> m_textureUvs;
		std::shared_ptr<std::vector<unsigned int>> m_indices;



	public:
		SkyboxModel();
		SkyboxModel(const SkyboxModel & other);
		SkyboxModel(
			const std::shared_ptr<std::vector<Math::Vec3>> vertices, 
			const std::shared_ptr<std::vector<Math::Vec3>> textureUvs, 
			const std::shared_ptr<std::vector<unsigned int>> indices);
		virtual ~SkyboxModel();


		std::shared_ptr<std::vector<Math::Vec3>> getVertices() const;
		std::shared_ptr<std::vector<Math::Vec3>> getTextureUvs() const;
		std::shared_ptr<std::vector<unsigned int>> getIndices() const;



		SkyboxModel & operator=(const SkyboxModel & other);



		/// <summary>
		/// Creates a <see cref="SkyboxModel"/> with
		/// the specified size in model space.
		/// </summary>
		/// <param name="size">The size of the skybox to create in model space.</param>
		/// <returns></returns>
		static SkyboxModel CreateSkyboxModel(float size);
	};
}
