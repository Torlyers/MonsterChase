#pragma once
#include "BitArray.h"


namespace Engine
{

	class FixedSizeAllocator
	{

	private:

		void* m_heap_head;
		size_t m_block_size;
		size_t m_block_num;
		BitArray* m_bit_array;

	public:

		FixedSizeAllocator();
		~FixedSizeAllocator();

		static FixedSizeAllocator* Create(size_t i_block_num, size_t i_block_size, MemoryAllocator* i_heapManager);

		void* Alloc(size_t i_size);
		bool Free(void* i_ptr);

		bool Contains(void* i_ptr);
		bool IsAllocated(void* i_ptr);

		size_t GetIndexFromPtr(void* i_ptr);
		void* GetPtrFromIndex(size_t index);
	};

}