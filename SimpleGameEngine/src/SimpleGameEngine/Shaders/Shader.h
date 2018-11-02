#pragma once
#include <GL/glew.h>

namespace SimpleGameEngine::Shaders
{
	class Shader
	{
	private:
		GLuint m_programId;
		GLuint m_vertexShaderId;
		GLuint m_fragmentShaderId;



	public:
		/// <summary>
		/// Initializes a new instance of a <see cref="Shader"/>.
		/// </summary>
		/// <param name="programId"></param>
		/// <param name="vertexShaderId"></param>
		/// <param name="fragmentShaderId"></param>
		Shader(GLuint programId, GLuint vertexShaderId, GLuint fragmentShaderId);

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~Shader();



		/// <summary>
		/// Gets the Shader Program ID.
		/// </summary>
		/// <returns></returns>
		GLuint getProgramId() const;

		/// <summary>
		/// Gets the Vertex Shader ID.
		/// </summary>
		/// <returns></returns>
		GLuint getVertexShaderId() const;

		/// <summary>
		/// Gets the Fragment Shader ID.
		/// </summary>
		/// <returns></returns>
		GLuint getFragmentShaderId() const;
	};
}
