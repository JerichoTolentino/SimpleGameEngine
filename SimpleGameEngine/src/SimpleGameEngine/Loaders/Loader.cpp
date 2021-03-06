#include "sgepch.h"
#include "Loader.h"

#include "TextureLoadException.h"
#include "../Utility/Generic.h"

#define VERTICES_ATTR 0
#define NORMALS_ATTR 1
#define TEXTURES_ATTR 2

using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Utility;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{

	GLuint Loader::loadSkybox(const Models::SkyboxModel & skybox)
	{
		auto vertices = skybox.getVertices();
		auto textureUvs = skybox.getTextureUvs();

		// Flatten vectors
		std::vector<float> flattenedVertices = Generic::flatten(
			vertices->begin(), 
			vertices->end(), 
			(std::function<void(const Vec3 &, std::vector<float> &)>) [](const Vec3 & vec, std::vector<float> & result)
		{
			result.push_back(vec.x);
			result.push_back(vec.y);
			result.push_back(vec.z);
		});
		std::vector<float> flattenedUvs = Generic::flatten(
			textureUvs->begin(), 
			textureUvs->end(), 
			(std::function<void(const Vec3 &, std::vector<float> &)>) [](const Vec3 & vec, std::vector<float> & result)
		{
			result.push_back(vec.x);
			result.push_back(vec.y);
			result.push_back(vec.z);
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		auto indices = skybox.getIndices();
		GLuint * indicesArray = Generic::copyToArray(*indices);
		GLsizeiptr indicesBytesSize = sizeof(GLuint) * indices->size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesBytesSize, indicesArray, GL_STATIC_DRAW);

		// Bind vertices
		GLfloat * verticesArray = Generic::copyToArray(flattenedVertices);
		GLsizeiptr verticesByteSize = sizeof(GLfloat) * flattenedVertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesByteSize, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		GLfloat * textureUvsArray = Generic::copyToArray(flattenedUvs);
		GLsizeiptr textureUvsByteSize = sizeof(GLfloat) * flattenedUvs.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, textureUvsByteSize, textureUvsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded SkyboxModel with {0} vertices, {1} textureUvs, and {2} indices",
					   verticesByteSize / sizeof(GLfloat),
					   textureUvsByteSize / sizeof(GLfloat),
					   indicesBytesSize / sizeof(GLuint));

		return vao;
	}

	GLuint Loader::loadGeometryModel(const GeometryModel & model)
	{
		// Flatten vectors
		auto vertices = model.getVertices();
		std::vector<float> flattenedVertices = Generic::flatten(
			vertices->begin(),
			vertices->end(),
			vertices->size() * 3,
			(std::function<void(const Vec3 &, std::vector<float> &)>) [](const Vec3 & vec, std::vector<float> & result)
		{
			result.push_back(vec.x);
			result.push_back(vec.y);
			result.push_back(vec.z);
		});
		auto normals = model.getNormals();
		std::vector<float> flattenedNormals = Generic::flatten(
			normals->begin(), 
			normals->end(),
			normals->size() * 3,
			(std::function<void(const Vec3 &, std::vector<float> &)>) [](const Vec3 & vec, std::vector<float> & result)
		{
			result.push_back(vec.x);
			result.push_back(vec.y);
			result.push_back(vec.z);
		});
		auto textureUvs = model.getTextureUvs();
		std::vector<float> flattenedUvs = Generic::flatten(
			textureUvs->begin(),
			textureUvs->end(),
			textureUvs->size() * 2,
			(std::function<void(const Vec2 &, std::vector<float> &)>) [](const Vec2 & vec, std::vector<float> & result)
		{
			result.push_back(vec.x);
			result.push_back(vec.y);
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		auto indices = model.getIndices();
		GLuint * indicesArray = Generic::copyToArray(*indices);
		GLsizeiptr indicesByteSize = sizeof(GLuint) * indices->size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indicesArray, GL_STATIC_DRAW);
		
		// Bind vertices
		GLfloat * verticesArray = Generic::copyToArray(flattenedVertices);
		GLsizeiptr verticesByteSize = sizeof(GLfloat) * flattenedVertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesByteSize, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind normals
		GLfloat * normalsArray = Generic::copyToArray(flattenedNormals);
		GLsizeiptr normalsByteSize = sizeof(GLfloat) * flattenedNormals.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, normalsByteSize, normalsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		GLfloat * textureUvsArray = Generic::copyToArray(flattenedUvs);
		GLsizeiptr textureUvsByteSize = sizeof(GLfloat) * flattenedUvs.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, textureUvsByteSize, textureUvsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded GeometryModel with {0} vertices, {1} normals, {2} textureUvs, and {3} indices",
					   verticesByteSize / sizeof(GLfloat),
					   normalsByteSize / sizeof(GLfloat),
					   textureUvsByteSize / sizeof(GLfloat),
					   indicesByteSize / sizeof(GLuint));
	
		return vao;
	}

	GLuint Loader::loadWaterModel(const Models::WaterModel & waterModel)
	{
		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		GLuint * indicesArray = Generic::copyToArray(*waterModel.getIndices());
		GLsizeiptr indicesByteSize = sizeof(GLuint) * waterModel.getIndices()->size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indicesArray, GL_STATIC_DRAW);

		// Bind vertices
		auto vertices = *waterModel.getVertices();
		GLfloat * verticesArray = Generic::copyToArray(vertices);
		GLsizeiptr verticesByteSize = sizeof(GLfloat) * vertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesByteSize, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded WaterModel with {0} vertices and {1} indices.",
					   verticesByteSize / sizeof(GLfloat),
					   indicesByteSize / sizeof(GLuint));

		return vao;
	}

	GLuint Loader::loadGuiElement(const Models::GuiGeometry & guiGeometry)
	{
		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		GLuint * indicesArray = Generic::copyToArray(*guiGeometry.getIndices());
		GLsizeiptr indicesByteSize = sizeof(GLuint) * guiGeometry.getIndices()->size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indicesArray, GL_STATIC_DRAW);

		// Bind vertices
		auto vertices = *guiGeometry.getVertices();
		GLfloat * verticesArray = Generic::copyToArray(vertices);
		GLsizeiptr verticesByteSize = sizeof(GLfloat) * vertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesByteSize, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		auto textureUvs = *guiGeometry.getTextureUvs();
		GLfloat * textureUvsArray = Generic::copyToArray(textureUvs);
		GLsizeiptr textureUvsByteSize = sizeof(GLfloat) * textureUvs.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, textureUvsByteSize, textureUvsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded GuiElement with {0} vertices, {1} textureUvs, and {2} indices.",
					   verticesByteSize / sizeof(GLfloat),
					   textureUvsByteSize / sizeof(GLfloat),
					   indicesByteSize / sizeof(GLuint));

		return vao;
	}

	GLuint Loader::loadTexture(const std::string & filepath)
	{
		GLuint id = SOIL_load_OGL_texture(filepath.c_str(), 0, 0, SOIL_FLAG_INVERT_Y);
		if (id < 0)
			throw TextureLoadException("Failed to load texture: " + filepath);

		glBindTexture(GL_TEXTURE_2D, id);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);

		SGE_CORE_TRACE("Loaded texture ID {0} from file {1}", id, filepath);

		return id;
	}

	GLuint Loader::loadCubemapTexture(
		const std::string & right, 
		const std::string & left, 
		const std::string & up, 
		const std::string & down, 
		const std::string & back, 
		const std::string & front)
	{
		GLuint id = SOIL_load_OGL_cubemap(right.c_str(), left.c_str(), up.c_str(), down.c_str(), back.c_str(), front.c_str(), 0, 0, 0);
		if (id < 0)
			throw TextureLoadException("Failed to load cubemap texture");

		glBindTexture(GL_TEXTURE_CUBE_MAP, id); 
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		SGE_CORE_TRACE("Loaded cubemap texture ID {0} from files\n[\nright: {1},\nleft: {2},\nup: {3},\ndown: {4},\nback: {5},\nfront: {6}\n]", 
			id, right, left, up, down, back, front);

		return id;
	}

	Models::HeightMap Loader::loadHeightMap(const std::string & filepath, int maxHeight)
	{
		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char * pixels = SOIL_load_image(filepath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
		auto pixelsVector = std::make_shared<std::vector<unsigned char>>(Generic::wrapInVector(pixels, width * height * channels));

		SGE_CORE_TRACE("Loaded height map from file {0}", filepath);
		
		return HeightMap(pixelsVector, width, height, channels, maxHeight);
	}

	Models::TexturePack Loader::loadTexturePack(
		const std::string & redTextureFile, 
		const std::string & greenTextureFile, 
		const std::string & blueTextureFile, 
		const std::string & backgroundTextureFile, 
		const std::string & blendMapFile)
	{
		GLuint redTextureId = loadTexture(redTextureFile);
		GLuint greenTextureId = loadTexture(greenTextureFile);
		GLuint blueTextureId = loadTexture(blueTextureFile);
		GLuint backgroundTextureId = loadTexture(backgroundTextureFile);
		GLuint blendMapTextureId = loadTexture(blendMapFile);

		return TexturePack(redTextureId, greenTextureId, blueTextureId, backgroundTextureId, blendMapTextureId);
	}
}
