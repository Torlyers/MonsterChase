#pragma once
#include "DebugTool\Debug.h"

namespace Engine {

	template <class T>
	class SharedPointer
	{
	private:



	public:

		T* m_ptr;
		long* shared_ref_count;
		long* weak_ref_count;

		SharedPointer();
		SharedPointer(T* i_ptr);
		SharedPointer(const SharedPointer<T> & i_SharedPtr);
		~SharedPointer();

		SharedPointer<T>& operator=(const SharedPointer<T> & i_SharedPtr);
		
		T& operator* ();
		T* operator-> ();

		bool operator==(const SharedPointer<T> & i_SharedPtr) const;

		void ReleaseCurrentReference();
		void AcquireNewReference(const SharedPointer & i_SharedPtr);

	};

	template <class T>
	SharedPointer<T>::SharedPointer() :
		m_ptr(nullptr),
		shared_ref_count(nullptr),
		weak_ref_count(nullptr)
	{

	}

	template <class T>
	SharedPointer<T>::SharedPointer(T* i_ptr) :
		m_ptr(i_ptr),
		shared_ref_count(new long(1)),
		weak_ref_count(new long(0))
	{
		printf("fuck");
	}

	template<class T>
	SharedPointer<T>::SharedPointer(const SharedPointer<T> & i_SharedPtr)
	{
		AcquireNewReference(i_SharedPtr);
	}

	template <class T>
	SharedPointer<T>::~SharedPointer()
	{
		ReleaseCurrentReference();
	}

	template <class T>
	T& SharedPointer<T>::operator*()
	{
		return *m_ptr;
	}

	template <class T>
	T* SharedPointer<T>::operator->()
	{
		ASSERT(m_ptr != nullptr);

		return m_ptr;
	}

	template <class T>
	SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T> & i_SharedPtr)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_SharedPtr);

		return *this;
	}

	template <class T>
	bool SharedPointer<T>::operator==(const SharedPointer<T> & i_SharedPtr) const
	{
		if (m_ptr == i_SharedPtr.m_ptr)
			return true;
		else
			return false;
	}

	template <class T>
	void SharedPointer<T>::ReleaseCurrentReference()
	{
		if (m_ptr != nullptr)
		{
			--(*shared_ref_count);
			if (*shared_ref_count == 0)
			{
				delete m_ptr;
				delete shared_ref_count;
				delete weak_ref_count;
				m_ptr = nullptr;
				shared_ref_count = nullptr;
				weak_ref_count = nullptr;
			}
		}
	}

	template<class T>
	void SharedPointer<T>::AcquireNewReference(const SharedPointer & i_SharedPtr)
	{
		m_ptr = i_SharedPtr.m_ptr;
		shared_ref_count = i_SharedPtr.shared_ref_count;
		weak_ref_count = i_SharedPtr.weak_ref_count;
		++(*shared_ref_count);
	}
}

