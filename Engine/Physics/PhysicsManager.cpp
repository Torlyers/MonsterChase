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
<<<<<<< HEAD

=======
		m_Mutex = new SingleWriterMutipleReader();
>>>>>>> parent of 56cd134... debug
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

<<<<<<< HEAD
			RigidBodies.push_back(newComponent);
=======
			mutex1.Acquire();

			//m_Mutex->WriteLock();
			RigidBodies.push_back(newComponent);
			//m_Mutex->ReleaseWriteLock();
	
			mutex1.Release();
>>>>>>> parent of 56cd134... debug
		}
	}

	void PhysicsManager::Shutdown()
	{
<<<<<<< HEAD
		DeleteInstance();
=======
		if (m_Mutex)
			delete m_Mutex;

		if(m_Instance != nullptr)
			delete m_Instance;
>>>>>>> parent of 56cd134... debug
	}
}
