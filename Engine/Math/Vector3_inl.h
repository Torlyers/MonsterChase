#pragma once
#include "Math/Vector3.h"

namespace Engine
{

	inline Vector3::Vector3() :
		m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{

	}

	inline Vector3::Vector3(float i_x, float i_y, float i_z)
	{
		m_Vec = _mm_set_ps(0.0f, i_z, i_y, i_x);
	}

	inline Vector3::Vector3(Vector2 i_Vec, float i_z)
	{
		m_Vec = _mm_set_ps(0.0f, i_z, i_Vec.y(), i_Vec.x());
	}

	inline Vector3::Vector3(__m128 i_Vec):
		m_Vec(i_Vec)
	{

	}

	inline Vector3::Vector3(const Vector3 & i_other) :
		m_Vec(i_other.m_Vec)
	{

	}

	inline Vector3& Vector3::operator=(const Vector3 & i_other)
	{
		m_Vec = i_other.m_Vec;

		return *this;
	}

	inline Vector3& Vector3::operator+=(const Vector3 & i_rhs)
	{
		m_Vec = _mm_add_ps(m_Vec, i_rhs.m_Vec);

		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3 & i_rhs)
	{
		m_Vec = _mm_sub_ps(m_Vec, i_rhs.m_Vec);

		return *this;
	}

	inline Vector3& Vector3::operator*=(const float i_val)
	{
		m_Vec = _mm_mul_ps(m_Vec, _mm_set_ps1(i_val));

		return *this;
	}

	inline Vector3& Vector3::operator/=(const float i_val)
	{
		m_Vec = _mm_div_ps(m_Vec, _mm_set_ps1(i_val));

		return *this;
	}

	inline Vector3& Vector3::operator-()
	{
		m_Vec = _mm_mul_ps(m_Vec, _mm_set_ps1(-1.0f));

		return *this;
	}

	inline Vector3 Vector3::Normalize()
	{
		float mag = Magnitude();
		
		if (!IsFloatZero(mag))
		{
			m_Vec = _mm_div_ps(m_Vec, _mm_set_ps1(mag));
			return Vector3(m_Vec);			
		}
		else
			return Vector3(0, 0, 0);
	}

	inline float Vector3::Magnitude()
	{
		float sqr = Dot(m_Vec, m_Vec);
		return fabs(sqrt(sqr));
	}

	inline float Vector3::x() const
	{
		return m_x;
	}

	inline float Vector3::y() const
	{
		return m_y;
	}

	inline float Vector3::z() const
	{
		return m_z;
	}

	inline __m128 Vector3::Vec() const
	{
		return m_Vec;
	}

	inline void Vector3::x(float i_x)
	{
		m_x = i_x;
	}

	inline void Vector3::y(float i_y)
	{
		m_y = i_y;
	}

	inline void Vector3::z(float i_z)
	{
		m_z = i_z;
	}

	inline Vector3 operator+(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		__m128 vec = _mm_add_ps(i_lhs.Vec(), i_rhs.Vec());
		return Vector3(vec);
	}

	inline Vector3 operator-(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		__m128 vec = _mm_sub_ps(i_lhs.Vec(), i_rhs.Vec());
		return Vector3(vec);
	}

	inline Vector3 operator*(const Vector3 & i_lhs, const float i_val)
	{
		__m128 vec = _mm_mul_ps(i_lhs.Vec(), _mm_set_ps1(i_val));
		return Vector3(vec);
	}

	inline Vector3 operator*(const float & i_val, const Vector3 & i_rhs)
	{
		__m128 vec = _mm_mul_ps(i_rhs.Vec(), _mm_set_ps1(i_val));
		return Vector3(vec);
	}

	inline Vector3 operator/(const Vector3 & i_lhs, const float i_val)
	{
		__m128 vec = _mm_div_ps(i_lhs.Vec(), _mm_set_ps1(i_val));
		return Vector3(vec);
	}

	inline bool operator==(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		if (IsFloatZero(i_lhs.x() - i_rhs.x()) &&
			IsFloatZero(i_lhs.y() - i_rhs.y()) &&
			IsFloatZero(i_lhs.z() - i_rhs.z()))
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		if (IsFloatZero(i_lhs.x() - i_rhs.x()) ||
			IsFloatZero(i_lhs.y() - i_rhs.y()) ||
			IsFloatZero(i_lhs.z() - i_rhs.z()))
			return true;
		else
			return false;
	}

	inline float Dot(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		return _mm_cvtss_f32(_mm_dp_ps(i_lhs.Vec(), i_rhs.Vec(), 0x71));
	}

	inline Vector3 Cross(const Vector3 & i_lhs, const Vector3 & i_rhs)
	{
		return _mm_sub_ps(
		       _mm_mul_ps(_mm_shuffle_ps(i_lhs.Vec(), i_lhs.Vec(), _MM_SHUFFLE(3, 0, 2, 1)),
				          _mm_shuffle_ps(i_rhs.Vec(), i_rhs.Vec(), _MM_SHUFFLE(3, 1, 0, 2))),
			   _mm_mul_ps(_mm_shuffle_ps(i_lhs.Vec(), i_lhs.Vec(), _MM_SHUFFLE(3, 1, 0, 2)), 
				          _mm_shuffle_ps(i_rhs.Vec(), i_rhs.Vec(), _MM_SHUFFLE(3, 0, 2, 1)))
		);
	}
}