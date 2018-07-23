#include "BoxCollider2D.h"
#include "Time/TimeManager.h"

namespace Engine
{

	BoxCollider2D::BoxCollider2D()
	{
		ResetMatrix();
	}

	BoxCollider2D::BoxCollider2D(shared_ptr<GameObject> go)
	{
		ResetMatrix();
		m_GameObject = go;
	}


	BoxCollider2D::~BoxCollider2D()
	{

	}

	void BoxCollider2D::ResetMatrix()
	{		
		if (m_GameObject.lock().get() != nullptr)
		{
			//Vector3 axis(0.0f, 0.0f, 1.0f);//z
			//float angle = GetGameObject()->GetRotation();
			//m_Model = m_Model.Rotate(axis, angle);
			
			Vector3 translation(GetGameObject().lock()->GetPosition(), 0.0f);
 			m_Model = m_Model.Translate(translation);			
		}
	}

	void BoxCollider2D::Update()
	{
		ResetMatrix();
	}

	bool BoxCollider2D::CheckCollision(const AABB & i_AABB, Vector2 i_Velocity, float & o_Time, Vector3 & o_Axis)
	{
		double dt = TimeManager::Instance()->GetFrameDeltaTime();
		
		float m_LBorder = m_AABB.Center.x() - m_AABB.Extents.x();
		float m_RBorder = m_AABB.Center.x() + m_AABB.Extents.x();
		float m_BBorder = m_AABB.Center.y() - m_AABB.Extents.y();
		float m_TBorder = m_AABB.Center.y() + m_AABB.Extents.y();

		float i_LBorder = i_AABB.Center.x() - i_AABB.Extents.x();
		float i_RBorder = i_AABB.Center.x() + i_AABB.Extents.x();
		float i_BBorder = i_AABB.Center.y() - i_AABB.Extents.y();
		float i_TBorder = i_AABB.Center.y() + i_AABB.Extents.y();

		float topenX, tcloseX, topenY, tcloseY;
		topenX = tcloseX = topenX = topenY = 0.0f;

		//relatively static and not collide
		if (i_Velocity.Magnitude() <= 0.0001f && (m_LBorder >= i_RBorder || m_RBorder <= i_LBorder) && (m_BBorder >= i_TBorder || m_TBorder <= i_BBorder))
			return false;

		if (i_Velocity.x() > 0)
		{
			tcloseX = (m_LBorder - i_RBorder) / i_Velocity.x();
			topenX = (m_RBorder - i_LBorder) / i_Velocity.x();
		}
		else if(i_Velocity.x() <= 0)
		{
			tcloseX = (m_RBorder - i_LBorder) / i_Velocity.x();
			topenX = (m_LBorder - i_RBorder) / i_Velocity.x();
		}
		else
		{

		}

		if (topenX < 0 || tcloseX > dt)
			return false;

		

		if (i_Velocity.y() > 0)
		{
			tcloseY = (m_BBorder - i_TBorder) / i_Velocity.y();
			topenY = (m_TBorder - i_BBorder) / i_Velocity.y();
		}
		else if(i_Velocity.y() <= 0)
		{
			tcloseY = (m_TBorder - i_BBorder) / i_Velocity.y();
			topenY = (m_BBorder - i_TBorder) / i_Velocity.y();
		}
		else
		{
			
		}

		if (topenY < 0 || tcloseY > dt)
			return false;

		if (max(tcloseX, tcloseY) >= min(topenX, topenY))
			return false;

		if (tcloseX > tcloseY)
			if (i_Velocity.x() >= 0)
				o_Axis = Vector3(-1.0f, 0.0f, 0.0f);//collide at left
			else
				o_Axis = Vector3(1.0f, 0.0f, 0.0f);//collide at right
		else
			if (i_Velocity.y() >= 0)
				o_Axis = Vector3(0.0f, -1.0f, 0.0f);//collide at top
			else
				o_Axis = Vector3(0.0f, 1.0f, 0.0f);//collide at bottom
		
		o_Time = max(tcloseY, tcloseX);

		return true;
	}
}