#include "Matrix4.h"
#include "DebugTool/Debug.h"

namespace Engine

{
	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 result = *this;

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m_elements[i * 4 + j] = m_elements[j * 4 + i];

		return result;
	}

	Matrix4 Matrix4::Inversion() const
	{
		Matrix4 result = *this;
		//ASSERT(*this != Zero);

		result.m_elements[0] = m_elements[5] * m_elements[10] * m_elements[15] + m_elements[5] * m_elements[10] * m_elements[13] + m_elements[6] * m_elements[9] * m_elements[10] - m_elements[5] * m_elements[11] * m_elements[14] - m_elements[6] * m_elements[9] * m_elements[15] - m_elements[7] * m_elements[10] * m_elements[13];
		result.m_elements[1] = m_elements[1] * m_elements[11] * m_elements[14] + m_elements[2] * m_elements[9] * m_elements[15] + m_elements[3] * m_elements[10] * m_elements[13] - m_elements[1] * m_elements[10] * m_elements[15] - m_elements[2] * m_elements[11] * m_elements[13] - m_elements[3] * m_elements[9] * m_elements[14];
		result.m_elements[2] = m_elements[1] * m_elements[6] * m_elements[15] + m_elements[2] * m_elements[7] * m_elements[13] + m_elements[3] * m_elements[5] * m_elements[14] - m_elements[1] * m_elements[7] * m_elements[14] - m_elements[2] * m_elements[5] * m_elements[15] - m_elements[3] * m_elements[6] * m_elements[13];
		result.m_elements[3] = m_elements[1] * m_elements[7] * m_elements[10] + m_elements[2] * m_elements[5] * m_elements[11] + m_elements[3] * m_elements[6] * m_elements[9] - m_elements[1] * m_elements[6] * m_elements[11] - m_elements[2] * m_elements[7] * m_elements[9] - m_elements[3] * m_elements[5] * m_elements[10];
		result.m_elements[4] = m_elements[1] * m_elements[11] * m_elements[14] + m_elements[6] * m_elements[8] * m_elements[15] + m_elements[7] * m_elements[10] * m_elements[12] - m_elements[4] * m_elements[10] * m_elements[15] - m_elements[6] * m_elements[11] * m_elements[12] - m_elements[7] * m_elements[8] * m_elements[14];
		result.m_elements[5] = m_elements[0] * m_elements[10] * m_elements[15] + m_elements[2] * m_elements[11] * m_elements[12] + m_elements[3] * m_elements[8] * m_elements[14] - m_elements[0] * m_elements[11] * m_elements[14] - m_elements[2] * m_elements[8] * m_elements[15] - m_elements[3] * m_elements[10] * m_elements[12];
		result.m_elements[6] = m_elements[0] * m_elements[7] * m_elements[14] + m_elements[2] * m_elements[4] * m_elements[15] + m_elements[3] * m_elements[6] * m_elements[12] - m_elements[0] * m_elements[6] * m_elements[15] - m_elements[2] * m_elements[7] * m_elements[12] - m_elements[3] * m_elements[4] * m_elements[14];
		result.m_elements[7] = m_elements[0] * m_elements[6] * m_elements[11] + m_elements[2] * m_elements[7] * m_elements[8] + m_elements[3] * m_elements[4] * m_elements[10] - m_elements[0] * m_elements[7] * m_elements[10] - m_elements[2] * m_elements[4] * m_elements[11] - m_elements[3] * m_elements[6] * m_elements[8];
		result.m_elements[8] = m_elements[4] * m_elements[9] * m_elements[15] + m_elements[5] * m_elements[11] * m_elements[12] + m_elements[7] * m_elements[8] * m_elements[13] - m_elements[4] * m_elements[11] * m_elements[13] - m_elements[5] * m_elements[8] * m_elements[15] - m_elements[7] * m_elements[9] * m_elements[12];
		result.m_elements[9] = m_elements[0] * m_elements[11] * m_elements[13] + m_elements[5] * m_elements[8] * m_elements[15] + m_elements[3] * m_elements[9] * m_elements[12] - m_elements[0] * m_elements[9] * m_elements[15] - m_elements[1] * m_elements[11] * m_elements[12] - m_elements[3] * m_elements[4] * m_elements[13];
		result.m_elements[10] = m_elements[0] * m_elements[5] * m_elements[15] + m_elements[1] * m_elements[7] * m_elements[12] + m_elements[3] * m_elements[4] * m_elements[13] - m_elements[0] * m_elements[7] * m_elements[13] - m_elements[1] * m_elements[4] * m_elements[15] - m_elements[3] * m_elements[5] * m_elements[12];
		result.m_elements[11] = m_elements[0] * m_elements[7] * m_elements[9] + m_elements[1] * m_elements[4] * m_elements[10] + m_elements[3] * m_elements[5] * m_elements[8] - m_elements[0] * m_elements[5] * m_elements[11] - m_elements[1] * m_elements[7] * m_elements[8] - m_elements[3] * m_elements[4] * m_elements[9];
		result.m_elements[12] = m_elements[4] * m_elements[10] * m_elements[12] + m_elements[5] * m_elements[8] * m_elements[14] + m_elements[6] * m_elements[9] * m_elements[12] - m_elements[4] * m_elements[9] * m_elements[14] - m_elements[5] * m_elements[10] * m_elements[12] - m_elements[6] * m_elements[8] * m_elements[13];
		result.m_elements[13] = m_elements[0] * m_elements[9] * m_elements[14] + m_elements[1] * m_elements[10] * m_elements[12] + m_elements[2] * m_elements[8] * m_elements[13] - m_elements[0] * m_elements[10] * m_elements[13] - m_elements[1] * m_elements[8] * m_elements[14] - m_elements[2] * m_elements[9] * m_elements[12];
		result.m_elements[14] = m_elements[0] * m_elements[6] * m_elements[13] + m_elements[1] * m_elements[4] * m_elements[14] + m_elements[2] * m_elements[5] * m_elements[12] - m_elements[0] * m_elements[5] * m_elements[14] - m_elements[1] * m_elements[6] * m_elements[12] - m_elements[2] * m_elements[8] * m_elements[13];
		result.m_elements[15] = m_elements[0] * m_elements[5] * m_elements[10] + m_elements[1] * m_elements[6] * m_elements[8] + m_elements[2] * m_elements[4] * m_elements[9] - m_elements[0] * m_elements[6] * m_elements[9] - m_elements[1] * m_elements[4] * m_elements[10] - m_elements[2] * m_elements[5] * m_elements[8];

		return result;
	}

	Matrix4 Matrix4::Translate(const Vector3 & i_Vector)
	{
		Matrix4 result = *this;
		result.m_elements[3] = i_Vector.x();
		result.m_elements[7] = i_Vector.y();
		result.m_elements[11] = i_Vector.z();

		return result;
	}

	Matrix4 Matrix4::Rotate(const Vector3 & i_Vector, const float i_angle)
	{
		Matrix4 result = *this;

		float s = sin(i_angle);
		float c = cos(i_angle);

		result.m_elements[0] = c + pow(i_Vector.x(), 2) * (1 - c);
		result.m_elements[1] = i_Vector.x() * i_Vector.y() * (1 - c) - i_Vector.z() * s;
		result.m_elements[2] = i_Vector.x() * i_Vector.z() * (1 - c) - i_Vector.y() * s;

		result.m_elements[4] = i_Vector.y() * i_Vector.x() * (1 - c) - i_Vector.z() * s;
		result.m_elements[5] = c + pow(i_Vector.y(), 2) * (1 - c);
		result.m_elements[6] = i_Vector.y() * i_Vector.z() * (1 - c) - i_Vector.x() * s;

		result.m_elements[8] = i_Vector.z() * i_Vector.x() * (1 - c) - i_Vector.y() * s;
		result.m_elements[9] = i_Vector.z() * i_Vector.y() * (1 - c) - i_Vector.x() * s;
		result.m_elements[10] = c + pow(i_Vector.z(), 2) * (1 - c);

		return result;
	}
	
	Matrix4 Matrix4::Scale(const Vector3 & i_Vector)
	{
		Matrix4 result = *this;
		result.m_elements[0] = i_Vector.x();
		result.m_elements[5] = i_Vector.y();
		result.m_elements[10] = i_Vector.z();

		return result;
	}	

}