#include "Colliders\ColliderManager.h"
#include "Physics\RigidBody.h"
#include "DebugTool\Debug.h"
#include "Time\TimeManager.h"
#include "Physics\PhysicsManager.h"
#include "Math\MathGlobal.h"
#include "Profiling\Profiler.h"

namespace Engine
{
	
	ColliderManager::ColliderManager()
	{
		
	}

	ColliderManager::~ColliderManager()
	{

	}

	void ColliderManager::Init()
	{

	}

	void ColliderManager::Run()
	{	
		for (auto collider : Colliders)
			collider->Update();

		if (Colliders.size() > 1)
			DetectCollision();
		
	}

	void ColliderManager::Shutdown()
	{

	}

	void ColliderManager::AddCollider(shared_ptr<GameObject> go)
	{
		if (go->GetCollider() == nullptr)
		{			
			BoxCollider2D* collider = new BoxCollider2D(go);			
			go->SetCollider(collider);

			Colliders.push_back(collider);
		}		
	}

	void ColliderManager::DetectCollision()
	{
		float remainTime = TimeManager::Instance()->GetFrameDeltaTime();
		CollisionPair EarliestPair;
		EarliestPair.colTime = remainTime;

		while (remainTime >= 0.0f)
		{
			float colTime = remainTime;
			Vector3 colNormal;
			bool isCol = false;

			for (int i = 0; i < Colliders.size() - 1; ++i)
			{
				for (int j = i + 1; j < Colliders.size(); ++j)
				{
					if (CheckCollision(Colliders[i], Colliders[j], colTime, colNormal))
					{
						isCol = true;
						if (colTime < EarliestPair.colTime)
						{
							EarliestPair.col1 = Colliders[i];
							EarliestPair.col2 = Colliders[j];
							EarliestPair.colTime = colTime;
							EarliestPair.colNormal = colNormal;
						}
					}
				}
			}

			if (isCol)
			{
				HandleCollision(EarliestPair);
				remainTime -= EarliestPair.colTime;
				PhysicsManager::Instance()->Run(EarliestPair.colTime);
			}
			else
			{
				PhysicsManager::Instance()->Run(remainTime);
				break;
			}
		}
	}

	bool ColliderManager::CheckCollision(BoxCollider2D* i_Col1, BoxCollider2D* i_Col2, float & o_Time, Vector3 & o_Axis)
	{	
		
		
		PROFILE_UNSCOPED("Test Profile");
		//Calculate Relative position in the other coordinate
		Matrix4 Coord1To2 = i_Col2->GetModelMatrix().Inversion() * i_Col1->GetModelMatrix();
		Matrix4 Coord2To1 = i_Col1->GetModelMatrix().Inversion() * i_Col2->GetModelMatrix();

		AABB AABB1InCoord2;
		AABB1InCoord2.Center = Coord1To2 * i_Col1->GetAABB().Center;
		AABB1InCoord2.Extents = i_Col1->GetAABB().Extents;

		AABB AABB2InCoord1;
		AABB2InCoord1.Center = Coord2To1 * i_Col2->GetAABB().Center;
		AABB2InCoord1.Extents = i_Col2->GetAABB().Extents;

		//Calculate Relative Velocity in the other coordinate
		Vector2 Velocity1 = i_Col1->GetGameObject().lock()->GetRigidBody()->GetVelocity();
		Vector2 Velocity2 = i_Col2->GetGameObject().lock()->GetRigidBody()->GetVelocity();
		Vector2 RelaVel1InCoord2 = Velocity1 - Velocity2;
		Vector2 RelaVel2InCoord1 = Velocity2 - Velocity1;

		//Check collision twice
		bool IsCol = i_Col2->CheckCollision(AABB1InCoord2, RelaVel1InCoord2, o_Time, o_Axis);
		
		/*if (IsCol)
			o_Axis = (Coord1To2 * o_Axis).Normalize();	*/				 

		return IsCol;
	}

	void ColliderManager::HandleCollision(const CollisionPair & i_Pair)
	{

		RigidBody* r1 = i_Pair.col1->GetGameObject().lock()->GetRigidBody();
		RigidBody* r2 = i_Pair.col2->GetGameObject().lock()->GetRigidBody();

		if (r1 != nullptr && r2 != nullptr)
		{
			//for pong use
			Vector2 v = r1->GetVelocity();
			if (IsFloatZero(i_Pair.colNormal.x()))
			{
				r1->SetVelocity(Vector2(v.x(), -v.y()));
			}
			else if(IsFloatZero(i_Pair.colNormal.y()))
			{
				r1->SetVelocity(Vector2(-v.x(), v.y()));
			}

			////Calculate speed
			//float mass1 = r1->GetMass();
			//float mass2 = r2->GetMass();
			//float s1 = r1->GetSpeed();
			//float s2 = r2->GetSpeed();
			//float speed1 = (r1->GetMass() - r2->GetMass()) / (r1->GetMass() + r2->GetMass()) * r1->GetSpeed() +
			//	           (2.0f * r2->GetMass()) / (r1->GetMass() + r2->GetMass()) * r2->GetSpeed();

			//float speed2 = (r2->GetMass() - r1->GetMass()) / (r1->GetMass() + r2->GetMass()) * r2->GetSpeed() +
			//	           (2.0f * r1->GetMass()) / (r1->GetMass() + r2->GetMass()) * r1->GetSpeed();

			////Calculate Normalized velocity vector
			//Vector3 Vel1 = Vector3(r1->GetVelocity().Normalize(), 0.0f);
			//Vector3 Vel2 = Vector3(r2->GetVelocity().Normalize(), 0.0f);

			//if (IsFloatZero(r1->GetSpeed()))
			//	Vel1 = Vel2;

			//if (IsFloatZero(r2->GetSpeed()))
			//	Vel2 = Vel1;

			//if(Dot(Vel1, -1.0 * i_Pair.colNormal) > 0)
			//{
			//	Vel1 = (2.0f * i_Pair.colNormal + Vel1).Normalize() * abs(speed1);
			//}
			//else
			//{
			//	Vel1 = (2.0f * i_Pair.colNormal - Vel1).Normalize() * abs(speed1);
			//}

			//if (Dot(Vel2, i_Pair.colNormal) > 0)
			//{
			//	Vel2 = (-2.0f * i_Pair.colNormal + Vel2).Normalize() * abs(speed2);
			//}
			//else
			//{
			//	Vel2 = (-2.0f * i_Pair.colNormal - Vel2).Normalize() * abs(speed2);
			//}

			//r1->SetVelocity(Vector2(Vel1.x(), Vel1.y()));
			//r2->SetVelocity(Vector2(Vel2.x(), Vel2.y()));

		}
	}
}