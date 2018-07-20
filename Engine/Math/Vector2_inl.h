#pragma once
#include <math.h>
#include "Math/Vector2.h"

namespace Engine
{

	inline Vector2::Vector2() :
		m_x(0.0f), m_y(0.0f)
	{

	}

	inline Vector2::Vector2(float i_x, float i_y) :
		m_x(i_x), m_y(i_y)
	{

	}

	inline Vector2::Vector2(const Vector2 & i_other) :
		m_x(i_other.m_x), m_y(i_other.m_y)
	{

	}

	inline Vector2& Vector2::operator=(const Vector2 & i_other)
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;

		return *this;
	}

	inline Vector2& Vector2::operator+=(const Vector2 & i_rhs)
	{
		m_x += i_rhs.m_x;
		m_y += i_rhs.m_y;

		return *this;
	}

	inline Vector2& Vector2::operator-=(const Vector2 & i_rhs)
	{
		m_x -= i_rhs.m_x;
		m_y -= i_rhs.m_y;

		return *this;
	}

	inline Vector2& Vector2::operator*=(const float i_val)
	{
		m_x *= i_val;
		m_y *= i_val;

		return *this;
	}

	inline Vector2& Vector2::operator/=(const float i_val)
	{
		m_x /= i_val;
		m_y /= i_val;

		return *this;
	}

	inline Vector2& Vector2::operator-()
	{
		m_x = -m_x;
		m_y = -m_y;

		return *this;
	}

	inline Vector2 Vector2::Normalize()
	{
		if (Magnitude() != 0)
		{
			float x = m_x / Magnitude();
			float y = m_y / Magnitude();

			return Vector2(x, y);
		}
		else
			return Vector2(0, 0);
	}

	inline float Vector2::Magnitude()
	{
		return sqrt(pow(m_x, 2) + pow(m_y, 2));
	}

	inline float Vector2::x() const
	{
		return m_x;
	}

	inline float Vector2::y() const
	{
		return m_y;
	}

	inline void Vector2::x(float i_x)
	{
		m_x = i_x;
	}

	inline void Vector2::y(float i_y)
	{
		m_y = i_y;
	}

	inline Vector2 operator+(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{
		return Vector2(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y());
	}

	inline Vector2 operator-(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{
		return Vector2(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y());
	}

	inline Vector2 operator*(const Vector2 & i_lhs, const float i_val)
	{
		return Vector2(i_lhs.x() * i_val, i_lhs.y() * i_val);
	}

	inline Vector2 operator*(const float & i_val, const Vector2 & i_rhs)
	{
		return Vector2(i_rhs.x() * i_val, i_rhs.y() * i_val);
	}

	inline Vector2 operator/(const Vector2 & i_lhs, const float i_val)
	{
		return Vector2(i_lhs.x() / i_val, i_lhs.y() / i_val);
	}

	inline bool operator==(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{
		if (fabs(i_lhs.x() - i_rhs.x()) < EPSILON &&
			fabs(i_lhs.y() - i_rhs.y()) < EPSILON )
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{
		if (fabs(i_lhs.x() - i_rhs.x()) >= EPSILON ||
			fabs(i_lhs.y() - i_rhs.y()) >= EPSILON)
			return true;
		else
			return false;
	}

	inline float Dot(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{
		return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y();
	}

	inline Vector2 Cross(const Vector2 & i_lhs, const Vector2 & i_rhs)
	{

	}
}