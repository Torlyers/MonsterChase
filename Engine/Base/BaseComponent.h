#pragma once
#include "GameObject/gameobject.h"
#include "SmartPointer/SharedPointer.h"
#include "SmartPointer/WeakPointer.h"

namespace Engine
{
	template<typename T>
	class BaseComponent
	{
	public:
		BaseComponent(SharedPointer<GameObject> i_GameObject);
		virtual ~BaseComponent() = 0;

	private:
		WeakPointer<GameObject> m_GameObject;
	};

}

