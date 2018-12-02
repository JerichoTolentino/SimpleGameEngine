#include "sgepch.h"
#include "HeightMap.h"

constexpr int MAX_COLOR = 255;

namespace SimpleGameEngine::Models
{
	HeightMap::HeightMap()
	{
	}

	HeightMap::HeightMap(const std::shared_ptr<std::vector<unsigned char>> pixels, int width, int height, int channels, int maxHeight)
	{
		m_pixels = pixels;
		m_width = width;
		m_height = height;
		m_channels = channels;
		m_maxHeight = maxHeight;
	}

	HeightMap::HeightMap(const HeightMap & other)
		: HeightMap(other.m_pixels, other.m_width, other.m_height, other.m_channels, other.m_maxHeight)
	{
	}

	HeightMap::~HeightMap()
	{
	}



	std::shared_ptr<std::vector<unsigned char>> HeightMap::getPixels() const
	{
		return m_pixels;
	}

	int HeightMap::getWidth() const
	{
		return m_width;
	}

	int HeightMap::getHeight() const
	{
		return m_height;
	}

	int HeightMap::getMaxHeight() const
	{
		return m_maxHeight;
	}

	int HeightMap::getChannels() const
	{
		return m_channels;
	}



	float HeightMap::findHeightAt(int x, int y)
	{
		// Check if requested an area outside of the image
		if (x > m_width || x < 0 || y > m_height || y < 0)
			throw std::out_of_range("Location does not exist in height map: (" + std::to_string(x) + ", " + std::to_string(y) + ")");

		// Get the R value (RGB values are all the same since it's a gray scale image)
		float height = (float) (*m_pixels)[x * m_channels + y * m_channels * m_width];

		// Normalize to max height
		height -= MAX_COLOR / 2.0;	//-127.5 <= height <= 127.5
		height /= MAX_COLOR / 2.0;	//-1 <= height <= 1
		height *= m_maxHeight;		//-maxHeight <= height <= maxHeight
		
		return height;
	}

	HeightMap & HeightMap::operator=(const HeightMap & other)
	{
		m_pixels = other.m_pixels;
		m_width = other.m_width;
		m_height = other.m_height;
		m_maxHeight = other.m_maxHeight;
		m_channels = other.m_channels;

		return *this;
	}



	HeightMap HeightMap::GenerateFlatHeightMap(int width, int height, int channels)
	{
		int size = width * height * channels;
		auto pixels = std::make_shared<std::vector<unsigned char>>(size, 0U);

		return HeightMap(pixels, width, height, channels, 0);
	}
}
