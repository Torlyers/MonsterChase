#pragma once
#include <math.h>
#include "Math/MathGlobal.h"
#include "Math/Vector2.h"

namespace Engine
{

	__declspec(align(16))
	class Vector3
	{
	public:

		Vector3();
		Vector3(float i_x, float i_y, float i_z);
		Vector3(__m128 i_Vec);
		Vector3(Vector2 i_Vec, float i_z);
		Vector3(const Vector3 & i_other);

		Vector3 & operator=(const Vector3 & i_other);

		Vector3 & operator+=(const Vector3 & i_rhs);
		Vector3 & operator-=(const Vector3 & i_rhs);
		Vector3 & operator*=(const float i_val);
		Vector3 & operator/=(const float i_val);

		Vector3 & operator-();

		float x() const;
		float y() const;
		float z() const;

		__m128 Vec() const;

		void x(float i_x);
		void y(float i_y);
		void z(float i_z);

		Vector3 Normalize();
		float Magnitude();
		static const Vector3 Zero;
		static const Vector3 One;
			

	private:
		union 
		{
			__m128 m_Vec;
			struct
			{
				float m_x, m_y, m_z, m_w;
			};
		};
		

	};

	Vector3 operator+(const Vector3 & i_lhs, const Vector3 & i_rhs);
	Vector3 operator-(const Vector3 & i_lhs, const Vector3 & i_rhs);

	Vector3 operator*(const Vector3 & i_lhs, const float i_val);
	Vector3 operator*(const float & i_val, const Vector3 & i_rhs);
	Vector3 operator/(const Vector3 & i_lhs, const float i_val);

	bool operator==(const Vector3 & i_lhs, const Vector3 & i_rhs);
	bool operator!=(const Vector3 & i_lhs, const Vector3 & i_rhs);

	float Dot(const Vector3 & i_lhs, const Vector3 & i_rhs);
	Vector3 Cross(const Vector3 & i_lhs, const Vector3 & i_rhs);



}

#include "Math/Vector3_inl.h"