#pragma once
#include <string>
#include "../Math/Vec3.h"
#include "../Models/GeometryModel.h"

namespace SimpleGameEngine::Parsers
{
	class WavefrontObjParser
	{
	private:
		static const std::string VERTEX_LINE;
		static const std::string TEXTURE_UV_LINE;
		static const std::string NORMAL_LINE;
		static const std::string PARAM_SPACE_VERTEX_LINE;
		static const std::string FACE_LINE;
		static const std::string LINE_ELEMENT_LINE;

	public:
		/// <summary>
		/// Parses a wavefront .obj file into a <see cref="GeometryModel"/>.
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		/// <exception cref="ParseException"></exception>
		static Models::GeometryModel parseFile(const std::string & filepath);



	private:
		class WavefrontObjVertex
		{
		private:
			int m_positionIndex;
			int m_textureUvIndex;
			int m_normalIndex;



		public:
			WavefrontObjVertex();
			WavefrontObjVertex(int positionIndex, int textureUvIndex, int normalIndex);
			WavefrontObjVertex(const WavefrontObjVertex & other);
			~WavefrontObjVertex();



			int getPositionIndex() const;
			int getTextureUvIndex() const;
			int getNormalIndex() const;



			WavefrontObjVertex & operator=(const WavefrontObjVertex & other);
			bool operator==(const WavefrontObjVertex & other);
		};
	};
}
