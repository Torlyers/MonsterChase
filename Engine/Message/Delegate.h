#pragma once
#include<vector>
#include"DebugTool/Debug.h"

namespace Engine
{
	template<class ... Params>
	class Delegate
	{

	private:

		typedef void(*tMethodStub)(void* i_Instance, Params...iParameter);

		void* m_Instance;
		tMethodStub m_MethodStub;
		
		explicit Delegate(void* i_Instance, tMethodStub i_MethodStub):
			m_Instance(i_Instance),
			m_MethodStub(i_MethodStub)
		{
			ASSERT(m_Instance);
			ASSERT(m_MethodStub);
		}

		//
		template<class T, void(T::*TMethod)(Params ...)>
		static void method_stub(void* i_Instance, Params...i_Parameters)
		{
			(static_cast<T*>(i_Instance)->*TMethod)(i_Parameters ...);
		}

	public:

		Delegate():
			m_Instance(nullptr),
			m_MethodStub(nullptr)
		{

		}
	
		//static for explicit call
		template<class T, void(T::*TMethod)(Params ...)>
		static Delegate Create(T* i_Instance)
		{
			return Delegate(i_Instance, &method_stub<T, TMethod>);
		}

		void operator()(Params ... i_Parameters) const
		{
			ASSERT(m_MethodStub);
			(*m_MethodStub)(m_Instance, i_Parameters ...);
		}

		void ExcuteIfBound(Params ... i_Parameters) const 
		{
			if (m_Instance)
			{
				ASSERT(m_MethodStub);
				(*m_MethodStub)(m_Instance, i_Parameters ...);
			}
		}

		operator bool() const
		{
			return m_Instance != nullptr;
		}

		bool operator==(const Delegate& other)
		{
			return m_Instance == other.m_Instance && m_MethodStub == m_MethodStub;
		}

	};

	template<class ... Params>
	class MultiCastDelegate
	{
	private:

		std::vector<Delegate<Params ... >> m_Receivers;

	public:

		void AddDelegate(Delegate<Params ... > & i_Delegate)
		{
			m_Receivers.push_back(i_Delegate);
		}

		void RemoveDelegate(Delegate<Params ... > & i_Delegate)
		{
			for (int i = 0; i < m_Receivers.size(); ++i)
			{
				if (m_Receivers[i] == i_Delegate)
				{
					m_Receivers.erase(m_Receivers.begin() + i);
					--i;
				}
			}
		}

		void ExecuteOnBound(Params ... i_Parameters)
		{
			for (auto receiver : m_Receivers)
			{
				receiver.ExcuteIfBound(i_Parameters ...);
			}
		}

	};

}

#include "Message/Delegate_inl.h"

