#include "TexturePack.h"


TexturePack::TexturePack()
{
	redTextureID = 0;
	greenTextureID = 0;
	blueTextureID = 0;
	backTextureID = 0;
	blendMapTextureID = 0;
}

TexturePack::~TexturePack()
{
	if (redTextureID != 0)
		glDeleteTextures(1, &redTextureID);
	if (greenTextureID != 0)
		glDeleteTextures(1, &greenTextureID);
	if (blueTextureID != 0)
		glDeleteTextures(1, &blueTextureID);
	if (backTextureID != 0)
		glDeleteTextures(1, &backTextureID);
	if (blendMapTextureID != 0)
		glDeleteTextures(1, &blendMapTextureID);
}

TexturePack::TexturePack(const char * red, const char * green, const char * blue, const char * back, const char * blend)
{
	redTextureID = Loader::loadTexture(red);
	greenTextureID = Loader::loadTexture(green);
	blueTextureID = Loader::loadTexture(blue);
	backTextureID = Loader::loadTexture(back);
	blendMapTextureID = Loader::loadTexture(blend);
}

GLuint TexturePack::getRedTextureID() const
{
	return redTextureID;
}

GLuint TexturePack::getGreenTextureID() const
{
	return greenTextureID;
}

GLuint TexturePack::getBlueTextureID() const
{
	return blueTextureID;
}

GLuint TexturePack::getBackTextureID() const
{
	return backTextureID;
}

GLuint TexturePack::getBlendMapTextureID() const
{
	return blendMapTextureID;
}

void TexturePack::loadTextures(const char * red, const char * green, const char * blue, const char * back, const char * blend)
{
	if (redTextureID != 0)
		glDeleteTextures(1, &redTextureID);
	if(greenTextureID != 0)
		glDeleteTextures(1, &greenTextureID);
	if (blueTextureID != 0)
		glDeleteTextures(1, &blueTextureID);
	if (backTextureID != 0)
		glDeleteTextures(1, &backTextureID);
	if (blendMapTextureID != 0)
		glDeleteTextures(1, &blendMapTextureID);

	redTextureID = Loader::loadTexture(red);
	greenTextureID = Loader::loadTexture(green);
	blueTextureID = Loader::loadTexture(blue);
	backTextureID = Loader::loadTexture(back);
	blendMapTextureID = Loader::loadTexture(blend);
}

std::string TexturePack::toString() const
{
	return "--TexturePack--\nRed: " + std::to_string(redTextureID) + "\nGreen: " + std::to_string(greenTextureID) + "\nBlue: " + std::to_string(blueTextureID) + "\nBack: " + std::to_string(backTextureID) + "\nBlend: " + std::to_string(blendMapTextureID) + "\n--End TexturePack--";
}
