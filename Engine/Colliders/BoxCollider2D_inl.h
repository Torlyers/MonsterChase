#pragma once
#include "BoxCollider2D.h"

namespace Engine 
{


	inline Matrix4 BoxCollider2D::GetModelMatrix()
	{
		return m_Model;
	}

	inline AABB BoxCollider2D::GetAABB()
	{
		return m_AABB;
	}

	inline void BoxCollider2D::SetAABB(const Vector3 & i_Center, const Vector3 & i_Extent)
	{
		m_AABB.Center = i_Center;
		m_AABB.Extents = i_Extent;
	}

	inline void BoxCollider2D::SetAABB(const AABB & i_AABB)
	{
		m_AABB = i_AABB;
	}

	inline weak_ptr<GameObject> BoxCollider2D::GetGameObject()
	{
		return m_GameObject;
	}

	
}