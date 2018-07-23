#pragma once
#include "Render/Renderer.h"


namespace Engine
{
	inline weak_ptr<GameObject> Renderer::GetGameObject()
	{
		return m_GameObject;
	}

	inline void Renderer::SetGameObject(shared_ptr<GameObject> i_GameObject)
	{
		m_GameObject = i_GameObject;
	}



}