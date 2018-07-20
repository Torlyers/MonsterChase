#pragma once
#include "Base/Singleton.h"

namespace Engine
{

	class MemoryManager: public Singleton<MemoryManager>
	{
	public:
		MemoryManager();
		~MemoryManager();
	};

}