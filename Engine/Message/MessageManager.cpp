#include "MessageManager.h"

namespace Engine
{
	MessageManager::MessageManager()
	{
	}


	MessageManager::~MessageManager()
	{
	}

	void MessageManager::Init()
	{

	}

	void MessageManager::Run()
	{

	}

	void MessageManager::ShutDown()
	{
		std::unordered_map<const char*, Delegate<>>::iterator itor1 = m_DelegateMap.begin();
		while (itor1 != m_DelegateMap.end())
		{
			m_DelegateMap.erase(itor1++);
		}
		m_DelegateMap.clear();

		std::unordered_map<const char*, MultiCastDelegate<>>::iterator itor2 = m_MultiDelegateMap.begin();
		while (itor2 != m_MultiDelegateMap.end())
		{
			m_MultiDelegateMap.erase(itor2++);
		}
		m_MultiDelegateMap.clear();
	}
}
