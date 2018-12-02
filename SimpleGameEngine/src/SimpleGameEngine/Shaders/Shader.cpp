#include "sgepch.h"
#include "Shader.h"

namespace SimpleGameEngine::Shaders
{
	Shader::Shader()
	{
	}

	Shader::Shader(GLuint programId, GLuint vertexShaderId, GLuint fragmentShaderId, bool isLoaded, bool isRunning)
	{
		m_programId = programId;
		m_vertexShaderId = vertexShaderId;
		m_fragmentShaderId = fragmentShaderId;
		m_loaded = isLoaded;
		m_running = isRunning;
	}

	Shader::Shader(const Shader & other)
		: Shader(other.m_programId, other.m_vertexShaderId, other.m_fragmentShaderId, other.m_loaded, other.m_running)
	{
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
	bool Shader::isLoaded() const
	{
		return m_loaded;
	}

	void Shader::setLoaded(bool loaded)
	{
		m_loaded = loaded;
	}



	Shader & Shader::operator=(const Shader & other)
	{
		m_programId = other.m_programId;
		m_vertexShaderId = other.m_vertexShaderId;
		m_fragmentShaderId = other.m_fragmentShaderId;
		m_loaded = other.m_loaded;
		m_running = other.m_running;
		
		return *this;
	}
}
