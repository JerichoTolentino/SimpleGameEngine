#include "HeightMap.h"
#include <iostream>

#define MAXHEIGHT 20
#define MAXCOLOR 255


HeightMap::HeightMap()
{
	width = -1;
	height = -1;
	channels = -1;
	pixels = nullptr;
}


HeightMap::~HeightMap()
{
}

HeightMap::HeightMap(char* filepath)
{
	pixels = SOIL_load_image(filepath, &width, &height, &channels, SOIL_LOAD_AUTO);

	//std::cout << "HeightMap - Size: " << width << "x" << height << " Channels: " << channels << std::endl;
}

float HeightMap::getHeight(int x, int y) const
{
	//check if requested an area outside of the image
	if (x > width || x < 0 || y > height || y < 0)
		return 0;

	float height = (float)pixels[x * channels + y * channels * width]; //return R value (all are same since it's a gray scale image)
	height -= MAXCOLOR / 2.0;	//-127.5 <= height <= 127.5
	height /= MAXCOLOR / 2.0;	//-1 <= height <= 1
	height *= MAXHEIGHT;		//-maxHeight <= height <= maxHeight
	return height;
}

std::string HeightMap::toString() const
{
	return "--HeightMap--\nWidth: " + std::to_string(width) + "\nHeight: " + std::to_string(height) + "\nChannels: " + std::to_string(channels) + "\nHasPixels: " + std::to_string(pixels != nullptr) + "\n--End HeightMap--";
}

int HeightMap::getSize() const
{
	return width;
}

int HeightMap::getChannels() const
{
	return channels;
}

unsigned char* HeightMap::getPixels() const
{
	return pixels;
}