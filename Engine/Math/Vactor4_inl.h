#pragma once
#include "Math/Vector4.h"

namespace Engine
{

	inline Vector4::Vector4() :
		m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
	{

	}

	inline Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) :
		m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
	{
		
	}

	inline Vector4::Vector4(const Vector4 & i_other):
		m_x(i_other.m_x), m_y(i_other.m_y), m_z(i_other.m_z), m_w(i_other.m_w)
	{
		
	}

	inline Vector4& Vector4::operator=(const Vector4 & i_other)
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;
		m_z = i_other.m_z;
		m_w = i_other.m_w;

		return *this;
	}

	inline Vector4& Vector4::operator+=(const Vector4 & i_rhs)
	{
		m_x += i_rhs.m_x;
		m_y += i_rhs.m_y;
		m_z += i_rhs.m_z;
		m_w += i_rhs.m_w;

		return *this;
	}

	inline Vector4& Vector4::operator-=(const Vector4 & i_rhs)
	{
		m_x -= i_rhs.m_x;
		m_y -= i_rhs.m_y;
		m_z -= i_rhs.m_z;
		m_w -= i_rhs.m_w;

		return *this;
	}

	inline Vector4& Vector4::operator*=(const float i_val)
	{
		m_x *= i_val;
		m_y *= i_val;
		m_z *= i_val;
		m_w *= i_val;

		return *this;
	}

	inline Vector4& Vector4::operator/=(const float i_val)
	{
		m_x /= i_val;
		m_y /= i_val;
		m_z /= i_val;
		m_w /= i_val;

		return *this;
	}

	inline Vector4& Vector4::operator-()
	{
		m_x = -m_x;
		m_y = -m_y;
		m_z = -m_z;
		m_w = -m_w;

		return *this;
	}

	inline Vector4 Vector4::Normalize()
	{
		if (Magnitude() != 0)
		{
			float x = m_x / Magnitude();
			float y = m_y / Magnitude();
			float z = m_z / Magnitude();
			float w = m_w / Magnitude();

			return Vector4(x, y, z, w);
		}
		else
			return Vector4(0, 0, 0, 0);
	}

	inline float Vector4::Magnitude()
	{
		return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2) + pow(m_w, 2));
	}

	inline float Vector4::x() const
	{
		return m_x;
	}

	inline float Vector4::y() const
	{
		return m_y;
	}

	inline float Vector4::z() const
	{
		return m_z;
	}

	inline float Vector4::w() const
	{
		return m_w;
	}

	inline void Vector4::x(float i_x)
	{
		m_x = i_x;
	}

	inline void Vector4::y(float i_y)
	{
		m_y = i_y;
	}

	inline void Vector4::z(float i_z)
	{
		m_z = i_z;
	}

	inline void Vector4::w(float i_w)
	{
		m_w = i_w;
	}

	inline Vector4 operator+(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{
		return Vector4(i_lhs.x()+i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z(), i_lhs.w() + i_rhs.w());
	}

	inline Vector4 operator-(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{
		return Vector4(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z(), i_lhs.w() - i_rhs.w());
	}

	inline Vector4 operator*(const Vector4 & i_lhs, const float i_val)
	{
		return Vector4(i_lhs.x() * i_val, i_lhs.y() * i_val, i_lhs.z() * i_val, i_lhs.w() * i_val);
	}

	inline Vector4 operator*(const float & i_val, const Vector4 & i_rhs)
	{
		return Vector4(i_rhs.x() * i_val, i_rhs.y() * i_val, i_rhs.z() * i_val, i_rhs.w() * i_val);
	}

	inline Vector4 operator/(const Vector4 & i_lhs, const float i_val)
	{
		return Vector4(i_lhs.x() / i_val, i_lhs.y() / i_val, i_lhs.z() / i_val, i_lhs.w() / i_val);
	}

	inline bool operator==(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{
		if (fabs(i_lhs.x() - i_rhs.x()) < EPSILON &&
			fabs(i_lhs.y() - i_rhs.y()) < EPSILON &&
			fabs(i_lhs.z() - i_rhs.z()) < EPSILON &&
			fabs(i_lhs.w() - i_rhs.w()) < EPSILON)
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{
		if (fabs(i_lhs.x() - i_rhs.x()) >= EPSILON ||
			fabs(i_lhs.y() - i_rhs.y()) >= EPSILON ||
			fabs(i_lhs.z() - i_rhs.z()) >= EPSILON ||
			fabs(i_lhs.w() - i_rhs.w()) >= EPSILON)
			return true;
		else
			return false;
	}

	inline float Dot(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{
		return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z() * i_rhs.z() + i_lhs.w() * i_rhs.w();
	}

	inline Vector4 Cross(const Vector4 & i_lhs, const Vector4 & i_rhs)
	{

	}
}