#pragma once
#include<math.h>
#include "Math/MathGlobal.h"

namespace Engine
{
	class Vector4
	{
	public:
		
		Vector4();
		Vector4(float i_x, float i_y, float i_z, float i_w);
		Vector4(const Vector4 & i_other);

		Vector4 & operator=(const Vector4 & i_other);

		Vector4 & operator+=(const Vector4 & i_rhs);
		Vector4 & operator-=(const Vector4 & i_rhs);
		Vector4 & operator*=(const float i_val);
		Vector4 & operator/=(const float i_val);

		Vector4 & operator-();		

		float x() const;
		float y() const;
		float z() const;
		float w() const;

		void x(float i_x);
		void y(float i_y);
		void z(float i_z);
		void w(float i_w);

		Vector4 Normalize();
		float Magnitude();
		static const Vector4 Zero;
		static const Vector4 One;
	
	private:
		float m_x, m_y, m_z, m_w;

	};

	Vector4 operator+(const Vector4 & i_lhs, const Vector4 & i_rhs);
	Vector4 operator-(const Vector4 & i_lhs, const Vector4 & i_rhs);

	Vector4 operator*(const Vector4 & i_lhs, const float i_val);
	Vector4 operator*(const float & i_val, const Vector4 & i_rhs);
	Vector4 operator/(const Vector4 & i_lhs, const float i_val);

	bool operator==(const Vector4 & i_lhs, const Vector4 & i_rhs);
	bool operator!=(const Vector4 & i_lhs, const Vector4 & i_rhs);

	float Dot(const Vector4 & i_lhs, const Vector4 & i_rhs);
	Vector4 Cross(const Vector4 & i_lhs, const Vector4 & i_rhs);

}

#include "Math/Vactor4_inl.h"

