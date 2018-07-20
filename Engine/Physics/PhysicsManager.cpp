#include "PhysicsManager.h"
#include "Colliders/ColliderManager.h"

namespace Engine {

	PhysicsManager* PhysicsManager::m_Instance = nullptr;

	PhysicsManager* PhysicsManager::Instance()
	{
		if (!m_Instance)
			m_Instance = new PhysicsManager();
		return m_Instance;
	}

	PhysicsManager::PhysicsManager()
	{

	}

	PhysicsManager::~PhysicsManager()
	{
		
	}

	void PhysicsManager::Init()
	{
		m_Mutex = new SingleWriterMutipleReader();
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

			mutex1.Acquire();

			//m_Mutex->WriteLock();
			RigidBodies.push_back(newComponent);
			//m_Mutex->ReleaseWriteLock();
	
			mutex1.Release();
		}
	}

	void PhysicsManager::Shutdown()
	{
		if (m_Mutex)
			delete m_Mutex;

		if(m_Instance != nullptr)
			delete m_Instance;
	}
}
