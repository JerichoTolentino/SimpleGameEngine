#include "Shader.h"

namespace SimpleGameEngine::Shaders
{
	Shader::Shader(GLuint programId, GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		m_programId = programId;
		m_vertexShaderId = vertexShaderId;
		m_fragmentShaderId = fragmentShaderId;
	}

	Shader::~Shader()
	{
	}



	GLuint Shader::getProgramId() const
	{
		return m_programId;
	}

	GLuint Shader::getVertexShaderId() const
	{
		return m_vertexShaderId;
	}

	GLuint Shader::getFragmentShaderId() const
	{
		return m_fragmentShaderId;
	}
	bool Shader::isRunning() const
	{
		return m_running;
	}
	void Shader::setRunning(bool running)
	{
		m_running = running;
	}
}
