#pragma once

#include <unordered_map>

#include "HashedString/HashedString.h"
#include "Message/Delegate.h"


namespace Engine
{

	class MessageManager
	{
	private:

		static MessageManager* m_Instance;
		std::unordered_map<const char*, Delegate<>> m_DelegateMap;
		std::unordered_map<const char*, MultiCastDelegate<>> m_MultiDelegateMap;

	public:
		MessageManager();
		~MessageManager();

		static MessageManager* Instance();

		void Init();
		void Run();
		void ShutDown();

		template<class ... Params>
		void AddDelegate(const char* i_Name, Delegate<Params ... > & i_Delegate)
		{
			m_DelegateMap[i_Name] = i_Delegate;
		}

		template<class ... Params>
		void AddMultiDelegate(const char* i_Name, Delegate<Params ... > & i_Delegate)
		{
			if (m_MultiDelegateMap.find(i_Name) != m_MultiDelegateMap.end())
			{
				m_MultiDelegateMap[i_Name].AddDelegate(i_Delegate);
			}
			else
			{
				MultiCastDelegate<Params ... > multiDelegate;
				multiDelegate.AddDelegate(i_Delegate);
				m_MultiDelegateMap[i_Name] = multiDelegate;
			}
		}

		template<class ... Params>
		void BroadCastMessage(const char* i_Name, Params ... i_Parameters)
		{
			if (m_DelegateMap.find(i_Name) != m_DelegateMap.end())
				m_DelegateMap[i_Name].ExcuteIfBound(i_Parameters ...);

			if (m_MultiDelegateMap.find(i_Name) != m_MultiDelegateMap.end())
				m_MultiDelegateMap[i_Name].ExecuteOnBound(i_Parameters ...);
		}
	};

}

#include "Message/MessageManager_inl.h"

