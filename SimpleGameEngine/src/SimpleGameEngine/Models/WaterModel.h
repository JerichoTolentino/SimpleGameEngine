#pragma once

namespace SimpleGameEngine::Models
{
	class WaterModel
	{
	private:
		std::shared_ptr<std::vector<float>> m_vertices;
		std::shared_ptr<std::vector<unsigned int>> m_indices;


	public:
		WaterModel();
		WaterModel(const WaterModel & other);
		WaterModel(
			const std::shared_ptr<std::vector<float>> vertices,
			const std::shared_ptr<std::vector<unsigned int>> indices);
		virtual ~WaterModel();



		std::shared_ptr<std::vector<float>> getVertices() const;
		std::shared_ptr<std::vector<unsigned int>> getIndices() const;



		WaterModel & operator=(const WaterModel & other);



		static WaterModel GenerateWaterModel();
	};
}
