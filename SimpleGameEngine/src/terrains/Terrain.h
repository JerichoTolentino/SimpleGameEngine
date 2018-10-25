#pragma once
#include "../math/engineMath.h"
#include "../entities/Model.h"
#include "../loaders/ObjectFileLoader.h"
#include "TexturePack.h"
#include "HeightMap.h"

class Terrain
{
private:
	Model *model;
	TexturePack *texturePack;
	HeightMap *heightMap;
	//bool hasTexturePack;
	Vec3 position;
	int tileSize;
	int tileFactor;
	int numRows;
	int numCols;
public:
	Terrain();
	virtual ~Terrain();

	Terrain(Vec3 pos, int tile_size, int tileFac, int rows, int cols);
	Terrain(Vec3 pos, int tile_size, int tileFac, int rows, int cols, TexturePack *pack, HeightMap *height);

	Vec3 getPosition() const;
	int getTileSize() const;
	int getTileFactor() const;
	int getNumRows() const;
	int getNumCols() const;
	Model *getModel() const;
	TexturePack* getTexturePack() const;
	HeightMap* getHeightMap() const;

	void setPosition(Vec3 pos);
	void setTileSize(int size);
	void setTileFactor(int factor);
	void setNumRows(int rows);
	void setNumCols(int cols);
	void setModel(Model* m);
	void setTexturePack(TexturePack* tp);
	void setHeightMap(HeightMap *height);

	float getHeight(const Vec3 &pos) const;
	Mat4 generateTransformationMatrix() const;
	
	std::string toString() const;
private:
	Model* generateTerrainMesh(const int tile_size, const int rows, const int cols) const;
};

