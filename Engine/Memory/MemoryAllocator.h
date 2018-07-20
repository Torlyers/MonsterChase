#pragma once
#include <cstdint> 
#include <memory.h>
#include <cinttypes>

#include "DataStructure/List.h"
#include "DebugTool/Debug.h"

#define ADDRESS reinterpret_cast<uintptr_t>

namespace Engine
{

	class MemoryAllocator
	{
	public:

		struct BlockDescriptor
		{

			void* m_data;	// pointer to the block of memory this BlockDescriptor describes
			size_t m_dataSize;	// size of that block of memory
			BlockDescriptor* next;
			BlockDescriptor* prev;

		};

		MemoryAllocator();
		MemoryAllocator(void* pHeap, size_t heapSize, unsigned int numDescriptors);
		~MemoryAllocator();

		void Create(void* pHeap, size_t heapSize, unsigned int numDescriptors);

		void* Allocate(size_t size, unsigned int alignment = 0);
		bool Free(void* ptr);
		void Collect();

		inline bool Contains(void* ptr);
		bool IsAllocated(void* ptr) ;

		size_t GetLargestFreeBlock() ;
		size_t GetTotalFreeMemory() ;
		

	private:

		void * m_pHeap;
		int m_nDescriptors;

		int m_nHeapSize;
		int m_nDesPoolSize;
		int m_nFreeHeapSize;

		BlockDescriptor* m_FreeDesHead;
		BlockDescriptor* m_FreeDesTail;
		BlockDescriptor* m_OsDesHead;
		BlockDescriptor* m_OsDesTail;
		BlockDescriptor* m_nullptrDesHead;
		BlockDescriptor* m_nullptrDesTail;
	};

}

#include "Memory/MemoryAllocator_inl.h"