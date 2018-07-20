#pragma once
#include "Math/MathGlobal.h"

namespace Engine
{

class Vector2
{

public:
	
	Vector2();
	Vector2(float i_x, float i_y);
	Vector2(const Vector2& i_other);
	Vector2& operator=(const Vector2& i_other);
	
	Vector2& operator+=(const Vector2& i_rhs);
	Vector2& operator-=(const Vector2& i_rhs);
	Vector2& operator*=(const float i_val);
	Vector2& operator/=(const float i_val);

	Vector2 & operator-();

	float x() const;
	float y() const;

	void x(float i_x);
	void y(float i_y);

	Vector2 Normalize();
	float Magnitude();
	static const Vector2 Zero;
	static const Vector2 One;

private:
	float m_x, m_y;

};

Vector2 operator+(const Vector2 & i_lhs, const Vector2 & i_rhs);
Vector2 operator-(const Vector2 & i_lhs, const Vector2 & i_rhs);

Vector2 operator*(const Vector2 & i_lhs, const float i_val);
Vector2 operator*(const float & i_val, const Vector2 & i_rhs);
Vector2 operator/(const Vector2 & i_lhs, const float i_val);

bool operator==(const Vector2 & i_lhs, const Vector2 & i_rhs);
bool operator!=(const Vector2 & i_lhs, const Vector2 & i_rhs);

float Dot(const Vector2 & i_lhs, const Vector2 & i_rhs);
Vector2 Cross(const Vector2 & i_lhs, const Vector2 & i_rhs);

}

#include "Math/Vector2_inl.h"