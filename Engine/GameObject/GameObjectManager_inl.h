#pragma once
#include "GameObject/GameObjectManager.h"

namespace Engine
{
	vector<shared_ptr<GameObject>>& GameObjectManager::GetObjects()
	{
		return m_GameObjects;
	}

}
