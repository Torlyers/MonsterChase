#include "PhysicsManager.h"
#include "Colliders/ColliderManager.h"

namespace Engine {

	PhysicsManager::PhysicsManager()
	{

	}

	PhysicsManager::~PhysicsManager()
	{
		
	}

	void PhysicsManager::Init()
	{

	}

	void PhysicsManager::Run(float i_FrameTime_ms)
	{
		for (u_int i = 0; i < RigidBodies.size(); ++i) 
		{
			RigidBodies[i]->Run(i_FrameTime_ms);
		}
	}

	void PhysicsManager::AddRigidBody(SharedPointer<GameObject> go)
	{
		if (go->GetRigidBody() == nullptr) 
		{			
			RigidBody* newComponent = new RigidBody(go);			
			go->SetRigidBody(newComponent);

			RigidBodies.push_back(newComponent);
		}
	}

	void PhysicsManager::Shutdown()
	{
		DeleteInstance();
	}
}
