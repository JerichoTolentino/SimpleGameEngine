/*
CLASS: Vec4
AUTHOR: Jericho J. Tolentino
CREATED: May 9, 2017

A class representing a 4-component vector using floats.
*/

#pragma once
#include <math.h>
#include <string>
class Vec4
{
public:
	float x, y, z, w;
public:
	Vec4();
	~Vec4();

	Vec4(float iX, float iY, float iZ, float iW);
	Vec4(const Vec4 &other);

	float length() const;
	void normalize();
	void reverse();

	Vec4& add(float value);
	Vec4& subtract(float value);
	Vec4& multiply(float value);
	Vec4& divide(float value);

	Vec4& add(const Vec4 &other);
	Vec4& subtract(const Vec4 &other);
	Vec4& multiply(const Vec4 &other);
	Vec4& divide(const Vec4 &other);
	Vec4& copy(const Vec4 &other);
	bool equals(const Vec4 &other);

	Vec4& operator=(const Vec4 &other);

	friend Vec4 operator+(Vec4 left, const Vec4 &right);
	friend Vec4 operator-(Vec4 left, const Vec4 &right);
	friend Vec4 operator*(Vec4 left, const Vec4 &right);
	friend Vec4 operator/(Vec4 left, const Vec4 &right);

	Vec4& operator+=(const Vec4 &other);
	Vec4& operator-=(const Vec4 &other);
	Vec4& operator*=(const Vec4 &other);
	Vec4& operator/=(const Vec4 &other);

	std::string toString() const;
};

