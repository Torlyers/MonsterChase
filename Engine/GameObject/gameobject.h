#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <memory>

#include "File\File.h"
#include "Math\Vector3.h"

using namespace std;

namespace Engine {

	//component declaration
	class RigidBody;
	class BoxCollider2D;
	class Renderer;	 

	class GameObject
	{
	protected:

		string  m_Name;
		Vector2 m_Position;
		float   m_Rotation;
		

		RigidBody* m_RigidBody;
		BoxCollider2D* m_Collider;
		Renderer* m_Renderer;

	public:

		GameObject();
		GameObject(Vector2 i_Position);
		GameObject(const GameObject & sprite);
		GameObject(GameObject && sprite);

		GameObject& operator=(const GameObject& sprite);
		GameObject& operator=(GameObject&& sprite);

		string GetName();
		void SetName(const string& name);
		
		Vector2 GetPosition();
		void SetPosition(Vector2 position);
		void SetPosition(float i_x, float i_y);	

		float GetRotation();
		void SetRotation(float i_Rot);

		RigidBody* GetRigidBody();
		void SetRigidBody(RigidBody* i_RigidBody);

		BoxCollider2D* GetCollider();
		void SetCollider(BoxCollider2D* i_Collider);

		Renderer* GetRenderer();
		void SetRenderer(Renderer* i_Renderer);
		
		void Init();
		void Run();
		void Shutdown();

		virtual ~GameObject();

	};

}

#include "GameObject/GameObject_inl.h"