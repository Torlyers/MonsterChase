#pragma once
#include"Base/Kernel.h"


namespace Engine
{



	template<typename T>
	class Singleton
	{
				
	public:
		
		static T* Instance();

	private:
		
		Singleton();
		~Singleton();
		Singleton(const T& i_other);
		Singleton& operator=(const T& i_other);
		
		static T* m_Instance;
	};

	

	template<typename T>
	static T* Singleton<T>::Instance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new T();
		}

		return m_Instance;
	}

	template<typename T>
	T* Singleton<T>::m_Instance = nullptr;
}