#pragma once
#include "SmartPointer/SharedPointer.h"

namespace Engine
{

	template <class T>
	class WeakPointer
	{
	private:

		T* m_ptr;
		long* shared_ref_count;
		long* weak_ref_count;

	public:
		WeakPointer();
		WeakPointer(const SharedPointer<T> & i_SharedPtr);
		WeakPointer(const WeakPointer<T> & i_WeakPtr);
		~WeakPointer();

		WeakPointer<T>& operator=(const SharedPointer<T> & i_SharedPtr);
		WeakPointer<T>& operator=(const WeakPointer<T> & i_WeakPtr);

		bool operator==(const SharedPointer<T> & i_SharedPtr) const;
		bool operator==(const WeakPointer<T> & i_WeakPtr) const;

		T& operator* ();
		T* operator-> ();

		bool IsValid() const;
		operator bool() const;

		void ReleaseCurrentReference();
		void AcquireNewReference(const SharedPointer<T> & i_SharedPtr);
		void AcquireNewReference(const WeakPointer<T> & i_WeakPtr);
		

	};

	template <class T>
	WeakPointer<T>::WeakPointer():
		m_ptr(nullptr),
		shared_ref_count(nullptr),
		weak_ref_count(nullptr)
	{

	}

	template <class T>
	WeakPointer<T>::WeakPointer(const SharedPointer<T> & i_SharedPtr):
		m_ptr(i_SharedPtr.m_ptr),
		shared_ref_count(i_SharedPtr.shared_ref_count),
		weak_ref_count(i_SharedPtr.weak_ref_count)
	{
		++(*weak_ref_count);
	}

	template <class T>
	WeakPointer<T>::WeakPointer(const WeakPointer<T> & i_WeakPtr):
		m_ptr(i_WeakPtr.m_ptr),
		shared_ref_count(i_WeakPtr.shared_ref_count),
		weak_ref_count(i_WeakPtr.weak_ref_count)
	{
		++(*weak_ref_count);
	}

	template <class T>
	WeakPointer<T>::~WeakPointer()
	{
		ReleaseCurrentReference();
	}

	template <class T>
	WeakPointer<T>& WeakPointer<T>::operator=(const SharedPointer<T> & i_SharedPtr)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_SharedPtr);

		return *this;
	}

	template <class T>
	WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer<T> & i_WeakPtr)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_WeakPtr);

		return *this;
	}

	template <class T>
	T& WeakPointer<T>::operator*()
	{
		return *m_ptr;
	}

	template <class T>
	T* WeakPointer<T>::operator->()
	{
		return m_ptr;
	}

	template <class T>
	bool WeakPointer<T>::operator==(const SharedPointer<T> & i_SharedPtr) const
	{
		if (m_ptr == i_SharedPtr.m_ptr)
			return true;
		else
			return false;
	}

	template <class T>
	bool WeakPointer<T>::operator==(const WeakPointer<T> & i_WeakPtr) const
	{
		if (m_ptr == i_WeakPtr.m_ptr)
			return true;
		else
			return false;
	}

	template <class T>
	bool WeakPointer<T>::IsValid() const
	{
		return m_ptr != nullptr;
	}

	template <class T>
	WeakPointer<T>::operator bool() const
	{
		return IsValid();
	}

	template <class T>
	void WeakPointer<T>::ReleaseCurrentReference()
	{
		if (weak_ref_count)
		{
			--(*weak_ref_count);
			if (*weak_ref_count == 0 && shared_ref_count == 0)
			{
				delete weak_ref_count;
				delete shared_ref_count;
				weak_ref_count = nullptr;
				shared_ref_count = nullptr;
			}
		}
	}

	template <class T>
	void WeakPointer<T>::AcquireNewReference(const SharedPointer<T> & i_SharedPtr)
	{
		m_ptr = i_SharedPtr.m_ptr;
		shared_ref_count = i_SharedPtr.shared_ref_count;
		weak_ref_count = i_SharedPtr.weak_ref_count;
		++(*weak_ref_count);
	}

	template <class T>
	void WeakPointer<T>::AcquireNewReference(const WeakPointer & i_WeakPtr)
	{
		m_ptr = i_WeakPtr.m_ptr;
		shared_ref_count = i_WeakPtr.shared_ref_count;
		weak_ref_count = i_WeakPtr.weak_ref_count;
		++(*weak_ref_count);
	}

}
