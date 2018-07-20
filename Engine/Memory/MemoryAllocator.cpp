#include "Memory/MemoryAllocator.h"

namespace Engine
{

// 	void* MemoryAllocator::m_pHeap = nullptr;
// 	size_t MemoryAllocator::m_nDescriptors = 0;
// 
// 	size_t MemoryAllocator::m_nHeapSize = 0;
// 	size_t MemoryAllocator::m_nDesPoolSize = 0;
// 	size_t MemoryAllocator::m_nFreeHeapSize = 0;
// 
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_FreeDesHead = nullptr;
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_FreeDesTail = nullptr;
// 
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_OsDesHead = nullptr;
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_OsDesTail = nullptr;
// 
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_nullptrDesHead = nullptr;
// 	MemoryAllocator::BlockDescriptor* MemoryAllocator::m_nullptrDesTail = nullptr;

	MemoryAllocator::MemoryAllocator(void* pHeap, size_t heapSize, unsigned int numDescriptors):
		m_pHeap(pHeap),
		m_nDescriptors(numDescriptors),
		m_nHeapSize(heapSize),
		m_nDesPoolSize(sizeof(BlockDescriptor) * m_nDescriptors),
		m_nFreeHeapSize(m_nHeapSize - m_nDesPoolSize),
		m_FreeDesHead(nullptr),
		m_FreeDesTail(nullptr),
		m_OsDesHead(nullptr),
		m_OsDesTail(nullptr),
		m_nullptrDesHead(nullptr),
		m_nullptrDesTail(nullptr)
	{
		//init nullptr descriptors list
		//m_nullptrDesHead points to the head of block descriptor pool
		m_nullptrDesHead = reinterpret_cast<BlockDescriptor*>(ADDRESS(m_pHeap) + m_nFreeHeapSize);
		m_nullptrDesHead->m_data = nullptr;
		m_nullptrDesHead->m_dataSize = 0;
		m_nullptrDesHead->prev = nullptr;

		//add temp ptr to init link list
		BlockDescriptor* ptr = m_nullptrDesHead;
		BlockDescriptor* ptr1 = ptr;
		for (size_t i = 0; i < m_nDescriptors - 1; i++)
		{

			ptr1 = ptr;
			ptr->next = reinterpret_cast<BlockDescriptor*>(ADDRESS(ptr) + sizeof(BlockDescriptor));
			ptr = ptr->next;
			ptr->prev = ptr1;

			ptr->m_data = nullptr;
			ptr->m_dataSize = 0;

		}
		m_nullptrDesTail = ptr;
		m_nullptrDesTail->next = nullptr;

		//init free list. the first node point to the whole block of memory
		m_FreeDesTail = m_FreeDesHead = m_nullptrDesHead;
		m_FreeDesHead->m_data = m_pHeap;
		m_FreeDesHead->m_dataSize = m_nFreeHeapSize;

		//move the head node of the nullptr list
		m_nullptrDesHead = m_nullptrDesHead->next;
		m_nullptrDesHead->prev = nullptr;
		m_FreeDesTail->next = nullptr;
	}

	MemoryAllocator::MemoryAllocator()
	{

	}

	MemoryAllocator::~MemoryAllocator()
	{

	}

// 	void MemoryAllocator::Create(void* pHeap, size_t heapSize, unsigned int numDescriptors)
// 	{
// 		//init member variables
// 		m_pHeap = pHeap;
// 		m_nDescriptors = numDescriptors;
// 		m_nHeapSize = heapSize;
// 		m_nDesPoolSize = sizeof(BlockDescriptor) * m_nDescriptors;
// 		m_nFreeHeapSize = m_nHeapSize - m_nDesPoolSize;
// 
// 		//init nullptr descriptors list
// 		//m_nullptrDesHead points to the head of block descriptor pool
// 		m_nullptrDesHead = reinterpret_cast<BlockDescriptor*>(ADDRESS(m_pHeap) + m_nFreeHeapSize);
// 		m_nullptrDesHead->m_data = nullptr;
// 		m_nullptrDesHead->m_dataSize = 0;
// 		m_nullptrDesHead->prev = nullptr;
// 
// 		//add temp ptr to init link list
// 		BlockDescriptor* ptr = m_nullptrDesHead;
// 		BlockDescriptor* ptr1 = ptr;
// 		for (size_t i = 0; i < m_nDescriptors - 1; i++)
// 		{
// 
// 			ptr1 = ptr;
// 			ptr->next = reinterpret_cast<BlockDescriptor*>(ADDRESS(ptr) + sizeof(BlockDescriptor));
// 			ptr = ptr->next;
// 			ptr->prev = ptr1;
// 
// 			ptr->m_data = nullptr;
// 			ptr->m_dataSize = 0;
// 
// 		}
// 		m_nullptrDesTail = ptr;
// 		m_nullptrDesTail->next = nullptr;
// 
// 		//init free list. the first node point to the whole block of memory
// 		m_FreeDesTail = m_FreeDesHead = m_nullptrDesHead;
// 		m_FreeDesHead->m_data = m_pHeap;
// 		m_FreeDesHead->m_dataSize = m_nFreeHeapSize;
// 
// 		//move the head node of the nullptr list
// 		m_nullptrDesHead = m_nullptrDesHead->next;
// 		m_nullptrDesHead->prev = nullptr;
// 		m_FreeDesTail->next = nullptr;
// 
// 		//allocate memory for MemoryAllocator itself 
// 		//MemoryAllocator MemoryAllocator;
// 		return reinterpret_cast<MemoryAllocator*>(MemoryAllocator.Allocate(sizeof(MemoryAllocator), 0));
// 
// 	}

	void* MemoryAllocator::Allocate(size_t size, unsigned int alignment)
	{
		//return to user
		void* ptr = nullptr;

		BlockDescriptor* firstFreeDes = m_FreeDesHead;
		size_t align = 0;

		//find a descriptor with enough size
		do
		{
			if (firstFreeDes->m_dataSize < size + sizeof(size_t) * 2 + sizeof(BlockDescriptor*))
			{
				firstFreeDes = firstFreeDes->next;
			}
			else
			{
				void* address = reinterpret_cast<void*>(ADDRESS(firstFreeDes->m_data) + sizeof(BlockDescriptor*) + sizeof(size_t));
				if (alignment != 0)
					align = alignment - ((size_t)address % alignment);

				if (firstFreeDes->m_dataSize < size + sizeof(size_t) * 2 + sizeof(BlockDescriptor*) + align)
					firstFreeDes = firstFreeDes->next;
				else
					break;
			}
		} while (firstFreeDes);

		//while there is no enough memory or descriptor, return nullptr
		if (firstFreeDes == nullptr || m_nullptrDesHead == m_nullptrDesTail)
			return ptr;

		//move a node from the nullptr descriptor list to the outstanding list 
		if (!m_OsDesHead) //first node
		{
			m_OsDesHead = m_OsDesTail = m_nullptrDesHead;
		}
		else
		{
			m_OsDesTail->next = m_nullptrDesHead;
			m_nullptrDesHead->prev = m_OsDesTail;
			m_OsDesTail = m_nullptrDesHead;
		}
		m_OsDesTail->m_data = firstFreeDes->m_data;
		m_OsDesTail->m_dataSize = sizeof(BlockDescriptor*) + sizeof(size_t) + size + sizeof(size_t) + align;

		//move the head of nullptr descriptor list
		if (m_nullptrDesHead->next)
		{
			m_nullptrDesHead = m_nullptrDesHead->next;
			m_nullptrDesHead->prev = nullptr;
		}

		m_OsDesTail->next = nullptr;

		//cut free memory
		if (firstFreeDes->m_dataSize == m_OsDesTail->m_dataSize)
		{
			//delete it
			if (firstFreeDes == m_FreeDesHead)
			{
				m_FreeDesHead = m_FreeDesHead->next;
				m_FreeDesHead->prev = nullptr;
			}
			else if (firstFreeDes == m_FreeDesTail)
			{
				m_FreeDesTail = m_FreeDesTail->prev;
				m_FreeDesTail->next = nullptr;
			}
			else
			{
				firstFreeDes->next->prev = firstFreeDes->prev;
				firstFreeDes->prev->next = firstFreeDes->next;
			}

			firstFreeDes->prev = m_nullptrDesTail;
			m_nullptrDesTail->next = firstFreeDes;
			m_nullptrDesTail = m_nullptrDesTail->next;
			m_nullptrDesTail->m_data = nullptr;
			m_nullptrDesTail->m_dataSize = 0;
			m_nullptrDesTail->next = nullptr;

		}
		else
		{
			firstFreeDes->m_data = reinterpret_cast<void*>(ADDRESS(firstFreeDes->m_data) + m_OsDesTail->m_dataSize);
			firstFreeDes->m_dataSize -= m_OsDesTail->m_dataSize;
		}

		//fill empty memory
		uintptr_t temp = ADDRESS(m_OsDesTail->m_data);

		memset(reinterpret_cast<void*>(temp), 0xED, align);
		temp += align;

		memcpy(reinterpret_cast<void*>(temp), &m_OsDesTail, sizeof(BlockDescriptor*));
		temp += sizeof(BlockDescriptor*);

		memset(reinterpret_cast<void*>(temp), 0xFD, 4);
		temp += 4;

		memset(reinterpret_cast<void*>(temp), 0xFC, size);
		temp += size;

		memset(reinterpret_cast<void*>(temp), 0xFD, 4);

		//the position of data is after align, blockDescriptor* and guardband
		ptr = reinterpret_cast<void*>(ADDRESS(m_OsDesTail->m_data) + sizeof(BlockDescriptor*) + sizeof(size_t) + align);

		return ptr;
	}

	bool MemoryAllocator::Free(void* ptr)
	{
		if (!IsAllocated(ptr))
			return false;

		//erase data
		BlockDescriptor* freeDescriptor = *reinterpret_cast<BlockDescriptor**>((char*)ptr - sizeof(size_t) - sizeof(BlockDescriptor*));
		memset(freeDescriptor->m_data, 0xCC, freeDescriptor->m_dataSize);

		//move this descriptor from outstanding list
		if (m_OsDesHead == m_OsDesTail)
			m_OsDesHead = m_OsDesTail = nullptr;
		else
		{
			if (freeDescriptor == m_OsDesHead)
			{
				m_OsDesHead = m_OsDesHead->next;
				m_OsDesHead->prev = nullptr;
			}
			else if (freeDescriptor == m_OsDesTail)
			{
				m_OsDesTail = m_OsDesTail->prev;
				m_OsDesTail->next = nullptr;
			}
			else
			{
				freeDescriptor->prev->next = freeDescriptor->next;
				freeDescriptor->next->prev = freeDescriptor->prev;
			}
		}

		//insert the descriptor into a correct place according to the address, or collect() doesn't work
		if (!m_FreeDesHead)
		{
			m_FreeDesHead = m_FreeDesTail = freeDescriptor;
			m_FreeDesHead->next = m_FreeDesHead->prev = nullptr;
		}

		else
		{
			//compare the node with head and tail first
			if (ADDRESS(m_FreeDesHead->m_data) > ADDRESS(freeDescriptor->m_data))
			{
				m_FreeDesHead->prev = freeDescriptor;
				freeDescriptor->next = m_FreeDesHead;
				m_FreeDesHead = freeDescriptor;
				m_FreeDesHead->prev = nullptr;
			}
			else if (ADDRESS(m_FreeDesTail->m_data) < ADDRESS(freeDescriptor->m_data))
			{
				m_FreeDesTail->next = freeDescriptor;
				freeDescriptor->prev = m_FreeDesTail;
				m_FreeDesTail = freeDescriptor;
				m_FreeDesTail->next = nullptr;
			}
			else {//if the node should be between head and tail, add two temp BD to traverse the free list

				BlockDescriptor* temp1;
				BlockDescriptor* temp2;
				temp1 = m_FreeDesHead;
				temp2 = m_FreeDesHead->next;

				while (temp2)
				{
					if (ADDRESS(freeDescriptor->m_data) > ADDRESS(temp1->m_data) &&
						ADDRESS(freeDescriptor->m_data) < ADDRESS(temp2->m_data))
					{
						temp1->next = freeDescriptor;
						temp2->prev = freeDescriptor;
						freeDescriptor->next = temp2;
						freeDescriptor->prev = temp1;
						break;
					}
					else
					{
						temp1 = temp2;
						temp2 = temp2->next;
					}
				}
			}
		}

		return true;
	}

	void MemoryAllocator::Collect()
	{

		BlockDescriptor* ptr = m_FreeDesHead;
		BlockDescriptor* nextPtr = m_FreeDesHead->next;
		while (ptr && nextPtr)
		{
			if (ADDRESS(ptr->m_data) + ptr->m_dataSize == ADDRESS(nextPtr->m_data))
			{
				ptr->m_dataSize += ptr->next->m_dataSize;//merge two nodes into the first node

														 //delete nextPtr from free list
				if (nextPtr == m_FreeDesHead)
				{
					m_FreeDesHead = m_FreeDesHead->next;
					m_FreeDesHead->prev = nullptr;
				}
				else if (nextPtr == m_FreeDesTail)
				{
					m_FreeDesTail = m_FreeDesTail->prev;
					m_FreeDesTail->next = nullptr;
				}
				else
				{
					nextPtr->next->prev = nextPtr->prev;
					nextPtr->prev->next = nextPtr->next;
				}

				//add this node to the end of nullptr list
				m_nullptrDesTail->next = nextPtr;
				m_nullptrDesTail = m_nullptrDesTail->next;
				m_nullptrDesTail->next = nullptr;
				m_nullptrDesTail->m_data = nullptr;
				m_nullptrDesTail->m_dataSize = 0;

				nextPtr = ptr->next;
			}
			else {
				ptr = ptr->next;
				nextPtr = ptr->next;
			}
		}
	}

	bool MemoryAllocator::IsAllocated(void* ptr)
	{
		BlockDescriptor* temp = m_OsDesHead;
		if (!temp)
			return false;
		else
		{
			BlockDescriptor* ptrBD = nullptr;
			while (temp)
			{
				ptrBD = *reinterpret_cast<BlockDescriptor**>((char*)ptr - sizeof(size_t) - sizeof(BlockDescriptor*));
				if (ptrBD->m_data == temp->m_data)
					return true;
				temp = temp->next;
			}
		}
		return false;
	}

	size_t MemoryAllocator::GetLargestFreeBlock()
	{
		size_t size = 0;

		BlockDescriptor* temp = m_FreeDesHead;
		while (temp)
		{
			if (temp->m_dataSize > size)
				size = temp->m_dataSize;
			temp = temp->next;
		}
		return size;
	}

	size_t MemoryAllocator::GetTotalFreeMemory()
	{
		size_t size = 0;
		BlockDescriptor* temp = m_FreeDesHead;
		while (temp)
		{
			size += temp->m_dataSize;
			temp = temp->next;
		}
		return size;
	}
}