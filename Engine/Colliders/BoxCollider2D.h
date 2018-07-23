#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "GameObject/gameobject.h"
#include <memory>

namespace Engine
{

	struct AABB
	{
		Vector3 Center;
		Vector3 Extents;
		AABB() {}
		AABB(const Vector3 & i_Center, const Vector3 & i_Extents)
		{
			Center = i_Center;
			Extents = i_Extents;
		}
	};

	class BoxCollider2D
	{
	private:

		Matrix4 m_Model;
		AABB m_AABB;		

		weak_ptr<GameObject> m_GameObject;

	public:
		BoxCollider2D();
		BoxCollider2D(shared_ptr<GameObject> go);
		~BoxCollider2D();

		Matrix4 GetModelMatrix();

		AABB GetAABB();
		void SetAABB(const Vector3 & i_Center, const Vector3 & i_Extent);
		void SetAABB(const AABB & i_AABB);
		void Update();

		void ResetMatrix();

		weak_ptr<GameObject> GetGameObject();	

		bool CheckCollision(const AABB & i_AABB, Vector2 i_Velocity, float & o_Time, Vector3 & o_Axis);
		
	};
}

#include "Colliders/BoxCollider2D_inl.h"
