#include "GameObject.h"
#include "Physics\RigidBody.h"
#include "Colliders\BoxCollider2D.h"
#include "Render\Renderer.h"
#include "Colliders\ColliderManager.h"
#include "Physics\PhysicsManager.h"
#include "Render\RenderManager.h"

namespace Engine {

	GameObject::GameObject():
		m_RigidBody(nullptr),
		m_Collider(nullptr),
		m_Renderer(nullptr),
		m_Rotation(0.0f)
	{
		m_Name = "sprite";
		m_Position.x(0.0f);
		m_Position.y(0.0f);
	}

	GameObject::GameObject(Vector2 i_Position):
		m_RigidBody(nullptr),
		m_Collider(nullptr),
		m_Renderer(nullptr),
		m_Rotation(0.0f),
		m_Position(i_Position)
	{
		

	}

	GameObject::GameObject(const GameObject & sprite)
	{
		m_Name = sprite.m_Name;
		m_Position = sprite.m_Position;
		m_RigidBody = sprite.m_RigidBody;
		m_Collider = sprite.m_Collider;
		m_Rotation = sprite.m_Rotation;

	}

	GameObject::GameObject(GameObject && sprite)
	{
		const char* temp = sprite.m_Name;
		this->m_Name = temp;
		sprite.m_Name = this->m_Name;

		//this->m_Name = sprite.m_Name;
		this->m_Position = sprite.m_Position;
	}

	GameObject& GameObject::operator=(const GameObject& sprite)
	{
		m_Name = sprite.m_Name;
		m_Position = sprite.m_Position;
		m_RigidBody = sprite.m_RigidBody;
		m_Collider = sprite.m_Collider;
		m_Rotation = sprite.m_Rotation;

		return *this;
	}

	GameObject& GameObject::operator=(GameObject && sprite)
	{
		const char* temp = sprite.m_Name;
		this->m_Name = temp;
		sprite.m_Name = this->m_Name;
		this->m_Position = sprite.m_Position;
		
		return *this;
	}

	GameObject::~GameObject()
	{
		
	}

	void GameObject::Init()
	{

	}

	void GameObject::Run()
	{

	}

	void GameObject::Shutdown()
	{

		if (m_Renderer != nullptr)
		{
			m_Renderer->ShutDown();
			delete m_Renderer;
		}

		if (m_RigidBody != nullptr)
		{
			delete m_RigidBody;

		}

		if (m_Collider != nullptr)
		{
			delete m_Collider;
		}


	}

}
