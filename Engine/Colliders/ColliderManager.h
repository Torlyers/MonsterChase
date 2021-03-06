#pragma once
#include <vector>

#include "Colliders/BoxCollider2D.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Base/Singleton.h"

namespace Engine
{

	class CollisionPair
	{
	public:
		BoxCollider2D* col1;
		BoxCollider2D* col2;
		float colTime;
		Vector3 colNormal;

		CollisionPair() :
			col1(nullptr), col2(nullptr) {}
	};

	class ColliderManager : public Singleton<ColliderManager>
	{
	private:

	public:
		ColliderManager();
		~ColliderManager();		

		//For engine loop
		void Init();
		void Run();
		void Shutdown();

		//All the rigidBodies in the game
		std::vector<BoxCollider2D*> Colliders;

		//For GameObjects to add rigidBody
		void AddCollider(shared_ptr<GameObject> go);

		void DetectCollision();
		bool CheckCollision(BoxCollider2D* i_Col1, BoxCollider2D* i_Col2, float & o_Time, Vector3 & o_Axis);
		void HandleCollision(const CollisionPair & i_Pair);

	};

}

#include "Colliders/ColliderManager_inl.h"



