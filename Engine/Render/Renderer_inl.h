#pragma once
#include "Render/Renderer.h"


namespace Engine
{
	inline WeakPointer<GameObject> Renderer::GetGameObject()
	{
		return m_GameObject;
	}

	inline void Renderer::SetGameObject(SharedPointer<GameObject> i_GameObject)
	{
		m_GameObject = i_GameObject;
	}



}