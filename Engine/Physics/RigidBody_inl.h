#pragma once
#include "Physics/RigidBody.h"

namespace Engine
{
	inline float RigidBody::GetMass()
	{
		return m_Mass;
	}

	inline void RigidBody::SetMass(float i_Mass)
	{
		m_Mass = i_Mass;
	}

	inline float RigidBody::GetDragFactor()
	{
		return m_DragFactor;
	}

	inline void RigidBody::SetDragFactor(float i_Factor)
	{
		m_DragFactor = i_Factor;
	}

	inline Vector2 RigidBody::GetAcceleration()
	{
		return m_Acceleration;
	}

	inline Vector2 RigidBody::GetVelocity()
	{
		return m_Velocity;
	}

	inline void RigidBody::SetVelocity(Vector2 i_Velocity)
	{
		m_Velocity = i_Velocity;
	}

	inline float RigidBody::GetSpeed()
	{
		return m_Speed;
	}
}