#pragma once

#include "GameObject/GameObject.h"
#include "SmartPointer/WeakPointer.h"
#include "Colliders/BoxCollider2D.h"

namespace Engine {

	class RigidBody
	{
	
	private:

		WeakPointer<GameObject> m_GameObject;
		BoxCollider2D* m_Collider;

		float m_Mass;

		Vector2 m_Force;
		Vector2 m_DragForce;
		Vector2 m_TotalForce;

		float m_DragFactor;

		Vector2 m_Acceleration;

		Vector2 m_Velocity;

		float m_Speed;

	public:

		RigidBody();
		RigidBody(SharedPointer<GameObject> & go);
		~RigidBody();

		friend class BoxCollider2D;
		
		float GetMass();
		void SetMass(float i_Mass);

		float GetDragFactor();
		void SetDragFactor(float i_Factor);

		Vector2 GetAcceleration();
		//void SetAcceleration(Vector2 i_Acceleration);

		Vector2 GetVelocity();
		void SetVelocity(Vector2 i_Velocity);
		
		float GetSpeed();
		//void SetSpeed();




		void Run(float DeltaTime);

		void AddForce(Vector2 i_Force);
		
	};

}

#include "Physics/RigidBody_inl.h"

