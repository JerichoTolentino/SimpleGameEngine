#include "sgepch.h"
#include "Vec2.h"

namespace SimpleGameEngine::Math
{
	Vec2::Vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vec2::Vec2(float iX, float iY)
	{
		this->x = iX;
		this->y = iY;
	}

	Vec2::Vec2(const Vec2 &other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	Vec2::~Vec2()
	{
	}



	float Vec2::length() const
	{
		return sqrt((this->x * this->x) + (this->y * this->y));
	}

	void Vec2::normalize()
	{
		float length = this->length();
		this->x /= length;
		this->y /= length;
	}

	void Vec2::reverse()
	{
		this->x = -(this->x);
		this->y = -(this->y);
	}

	Vec2& Vec2::add(float value)
	{
		this->x += value;
		this->y += value;
		return *this;
	}

	Vec2& Vec2::add(const Vec2 &other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2& Vec2::subtract(float value)
	{
		this->x -= value;
		this->y -= value;
		return *this;
	}

	Vec2& Vec2::subtract(const Vec2 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2& Vec2::multiply(float value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	Vec2& Vec2::multiply(const Vec2 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vec2& Vec2::divide(float value)
	{
		this->x /= value;
		this->y /= value;
		return *this;
	}

	Vec2& Vec2::divide(const Vec2 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	Vec2& Vec2::copy(const Vec2 &other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	bool Vec2::equals(const Vec2 &other)
	{
		return (this->x == other.x && this->y == other.y);
	}

	std::string Vec2::toString() const
	{
		return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	}



	Vec2& Vec2::operator=(const Vec2 &other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vec2& Vec2::operator+=(const Vec2 &other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2& Vec2::operator*=(const Vec2 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vec2& Vec2::operator/=(const Vec2 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}



	Vec2 operator+(Vec2 left, const Vec2 &right)
	{
		left += right;
		return left;
	}

	Vec2 operator-(Vec2 left, const Vec2 &right)
	{
		left -= right;
		return left;
	}

	Vec2 operator*(Vec2 left, const Vec2 &right)
	{
		left *= right;
		return left;
	}

	Vec2 operator/(Vec2 left, const Vec2 &right)
	{
		left /= right;
		return left;
	}
}
