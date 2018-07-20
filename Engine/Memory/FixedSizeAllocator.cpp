#include "FixedSizeAllocator.h"

namespace Engine
{


	FixedSizeAllocator::FixedSizeAllocator()
	{

	}


	FixedSizeAllocator::~FixedSizeAllocator()
	{

	}

	FixedSizeAllocator* FixedSizeAllocator::Create(size_t i_block_num, size_t i_block_size, MemoryAllocator* i_heapManager)
	{
		FixedSizeAllocator* fixed_size_allocator = reinterpret_cast<FixedSizeAllocator*>(i_heapManager->Allocate(sizeof(FixedSizeAllocator)));

		fixed_size_allocator->m_block_num = i_block_num;
		fixed_size_allocator->m_block_size = i_block_size;
		fixed_size_allocator->m_heap_head = i_heapManager->Allocate(i_block_num * i_block_size);
		fixed_size_allocator->m_bit_array = BitArray::Create(i_block_num, i_heapManager);

		printf("Fixed Created!\n");

		return fixed_size_allocator;
	}

	void* FixedSizeAllocator::Alloc(size_t i_size)
	{

		size_t index = 0;
		m_bit_array->GetFirstClearBit(index);
		m_bit_array->SetBit(index);
		void* ptr = GetPtrFromIndex(index);

		memset(ptr, 0xFD, 4);
		memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr) + 4), 0xCD, m_block_size);
		memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr) + 4 + m_block_size), 0xFD, 4);

		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr) + 4);
	}

	bool FixedSizeAllocator::Free(void* i_ptr)
	{
		if (Contains(i_ptr) && IsAllocated(i_ptr))
		{
			size_t index = GetIndexFromPtr(i_ptr);
			m_bit_array->ClearBit(index);
			memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_ptr) - 4), 0xCC, m_block_size + 8);
			return true;
		}
		return false;
	}

	bool FixedSizeAllocator::Contains(void* i_ptr)
	{
		return (reinterpret_cast<uintptr_t>(i_ptr) >= reinterpret_cast<uintptr_t>(m_heap_head) &&
			reinterpret_cast<uintptr_t>(i_ptr) <= reinterpret_cast<uintptr_t>(m_heap_head) + m_block_size * m_block_num);
	}

	bool FixedSizeAllocator::IsAllocated(void* i_ptr)
	{
		size_t index = GetIndexFromPtr(i_ptr);
		return m_bit_array->IsBitSet(index);
	}

	size_t FixedSizeAllocator::GetIndexFromPtr(void* i_ptr)
	{
		size_t index = 0;
		index += (reinterpret_cast<uintptr_t>(i_ptr) - 4 - reinterpret_cast<uintptr_t>(m_heap_head)) / (m_block_size + 8);
		return index;
	}

	void* FixedSizeAllocator::GetPtrFromIndex(size_t index)
	{
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(m_heap_head) + index * (m_block_size + 8));
	}

}