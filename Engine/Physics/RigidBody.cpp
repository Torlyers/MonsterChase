#include "RigidBody.h"

namespace Engine {

	RigidBody::RigidBody() :
		m_Mass(1.0f),
		m_DragFactor(0.3f),
		m_Collider(nullptr)
	{

	}

	RigidBody::RigidBody(SharedPointer<GameObject> & go) :
		m_Mass(1.0f),
		m_DragFactor(0.3f),
		m_Collider(nullptr)
	{
		m_GameObject = go;
		if (m_GameObject->GetCollider() == nullptr)
		{
			BoxCollider2D* collider = new BoxCollider2D(go);
			m_Collider = collider;
			go->SetCollider(collider);
		}
		else
		{
			m_Collider = go->GetCollider();
		}
	}


	RigidBody::~RigidBody()
	{
		
	}

	void RigidBody::Run(float DeltaTime)
	{		
		m_DragForce = m_Velocity * m_DragFactor * (-1.0f);
		m_TotalForce = m_Force + m_DragForce;		
		
		m_Acceleration = m_TotalForce / m_Mass;
		Vector2 VeloCity_new = m_Velocity + m_Acceleration * DeltaTime;
		
		m_GameObject->SetPosition(m_GameObject->GetPosition() + (m_Velocity + VeloCity_new) / 2.0f * DeltaTime);
		m_Velocity = VeloCity_new;
		m_Speed = m_Velocity.Magnitude();

		m_Force = Vector2(0, 0);
	}

	void RigidBody::AddForce(Vector2 i_Force)
	{
		m_Force = i_Force;
	}

}