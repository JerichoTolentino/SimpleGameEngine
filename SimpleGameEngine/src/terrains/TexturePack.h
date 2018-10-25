#pragma once
#include "../loaders/Loader.h"

class TexturePack
{
private:
	GLuint redTextureID;
	GLuint greenTextureID;
	GLuint blueTextureID;
	GLuint backTextureID;
	GLuint blendMapTextureID;
public:
	TexturePack();
	~TexturePack();

	TexturePack(const char* red, const char* green, const char* blue, const char* back, const char* blend);

	GLuint getRedTextureID() const;
	GLuint getGreenTextureID() const;
	GLuint getBlueTextureID() const;
	GLuint getBackTextureID() const;
	GLuint getBlendMapTextureID() const;

	void loadTextures(const char* red, const char* green, const char* blue, const char* back, const char* blend);

	std::string toString() const;
};

