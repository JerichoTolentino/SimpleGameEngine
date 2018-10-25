/*
CLASS: Vec3
AUTHOR: Jericho J. Tolentino
CREATED: May 9, 2017

A class representing a 3-component vector using floats.
*/

#pragma once
#include <math.h>
#include <string>
class Vec3
{
public:
	float x, y, z;
public:
	Vec3();
	~Vec3();

	Vec3(float iX, float iY, float iZ);
	Vec3(const Vec3 &other);

	float length() const;
	void normalize();
	void reverse();

	Vec3& add(float value);
	Vec3& subtract(float value);
	Vec3& multiply(float value);
	Vec3& divide(float value);

	Vec3& add(const Vec3 &other);
	Vec3& subtract(const Vec3 &other);
	Vec3& multiply(const Vec3 &other);
	Vec3& divide(const Vec3 &other);
	Vec3& copy(const Vec3 &other);
	bool equals(const Vec3 &other);

	Vec3& operator=(const Vec3 &other);

	friend Vec3 operator+(Vec3 left, const Vec3 &right);
	friend Vec3 operator-(Vec3 left, const Vec3 &right);
	friend Vec3 operator*(Vec3 left, const Vec3 &right);
	friend Vec3 operator/(Vec3 left, const Vec3 &right);

	Vec3& operator+=(const Vec3 &other);
	Vec3& operator-=(const Vec3 &other);
	Vec3& operator*=(const Vec3 &other);
	Vec3& operator/=(const Vec3 &other);

	std::string toString() const;
};

