#pragma once

#include<math.h>

#include"Math/Vector4.h"
#include"Math/Vector3.h"
#include"math/MathGlobal.h"

namespace Engine
{
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(float i_array[16]);
		Matrix4(const Matrix4 & i_other);		
		Matrix4& operator=(const Matrix4 & i_other);

		Matrix4& operator+=(const Matrix4 & i_rhs);
		Matrix4& operator-=(const Matrix4 & i_rhs);
		Matrix4& operator*=(const float i_val);
		Matrix4& operator/=(const float i_val);
		Matrix4& operator-();		

		Vector4& operator[](int i) const;

		Vector3 operator*(const Vector3 & i_Vector);

		Matrix4 Transpose() const;
		Matrix4 Inversion() const;
		Matrix4 Translate(const Vector3 & i_Vector);
		//rotate matrix
		Matrix4 Rotate(const Vector3 & i_Vector, const float i_Angle);
		//Eular angle
		Matrix4 Rotate(const Vector3 & i_Eular);
		Matrix4 Scale(const Vector3 & i_Vector);

		friend Matrix4 operator+(const Matrix4 & i_lhs, const Matrix4 & i_rhs);
		friend Matrix4 operator-(const Matrix4 & i_lhs, const Matrix4 & i_rhs);
		friend Matrix4 operator*(const Matrix4 & i_lhs, const float i_val);
		friend Matrix4 operator*(const float i_val, const Matrix4 & i_rhs);
		friend Matrix4 operator*(const Matrix4 & i_lhs, const Matrix4 & i_rhs);
		friend Matrix4 operator/(const Matrix4 & i_lhs, const float i_val);

		friend bool operator==(const Matrix4 & i_lhs, const Matrix4 & i_rhs);
		friend bool operator!=(const Matrix4 & i_lhs, const Matrix4 & i_rhs);
		friend bool IsEqual(const Matrix4 & i_lhs, const Matrix4 & i_rhs);

	private:

		union
		{
			float m_elements[16];
			__m128 m_Rows[4];
		};
		
	};
}

#include"Math/Matrix4_inl.h"