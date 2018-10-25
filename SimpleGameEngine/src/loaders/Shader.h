#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "../math/engineMath.h"
#include "../utils/MessageHandler.h"

class Shader
{
private:
	GLuint programID, vShaderID, fShaderID;
public:
	Shader();
	~Shader();

	Shader(const char *vertex, const char *fragment);

	void start() const;
	void stop() const;
	void destroy() const;

	void loadUniform1f(float value, const char* uniform) const;
	void loadUniform1i(int value, const char* uniform) const;

	void loadUniformVec2f(Vec2 value, const char* uniform) const;
	void loadUniformVec3f(Vec3 value, const char* uniform) const;
	void loadUniformVec4f(Vec4 value, const char* uniform) const;

	void loadUniformMat4f(Mat4 value, const char* uniform) const;
private:
	std::string fileToString(const char* filepath);
};

