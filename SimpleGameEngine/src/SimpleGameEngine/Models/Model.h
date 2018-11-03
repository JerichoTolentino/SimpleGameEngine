#pragma once
#include <GL/glew.h>
#include <vector>

namespace SimpleGameEngine::Models
{
	class Model
	{
	private:
		GLuint m_vaoId;
		std::vector<int> m_indices;



	public:
		Model();
		Model(const Model &other);
		Model(GLuint vaoId, std::vector<int> indices);
		virtual ~Model();



		GLuint getVaoId() const;
		std::vector<int> getIndices() const;



		/// <summary>
		/// Copy assignment override.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Model& operator=(const Model &other);
	};
}
