#pragma once
#include"Memory/MemoryAllocator.h"

namespace Engine
{
	bool MemoryAllocator::Contains(void* ptr)
	{
		ASSERT(ptr);
		return ADDRESS(ptr) > ADDRESS(m_pHeap) && ADDRESS(ptr) < ADDRESS(ptr) + m_nHeapSize;
	}


}