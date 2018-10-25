/*
CLASS: Vec2
AUTHOR: Jericho J. Tolentino
CREATED: May 9, 2017

A class representing a 2-component vector using floats.
*/

#pragma once
#include <math.h>
#include <string>
class Vec2
{
public:
	float x, y;
public:
	Vec2();
	~Vec2();

	Vec2(float iX, float iY);
	Vec2(const Vec2 &other);

	float length() const;
	void normalize();
	void reverse();

	Vec2& add(float value);
	Vec2& subtract(float value);
	Vec2& multiply(float value);
	Vec2& divide(float value);

	Vec2& add(const Vec2 &other);
	Vec2& subtract(const Vec2 &other);
	Vec2& multiply(const Vec2 &other);
	Vec2& divide(const Vec2 &other);
	Vec2& copy(const Vec2 &other);
	bool equals(const Vec2 &other);

	Vec2& operator=(const Vec2 &other);

	friend Vec2 operator+(Vec2 left, const Vec2 &right);
	friend Vec2 operator-(Vec2 left, const Vec2 &right);
	friend Vec2 operator*(Vec2 left, const Vec2 &right);
	friend Vec2 operator/(Vec2 left, const Vec2 &right);

	Vec2& operator+=(const Vec2 &other);
	Vec2& operator-=(const Vec2 &other);
	Vec2& operator*=(const Vec2 &other);
	Vec2& operator/=(const Vec2 &other);

	std::string toString() const;
};

