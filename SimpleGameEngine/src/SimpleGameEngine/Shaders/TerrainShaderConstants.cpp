#include "TerrainShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string TerrainShaderConstants::VERT_MODEL_MATRIX = "uModelMatrix";
	const std::string TerrainShaderConstants::VERT_PROJECTION_MATRIX = "uProjectionMatrix";
	const std::string TerrainShaderConstants::VERT_VIEW_MATRIX = "uViewMatrix";
	const std::string TerrainShaderConstants::VERT_LIGHT_POSITION = "uLightPosition";

	const std::string TerrainShaderConstants::FRAG_AMBIENT = "uAmbient";
	const std::string TerrainShaderConstants::FRAG_DIFFUSE = "uDiffuse";
	const std::string TerrainShaderConstants::FRAG_OPACITY = "uOpacity";
	const std::string TerrainShaderConstants::FRAG_TILE_FACTOR = "uTileFactor";
	const std::string TerrainShaderConstants::FRAG_BLEND_SAMPLER = "uBlendMapSampler";
	const std::string TerrainShaderConstants::FRAG_RED_SAMPLER = "uRedSampler";
	const std::string TerrainShaderConstants::FRAG_GREEN_SAMPLER = "uGreenSampler";
	const std::string TerrainShaderConstants::FRAG_BLUE_SAMPLER = "uBlueSampler";
	const std::string TerrainShaderConstants::FRAG_BACKGROUND_SAMPLER = "uBackgroundSampler";

	const int TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT = 0;
	const int TerrainShaderConstants::RED_TEXTURE_SLOT = 1;
	const int TerrainShaderConstants::GREEN_TEXTURE_SLOT = 2;
	const int TerrainShaderConstants::BLUE_TEXTURE_SLOT = 3;
	const int TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT = 4;

	const GLenum TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT_OPENGL = GL_TEXTURE0;
	const GLenum TerrainShaderConstants::RED_TEXTURE_SLOT_OPENGL = GL_TEXTURE1;
	const GLenum TerrainShaderConstants::GREEN_TEXTURE_SLOT_OPENGL = GL_TEXTURE2;
	const GLenum TerrainShaderConstants::BLUE_TEXTURE_SLOT_OPENGL = GL_TEXTURE3;
	const GLenum TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT_OPENGL = GL_TEXTURE4;
}
