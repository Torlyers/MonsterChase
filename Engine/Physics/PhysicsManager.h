#pragma once
#include <vector>
#include <memory>
#include "Physics/RigidBody.h"
#include "Base/Singleton.h"

namespace Engine
{
	class PhysicsManager : public Singleton<PhysicsManager>
	{
	private:
	
	public:

		PhysicsManager();
		~PhysicsManager();

		//For engine loop
		void Init();
		void Run(float i_FrameTime_ms);
		void Shutdown();

		//All the rigidBodies in the game
		std::vector<RigidBody*> RigidBodies;

		//The sum of forces from outside
		Vector2 InputForce;

		//For GameObjects to add rigidBody
		void AddRigidBody(shared_ptr<GameObject> go);
	};
}

#include "PhysicsManager_inl.h"

