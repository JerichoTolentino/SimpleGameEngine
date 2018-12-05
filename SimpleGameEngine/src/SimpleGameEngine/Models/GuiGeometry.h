#pragma once

namespace SimpleGameEngine::Models
{
	class GuiGeometry
	{
	private:
		std::shared_ptr<std::vector<float>> m_vertices;
		std::shared_ptr<std::vector<float>> m_textureUvs;
		std::shared_ptr<std::vector<unsigned int>> m_indices;



	public:
		GuiGeometry();
		GuiGeometry(const GuiGeometry & other);
		GuiGeometry(
			const std::shared_ptr<std::vector<float>> vertices,
			const std::shared_ptr<std::vector<float>> textureUvs,
			const std::shared_ptr<std::vector<unsigned int>> indices);
		virtual ~GuiGeometry();



		std::shared_ptr<std::vector<float>> getVertices() const;
		std::shared_ptr<std::vector<float>> getTextureUvs() const;
		std::shared_ptr<std::vector<unsigned int>> getIndices() const;



		GuiGeometry & operator=(const GuiGeometry & other);



		static GuiGeometry GenerateQuad();
	};
}
