#pragma once
#include"Base/Kernel.h"


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
		virtual ~Singleton();

	private:
		static T* m_Instance;
	};

	template<typename T>
	T* Singleton<T>::m_Instance = nullptr;

	template<typename T>
	T* Singleton<T>::Instance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new T();
		}

		return m_Instance;
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