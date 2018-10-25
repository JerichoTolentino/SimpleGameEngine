#include "Skybox.h"



Skybox::Skybox()
{
	vaoID = initVertices();
	textureID = 0;
	MessageHandler::printMessage("WARNING: Default Skybox constructor called!\n");
}


Skybox::~Skybox()
{
}

Skybox::Skybox(const char* right, const char* left, const char* up, const char* down, const char* back, const char* front)
{
	//NOTE: numIndices initialized in "initVertices()" method!
	vaoID = initVertices();
	textureID = Loader::loadCubemapTexture(right, left, up, down, back, front);
}

GLuint Skybox::getVAO() const
{
	return vaoID;
}

GLuint Skybox::getTextureID() const
{
	return textureID;
}

int Skybox::getNumIndices() const
{
	return numIndices;
}

std::string Skybox::toString() const
{
	return "--Skybox--\nVao ID: " + std::to_string(vaoID) + "\nTexture ID: " + std::to_string(textureID) + "\nnumIndices: " + std::to_string(numIndices) + "\n--End Skybox--";
}

GLuint Skybox::initVertices()
{
	/*
	
	this is just raw data that works with glDrawArrays()... don't want to delete it yet (cuz of the amount of time spent
	making this damn thing that should've been spent doing other things..)
	
	GLfloat *vertices = new GLfloat[]
	{
		//neg-z square
		-SIZE, SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,

		//pos-x square
		SIZE, SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, -SIZE,

		//pos-z square
		SIZE, SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,

		//neg-x square
		-SIZE, SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, SIZE,

		//pos-y square
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,

		//neg-y square
		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE
	};

	GLfloat *textureCoords = new GLfloat[]
	{
		//neg-z square
		-SIZE, SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,

		//pos-x square
		SIZE, SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, -SIZE,

		//pos-z square
		SIZE, SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,

		//neg-x square
		-SIZE, SIZE, SIZE,
		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, SIZE,

		//pos-y square
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,

		//neg-y square
		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE
	};*/

	int numVertices = 3 * 4 * 6;

	GLfloat *vertices = new GLfloat[numVertices]
	{
		//neg-z square
		-SIZE, SIZE, -SIZE,		//0
		-SIZE, -SIZE, -SIZE,	//1
		SIZE, -SIZE, -SIZE,		//2
		SIZE, SIZE, -SIZE,		//3
		// 0, 1, 2, 2, 3, 0,

		//pos-x square
		SIZE, SIZE, -SIZE,		//4
		SIZE, -SIZE, -SIZE,		//5
		SIZE, -SIZE, SIZE,		//6
		SIZE, SIZE, SIZE,		//7
		// 4, 5, 6, 6, 7, 4,

		//pos-z square
		SIZE, SIZE, SIZE,		//8
		SIZE, -SIZE, SIZE,		//9
		-SIZE, -SIZE, SIZE,		//10
		-SIZE, SIZE, SIZE,		//11
		// 8, 9, 10, 10, 11, 8,

		//neg-x square
		-SIZE, SIZE, SIZE,		//12
		-SIZE, -SIZE, SIZE,		//13
		-SIZE, -SIZE, -SIZE,	//14
		-SIZE, SIZE, -SIZE,		//15
		// 12, 13, 14, 14, 15, 12,

		//pos-y square
		-SIZE, SIZE, SIZE,		//16
		-SIZE, SIZE, -SIZE,		//17
		SIZE, SIZE, -SIZE,		//18
		SIZE, SIZE, SIZE,		//19
		// 16, 17, 18, 18, 19, 16,

		//neg-y square
		-SIZE, -SIZE, -SIZE,	//20
		-SIZE, -SIZE, SIZE,		//21
		SIZE, -SIZE, SIZE,		//22
		SIZE, -SIZE, -SIZE,		//23
		// 20, 21, 22, 22, 23, 20

	};

	GLfloat *textures = new GLfloat[numVertices]
	{
		//neg-z square
		-1, 1, -1,		//0
		-1, -1, -1,	//1
		1, -1, -1,		//2
		1, 1, -1,		//3
		// 0, 1, 2, 2, 3, 0,

		//pos-x square
		1, 1, -1,		//4
		1, -1, -1,		//5
		1, -1, 1,		//6
		1, 1, 1,		//7
		// 4, 5, 6, 6, 7, 4,

		//pos-z square
		1, 1, 1,		//8
		1, -1, 1,		//9
		-1, -1, 1,		//10
		-1, 1, 1,		//11
		// 8, 9, 10, 10, 11, 8,

		//neg-x square
		-1, 1, 1,		//12
		-1, -1, 1,		//13
		-1, -1, -1,	//14
		-1, 1, -1,		//15
		// 12, 13, 14, 14, 15, 12,

		//pos-y square
		-1, 1, 1,		//16
		-1, 1, -1,		//17
		1, 1, -1,		//18
		1, 1, 1,		//19
		// 16, 17, 18, 18, 19, 16,

		//neg-y square
		-1, -1, -1,	//20
		-1, -1, 1,		//21
		1, -1, 1,		//22
		1, -1, -1,		//23
		// 20, 21, 22, 22, 23, 20
	};


	numIndices = 6 * 6;	//TODO: hard coded...

	GLuint *indices = new GLuint[numIndices]
	{
		//neg-z face
		0, 1, 2, 2, 3, 0,

		//pos-x face
		4, 5, 6, 6, 7, 4,

		//pos-z face
		8, 9, 10, 10, 11, 8,

		//neg-x face
		12, 13, 14, 14, 15, 12,

		//pos-y face
		16, 17, 18, 18, 19, 16,

		//neg-y face
		20, 21, 22, 22, 23, 20
	};

	//TODO: Sometimes program breaks here!
	GLuint vao = Loader::loadSkybox(vertices, textures, indices, numVertices, numVertices, numIndices);

	delete[] vertices;
	delete[] textures;
	delete[] indices;

	return vao;
}