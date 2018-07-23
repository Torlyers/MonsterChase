#pragma once
#include "GameObject/gameobject.h"
#include <memory>

namespace Engine
{
	template<typename T>
	class BaseComponent
	{
	public:
		BaseComponent(shared_ptr<GameObject> i_GameObject);
		virtual ~BaseComponent() = 0;

	private:
		weak_ptr<GameObject> m_GameObject;
	};

}

