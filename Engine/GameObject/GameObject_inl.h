#pragma once
#include "GameObject/GameObject.h"

namespace Engine
{
	inline Vector2 GameObject::GetPosition()
	{
		return m_Position;
	}

	inline void GameObject::SetPosition(Vector2 position)
	{ 
		m_Position = position;
	}

	inline void GameObject::SetPosition(float i_x, float i_y)
	{
		m_Position.x(i_x);
		m_Position.x(i_y);
	}

	inline float GameObject::GetRotation()
	{
		return m_Rotation;
	}

	inline void GameObject::SetRotation(float i_Rot)
	{
		m_Rotation = i_Rot;
	}

	inline const char* GameObject::GetName() const
	{
		return m_Name;
	}

	inline void GameObject::SetName(const char* name)
	{
		m_Name = name;
	}	

	inline RigidBody* GameObject::GetRigidBody()
	{
		return m_RigidBody;
	}

	inline void GameObject::SetRigidBody(RigidBody* i_RigidBody)
	{
		m_RigidBody = i_RigidBody;
	}

	inline BoxCollider2D* GameObject::GetCollider()
	{
		return m_Collider;
	}

	inline void GameObject::SetCollider(BoxCollider2D* i_Collider)
	{
		m_Collider = i_Collider;
	}

	inline Renderer* GameObject::GetRenderer()
	{
		return m_Renderer;
	}

	inline void GameObject::SetRenderer(Renderer* i_Renderer)
	{
		m_Renderer = i_Renderer;
	}
}