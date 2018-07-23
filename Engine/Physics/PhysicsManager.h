#pragma once
#include <vector>
#include "Physics/RigidBody.h"
#include "SmartPointer/SharedPointer.h"
#include "Base/Singleton.h"

namespace Engine
{

	class PhysicsManager final: public Singleton<PhysicsManager> 
	{
	private:
	
	public:
		friend Singleton<PhysicsManager>;

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
		void AddRigidBody(SharedPointer<GameObject> go);
	};

}

#include "PhysicsManager_inl.h"

