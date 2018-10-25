#include "Terrain.h"



Terrain::Terrain()
{
	position = Vec3(0, 0, 0);
	tileSize = 1;
	numRows = 1;
	numCols = 1;
	model = generateTerrainMesh(tileSize, numRows, numCols);
	//hasTexturePack = false;

	MessageHandler::printMessage("WARNING: Default Terrain constructor called!\n");
}


Terrain::~Terrain()
{
	delete model;
}

Terrain::Terrain(Vec3 pos, int tile_size, int tileFac, int rows, int cols)
{
	position = pos;
	tileSize = tile_size;
	tileFactor = tileFac;
	numRows = rows;
	numCols = cols;
	model = generateTerrainMesh(tileSize, numRows, numCols);
	//hasTexturePack = false;
}

Terrain::Terrain(Vec3 pos, int tile_size, int tileFac, int rows, int cols, TexturePack * pack, HeightMap *height)
{
	position = pos;
	tileSize = tile_size;
	tileFactor = tileFac;
	numRows = rows; //TODO: Get rid of this!
	numCols = cols; //TODO: Get rid of this!
	heightMap = height;
	texturePack = pack;
	int adjustedSize = heightMap->getSize() - 1;	//subtract one because the generateTerrainMesh() method adds an extra row/column of vertices
	MessageHandler::printMessage("Height Map Size: " + std::to_string(heightMap->getSize()));
	model = generateTerrainMesh(tileSize, adjustedSize, adjustedSize);
	//hasTexturePack = true;
}

Vec3 Terrain::getPosition() const
{
	return position;
}

int Terrain::getTileSize() const
{
	return tileSize;
}

int Terrain::getTileFactor() const
{
	return tileFactor;
}

int Terrain::getNumRows() const
{
	return numRows;
}

int Terrain::getNumCols() const
{
	return numCols;
}

Model * Terrain::getModel() const
{
	return model;
}

TexturePack * Terrain::getTexturePack() const
{
	return texturePack;
}

HeightMap * Terrain::getHeightMap() const
{
	return heightMap;
}

void Terrain::setPosition(Vec3 pos)
{
	position = pos;
}

void Terrain::setTileSize(int size)
{
	tileSize = size;
}

void Terrain::setTileFactor(int factor)
{
	tileFactor = factor;
}

void Terrain::setNumRows(int rows)
{
	numRows = rows;
}

void Terrain::setNumCols(int cols)
{
	numCols = cols;
}

void Terrain::setModel(Model * m)
{
	model = m;
}

void Terrain::setTexturePack(TexturePack * tp)
{
	texturePack = tp;
}

void Terrain::setHeightMap(HeightMap * height)
{
	heightMap = height;
}

float Terrain::getHeight(const Vec3 &pos) const
{
	Vec3 posWRTTerrain = pos - position;

	//find which "tile" we are in (within the terrain grid)
	int cellX = std::floor(posWRTTerrain.x / tileSize);
	int cellZ = std::floor(posWRTTerrain.z / tileSize);

	//find where in that "tile" we are in
	float posWRTCellX = std::fmodf(posWRTTerrain.x, tileSize) / tileSize;
	float posWRTCellZ = std::fmodf(posWRTTerrain.z, tileSize) / tileSize;
	float finalHeight;
	if (posWRTCellX <= 1 - posWRTCellZ)
	{
		finalHeight = MathUtils::barryCentric(Vec3(0, heightMap->getHeight(cellX, cellZ), 0), Vec3(1, heightMap->getHeight(cellX + 1, cellZ), 0),Vec3(0,heightMap->getHeight(cellX, cellZ + 1), 1), Vec2(posWRTCellX, posWRTCellZ));
	}
	 else {
		 finalHeight = MathUtils::barryCentric(Vec3(1, heightMap->getHeight(cellX + 1, cellZ), 0), Vec3(1,heightMap->getHeight(cellX + 1, cellZ + 1), 1), Vec3(0,heightMap->getHeight(cellX, cellZ + 1), 1), Vec2(posWRTCellX, posWRTCellZ));
	 }

	 return finalHeight;
	//std::cout << "X: " << posWRTCellX << " Z: " << posWRTCellZ << std::endl;
	//return heightMap->getHeight(posWRTTerrain.x, posWRTTerrain.z); //NOTE: This CASTS float to int! (floors it!)
}

Mat4 Terrain::generateTransformationMatrix() const
{
	Mat4 transformations;
	transformations.setIdentity();

	transformations.transform(position, Vec3(0, 0, 0), Vec3(1, 1, 1));

	return transformations;
}

std::string Terrain::toString() const
{
	std::string retVal = "Terrain:\n" + model->toString() + "\nPosition: " + position.toString() + "\nTileSize: " + std::to_string(tileSize) + "\nNumRows: " + std::to_string(numRows) + "\nNumCols: " + std::to_string(numCols);// +"\nHasTexturePack: " + std::to_string(hasTexturePack);
	
	//if (hasTexturePack)
		retVal += "\n" + texturePack->toString() + "\n" + heightMap->toString();

	retVal += "\n--End Terrain--";
	
	return retVal;
}

Model* Terrain::generateTerrainMesh(const int tile_size, const int rows, const int cols) const
{
	float fRows = rows;
	float fCols = cols;
	float rowEdge = rows * tile_size;	//used when calculating z-coordinate for winding (since -z is forwards)

	GLfloat *vertices = new GLfloat[rows * cols * 3 * 4];
	GLfloat *normals = new GLfloat[rows * cols * 3 * 4];	//TODO: These are all set to point Y-up for now
	GLfloat *textures = new GLfloat[rows * cols * 2 * 4];
	GLuint *indices = new GLuint[rows * cols * 6];

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			int tileOffset = col * 4 + row * 4 * cols;
			float x, z;

			//calculates 4 vertices

			//bot left
			x = col * tile_size;
			z = rowEdge - row * tile_size;
			vertices[tileOffset * 3] = x;
			vertices[tileOffset * 3 + 1] = heightMap->getHeight(x, z);	//TODO: Use a height map to set this!
			vertices[tileOffset * 3 + 2] = z;
			//vertices[tileOffset * 3 + 2] = row * tile_size;

			//bot right
			x = (col + 1) * tile_size;
			z = rowEdge - row * tile_size;
			vertices[(tileOffset + 1) * 3] = x;
			vertices[(tileOffset + 1) * 3 + 1] = heightMap->getHeight(x, z);	//TODO: Use a height map to set this!
			vertices[(tileOffset + 1) * 3 + 2] = z;
			//vertices[(tileOffset + 1) * 3 + 2] = row * tile_size;

			//top left
			x = col * tile_size;
			z = rowEdge - (row + 1) * tile_size;
			vertices[(tileOffset + 2) * 3] = x;
			vertices[(tileOffset + 2) * 3 + 1] = heightMap->getHeight(x, z);	//TODO: Use a height map to set this!
			vertices[(tileOffset + 2) * 3 + 2] = z;
			//vertices[(tileOffset + 2) * 3 + 2] = (row + 1) * tile_size;

			//top right
			x = (col + 1) * tile_size;
			z = rowEdge - (row + 1) * tile_size;
			vertices[(tileOffset + 3) * 3] = x;
			vertices[(tileOffset + 3) * 3 + 1] = heightMap->getHeight(x, z);	//TODO: Use a height map to set this!
			vertices[(tileOffset + 3) * 3 + 2] = z;
			//vertices[(tileOffset + 3) * 3 + 2] = (row + 1) * tile_size;

			//calculate 4 normals

			//bot left
			normals[tileOffset * 3] = 0;
			normals[tileOffset * 3 + 1] = 1;	//TODO: Use neighbouring vertices to set this!
			normals[tileOffset * 3 + 2] = 0;

			//bot right
			normals[(tileOffset + 1) * 3] = 0;
			normals[(tileOffset + 1) * 3 + 1] = 1;	//TODO: Use neighbouring vertices to set this!
			normals[(tileOffset + 1) * 3 + 2] = 0;

			//top left
			normals[(tileOffset + 2) * 3] = 0;
			normals[(tileOffset + 2) * 3 + 1] = 1;	//TODO: Use neighbouring vertices to set this!
			normals[(tileOffset + 2) * 3 + 2] = 0;

			//top right
			normals[(tileOffset + 3) * 3] = 0;
			normals[(tileOffset + 3) * 3 + 1] = 1;	//TODO: Use neighbouring vertices to set this!
			normals[(tileOffset + 3) * 3 + 2] = 0;

			//calculate 4 texture coords

			//bot left
			textures[tileOffset * 2] = col / fCols;
			textures[tileOffset * 2 + 1] = row / fRows;

			//bot right
			textures[(tileOffset + 1) * 2] = (col + 1) / fCols;
			textures[(tileOffset + 1) * 2 + 1] = row / fRows;

			//top left
			textures[(tileOffset + 2) * 2] = col / fCols;
			textures[(tileOffset + 2) * 2 + 1] = (row + 1) / fRows;

			//top right
			textures[(tileOffset + 3) * 2] = (col + 1) / fCols;
			textures[(tileOffset + 3) * 2 + 1] = (row + 1) / fRows;

			//calculate indices
			int indexOffset = col * 6 + row * 6 * cols;

			//bot left triangle
			indices[indexOffset] = tileOffset + 2;
			indices[indexOffset + 1] = tileOffset;
			indices[indexOffset + 2] = tileOffset + 1;

			//top right triangle
			indices[indexOffset + 3] = tileOffset + 1;
			indices[indexOffset + 4] = tileOffset + 3;
			indices[indexOffset + 5] = tileOffset + 2;
		}
	}

	Model *m = Loader::loadModel(vertices, normals, textures, indices, rows * cols * 4,
		rows * cols * 4, rows * cols * 4, rows * cols * 6);

	//CORRECTNESS CHECK
	/*
	std::cout << "Checking vertices[]...\n";
	for (unsigned int i = 0; i < rows * cols * 3 * 4; i += 3)
	{
		std::cout << "Vertex: (" << vertices[i] << "," << vertices[i + 1] << "," << vertices[i + 2] << ")\n";
	}
	std::cout << "Checking normals[]...\n";
	for (unsigned int i = 0; i < rows * cols * 3 * 4; i += 3)
	{
		std::cout << "Normal: (" << normals[i] << "," << normals[i + 1] << "," << normals[i + 2] << ")\n";
	}
	std::cout << "Checking textures[]...\n";
	for (unsigned int i = 0; i < rows * cols * 2 * 4; i += 2)
	{
		std::cout << "Texture: (" << textures[i] << "," << textures[i + 1] << ")\n";
	}
	std::cout << "Checking indices[]...\n";
	for (unsigned int i = 0; i < rows * cols * 6; i += 3)
	{
		std::cout << "Triangle: {" << indices[i] << "," << indices[i + 1] << "," << indices[i + 2] << ")\n";
	}
	*/
	//END CORRECTNESS CHECK

	delete vertices;
	delete normals;
	delete textures;
	delete indices;

	return m;
}
