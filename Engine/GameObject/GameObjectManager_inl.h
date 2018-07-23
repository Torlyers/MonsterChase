#pragma once
#include "GameObject/GameObjectManager.h"

namespace Engine
{
	vector<SharedPointer<GameObject>>& GameObjectManager::GetObjects()
	{
		return m_GameObjects;
	}

}
