#pragma once
#include<vector>
#include"Physics/RigidBody.h"
#include "JobSystem/Thread/Mutex.h"
#include "JobSystem/Thread/SingleWriterMultipleReader.h"
#include <memory>
#include <mutex>

namespace Engine
{

	class PhysicsManager
	{
	private:
		static PhysicsManager* m_Instance;
		//SingleWriterMutipleReader* m_Mutex;

		//Mutex mutex1;
	
	public:

		PhysicsManager();
		~PhysicsManager();

		//For engine loop
		void Init();
		void Run(float i_FrameTime_ms);
		void Shutdown();

		//All the rigidBodies in the game
		std::vector<RigidBody*> RigidBodies;
		
		//Singleton
		static PhysicsManager* Instance();

		//The sum of forces from outside
		Vector2 InputForce;

		//For GameObjects to add rigidBody
		void AddRigidBody(shared_ptr<GameObject> go);
	};

}

#include "PhysicsManager_inl.h"

