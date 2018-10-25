/*
CLASS: Mat4
AUTHOR: Jericho J. Tolentino
CREATED: May 9, 2017

A class representing a 4x4 matrix, using floats, that implements basic matrix operations.
NOTE: This matrix class was designed to be used in a computer graphics application.
*/

#pragma once
#include "Vec3.h"
#include <string>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include "MathUtils.h"
#include "../utils/MessageHandler.h"

class Mat4
{
public:
	GLfloat *elements;
public:
	//creates a new column-major matrix with all elements set to 0
	Mat4();

	//copies elements of other into this
	Mat4(const Mat4 &other);

	~Mat4();

	//sets matrix to be an identity matrix
	void setIdentity();
	
	//sets all elements in matrix to 0
	void clear();

	//flips the matrix along the main diagonal
	void transpose();

	//sets the matrix to be the inverse of itself
	void inverse();

	//sets all elements to be the values in the argument array (column major)
	void setElements(float e[16]);

	//scales, rotates about z, rotates about y, rotates about x, then translates the matrix by the given argument values
	void transform(Vec3 translate, Vec3 rotate, Vec3 scale);

	//generate a prospective projection matrix given fov, far, and near clipping planes
	static Mat4 generateProjectionMatrix(float aspectRatio, float fov, float near, float far);

	//generate a view matrix given a camera position and rotation
	static Mat4 generateViewMatrix(Vec3 cameraPos, Vec3 cameraRot);

	//generate a normal matrix given a model transformation matrix
	static Mat4 generateNormalMatrix(Mat4 modelMatrix);

	//copies the other matrix's elements to this matrix's elements
	Mat4& operator=(const Mat4 &other);
	
	//sets this matrix to be the sum of this matrix & the other matrix (dot product)
	Mat4& operator+=(const Mat4 &other);

	//sets this matrix to be the difference of this matrix & the other matrix (dot product)
	Mat4& operator-=(const Mat4 &other);

	//sets this matrix to be the cross product of this matrix and the other matrix
	Mat4& operator*=(const Mat4 &other);

	//returns a matrix which holds the sum of the two argument matrices
	friend Mat4 operator+(Mat4 left, const Mat4 &right);

	//returns a matrix which holds the difference of the two argument matrices
	friend Mat4 operator-(Mat4 left, const Mat4 &right);

	//returns a matrix which holds the cross product of the two argument matrices
	friend Mat4 operator*(Mat4 left, const Mat4 &right);

	//prints the matrix in a readable format
	std::string toString() const;

private:
	//generates a rotation matrix given an angle and axis of rotation
	static Mat4 generateRotation(float angle, Vec3 axis);

	//generates a translation matrix given a translation coordinate
	static Mat4 generateTranslation(Vec3 translate);

	//generates a scaling matrix given the scale
	static Mat4 generateScaling(Vec3 scale);
};
