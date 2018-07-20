#pragma once
#include"Math/Matrix4.h"

namespace Engine
{

	inline Matrix4::Matrix4()
	{
		for (int i = 0; i < 16; ++i)
			m_elements[i] = 0;		
		m_elements[0] = m_elements[5] = m_elements[10] = m_elements[15] = 1.0f;
	}

	inline Matrix4::Matrix4(float i_array[16])
	{
		for (int i = 0; i < 16; ++i)
			m_elements[i] = i_array[i];
	}

	inline Matrix4::Matrix4(const Matrix4 & i_other)
	{
		for (int i = 0; i < 4; ++i)
			m_Rows[i] = i_other.m_Rows[i];
	}

	inline Matrix4& Matrix4::operator=(const Matrix4 & i_other)
	{
		for (int i = 0; i < 4; ++i)
			m_Rows[i] = i_other.m_Rows[i];

		return *this;
	}

	inline Matrix4& Matrix4::operator+=(const Matrix4 & i_rhs)
	{
		for (int i = 0; i < 4; ++i)
			_mm_add_ps(m_Rows[i], i_rhs.m_Rows[i]);

		return *this;
	}

	inline Matrix4& Matrix4::operator-=(const Matrix4 & i_rhs)
	{
		for (int i = 0; i < 4; ++i)
			_mm_sub_ps(m_Rows[i], i_rhs.m_Rows[i]);

		return *this;
	}

	inline Matrix4& Matrix4::operator*=(const float i_val)
	{
		for (int i = 0; i < 4; ++i)
			_mm_mul_ps(m_Rows[i], _mm_set_ps1(i_val));

		return *this;
	}

	inline Matrix4& Matrix4::operator/=(const float i_val)
	{
		for (int i = 0; i < 4; ++i)
			_mm_div_ps(m_Rows[i], _mm_set_ps1(i_val));

		return *this;
	}

	inline Matrix4& Matrix4::operator-()
	{
		for (int i = 0; i < 4; ++i)
			_mm_div_ps(m_Rows[i], _mm_set_ps1(-1.0f));

		return *this;
	}

	inline Vector4& Matrix4::operator[](int i) const
	{
		return Vector4(m_elements[i * 4], m_elements[i * 4 + 1], m_elements[i * 4 + 2], m_elements[i * 4 + 3]);
	}

	inline Vector3 Matrix4::operator*(const Vector3 & i_Vector)
	{
		__m128 vec = _mm_set_ps(1.0f, i_Vector.z(), i_Vector.y(), i_Vector.x());

		return Vector3(_mm_cvtss_f32(_mm_dp_ps(vec, m_Rows[0], 0xF1)),
			_mm_cvtss_f32(_mm_dp_ps(vec, m_Rows[1], 0xF1)),
			_mm_cvtss_f32(_mm_dp_ps(vec, m_Rows[2], 0xF1)));		
	}

	inline Matrix4 operator+(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			result.m_Rows[i] = _mm_add_ps(i_lhs.m_Rows[i], i_rhs.m_Rows[i]);
		}

		return result;
	}

	inline Matrix4 operator-(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			result.m_Rows[i] = _mm_sub_ps(i_lhs.m_Rows[i], i_rhs.m_Rows[i]);
		}

		return result;
	}

	inline Matrix4 operator*(const Matrix4 & i_lhs, const float i_val)
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			result.m_Rows[i] = _mm_mul_ps(i_lhs.m_Rows[i], _mm_set_ps1(i_val));
		}

		return result;
	}

	inline Matrix4 operator*(const float i_val, const Matrix4 & i_rhs)
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			result.m_Rows[i] = _mm_mul_ps(i_rhs.m_Rows[i], _mm_set_ps1(i_val));
		}

		return result;
	}

	inline Matrix4 operator*(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		float elements[16];
		Matrix4 rt = i_rhs.Transpose();

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				elements[i * 4 + j] = _mm_cvtss_f32(_mm_dp_ps(i_lhs.m_Rows[i], rt.m_Rows[j], 0xF1));
			}
		}

		Matrix4 matrix(elements);
		return matrix;
	}

	inline Matrix4 operator/(const Matrix4 & i_lhs, const float i_val)
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			result.m_Rows[i] = _mm_div_ps(i_lhs.m_Rows[i], _mm_set_ps1(i_val));
		}

		return result;
	}

	inline bool operator==(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		return IsEqual(i_lhs, i_rhs);
	}

	inline bool operator!=(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		return !IsEqual(i_lhs, i_rhs);
	}

	inline bool IsEqual(const Matrix4 & i_lhs, const Matrix4 & i_rhs)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i_lhs[i] != i_rhs[i])
				return false;
		}
		return true;
	}
}