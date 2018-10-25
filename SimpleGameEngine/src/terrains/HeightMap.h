#pragma once
#include <SOIL.h>
#include <string>

class HeightMap
{
private:
	int width, height, channels;
	unsigned char* pixels;
public:
	HeightMap();
	~HeightMap();

	HeightMap(char* filepath);

	int getSize() const;
	int getChannels() const;
	unsigned char* getPixels() const;
	float getHeight(int x, int y) const;

	std::string toString() const;
};

