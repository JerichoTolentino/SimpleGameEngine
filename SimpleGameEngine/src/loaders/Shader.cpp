#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}


Shader::Shader(const char *vertex, const char *fragment)
{
	std::string vertexShader = fileToString(vertex);
	std::string fragmentShader = fileToString(fragment);
	const GLchar *vShader = vertexShader.c_str();
	const GLchar *fShader = fragmentShader.c_str();

	programID = glCreateProgram();
	
	vShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderID, 1, &vShader, NULL);
	fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderID, 1, &fShader, NULL);

	GLint vCompileStatus = -1;

	glCompileShader(vShaderID);
	glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &vCompileStatus);
	if (vCompileStatus == GL_FALSE)
	{
		GLint logSize = 0;
		glGetShaderiv(vShaderID, GL_INFO_LOG_LENGTH, &logSize);
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(vShaderID, logSize, NULL, log);
		MessageHandler::printMessage("ERROR: Cannot compile vertex shader!\n" + std::string(log) + "\n");
	}

	GLint fCompileStatus = -1;

	glCompileShader(fShaderID);
	glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &fCompileStatus);
	if (fCompileStatus == GL_FALSE)
	{
		GLint logSize = 0;
		glGetShaderiv(fShaderID, GL_INFO_LOG_LENGTH, &logSize);
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(fShaderID, logSize, NULL, log);
		MessageHandler::printMessage("ERROR: Cannot compile fragment shader!\n" + std::string(log) + "\n");
	}

	if (vCompileStatus == 0 || fCompileStatus == 0)
		system("PAUSE");
	
	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);

	glLinkProgram(programID);
}

void Shader::start() const
{
	glUseProgram(programID);
}

void Shader::stop() const
{
	glUseProgram(0);
}

void Shader::destroy() const
{
	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);
	glDeleteProgram(programID);
}

void Shader::loadUniform1f(float value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniform1f(location, value);
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

void Shader::loadUniform1i(int value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniform1i(location, value);
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

void Shader::loadUniformVec2f(Vec2 value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniform2f(location, value.x, value.y);
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

void Shader::loadUniformVec3f(Vec3 value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniform3f(location, value.x, value.y, value.z);
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

void Shader::loadUniformVec4f(Vec4 value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniform4f(location, value.x, value.y, value.z, value.w);
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

void Shader::loadUniformMat4f(Mat4 value, const char* uniform) const
{
	GLint location = glGetUniformLocation(programID, uniform);
	if (location != -1)
		glUniformMatrix4fv(location, 1,  GL_TRUE, value.elements);	//NOTE: GLSL Matrices are ROW MAJOR!!! (MUST TRANPOSE!)
	else
	{
		MessageHandler::printMessage("ERROR: Cannot get location of " + std::string(uniform) + " in shaders!\n");
		system("PAUSE");
	}
}

std::string Shader::fileToString(const char* filepath)
{
	std::string converted;
	char c;
	std::ifstream file;
	file.open(filepath);

	if (!file.is_open())
		MessageHandler::printMessage("ERROR: Cannot open " + std::string(filepath) + "!\n");

	file.get(c);

	while (!file.eof())
	{
		converted += c;
		//std::cout << c;
		file.get(c);
	}

	return converted;
}

