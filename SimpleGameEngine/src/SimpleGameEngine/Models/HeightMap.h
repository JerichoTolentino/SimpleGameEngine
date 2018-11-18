#pragma once
#include <vector>
#include <memory>

namespace SimpleGameEngine::Models
{
	class HeightMap
	{
	private:
		std::shared_ptr<std::vector<unsigned char>> m_pixels;
		int m_width;
		int m_height;
		int m_maxHeight;
		int m_channels;



	public:
		HeightMap();
		HeightMap(const std::shared_ptr<std::vector<unsigned char>> pixels, int width, int height, int channels, int maxHeight);
		HeightMap(const HeightMap & other);
		virtual ~HeightMap();



		std::shared_ptr<std::vector<unsigned char>> getPixels() const;
		int getWidth() const;
		int getHeight() const;
		int getMaxHeight() const;
		int getChannels() const;



		/// <summary>
		/// Finds the height at a location in the height map.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		float findHeightAt(int x, int y);



		HeightMap & operator=(const HeightMap & other);



		/// <summary>
		/// Generates a <see cref="HeightMap"/> with a maximum height of 0.
		/// </summary>
		static HeightMap GenerateFlatHeightMap(int width, int height, int channels);
	};
}
