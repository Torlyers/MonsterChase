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
		//m_Mutex = new SingleWriterMutipleReader();
	}

	void PhysicsManager::Run(float i_FrameTime_ms)
	{
		for (int i = 0; i < RigidBodies.size(); ++i) 
		{
			RigidBodies[i]->Run(i_FrameTime_ms);
		}
	}

	void PhysicsManager::AddRigidBody(shared_ptr<GameObject> go)
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

	}
}
