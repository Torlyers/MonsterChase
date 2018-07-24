#pragma once
#include <memory>
#include <mutex>
#include "Base/Kernel.h"

using namespace std;

namespace Engine
{
	template<typename T>
	class Singleton
	{				
	public:
		static T* Instance();
		static void DeleteInstance();

	protected:
		Singleton();
		virtual ~Singleton() = 0;

	private:
		Singleton(const Singleton<T>& i_other);
		Singleton<T>& operator=(const Singleton<T>& i_other);
		static unique_ptr<T> m_Instance;
		static mutex m_Mutex;
	};

	template<typename T>
	unique_ptr<T> Singleton<T>::m_Instance = nullptr;

	template<typename T>
	mutex Singleton<T>::m_Mutex;

	template<typename T>
	T* Singleton<T>::Instance()
	{
		if (m_Instance.get() == nullptr)
		{
			lock_guard<mutex> lock(m_Mutex);
			if (m_Instance.get() == nullptr)
			{
				m_Instance = make_unique<T>();
			}
		}

		return m_Instance.get();
	}

	template<typename T>
	void Singleton<T>::DeleteInstance()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	template<typename T>
	Singleton<T>::Singleton() {}

	template<typename T>
	Singleton<T>::~Singleton() {}
}