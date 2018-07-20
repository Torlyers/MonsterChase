#pragma once
#include "DebugTool\Debug.h"
#include "Memory\HeapManager.h"
#include "Memory\FixedSizeAllocator.h"

const size_t 		sizeHeap = 1024 * 1024;
const unsigned int 	numDescriptors = 2048;
void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
HeapManager* pHeapManager = HeapManager::create(pHeapMemory, sizeHeap, numDescriptors);

const size_t fixed_size = 16;
const size_t block_num = 256;
FixedSizeAllocator* fixed_size_allocator = FixedSizeAllocator::Create(block_num, fixed_size, pHeapManager);

void* operator new(size_t size)
{
	if (size + 1 < fixed_size)
		return fixed_size_allocator->Alloc(size);
	else
		return pHeapManager->allocate(size, 0);
}

void* operator new[](size_t size)
{
	if (size + 1 < fixed_size)
		return fixed_size_allocator->Alloc(size);
	else
		return pHeapManager->allocate(size, 0);
}

void* operator new(size_t size, HeapManager* heapManager, unsigned int alignment)
{
	ASSERT(heapManager);

	return heapManager->allocate(size, alignment);
}

void* operator new[](size_t size, HeapManager* heapManager, unsigned int alignment)
{
	ASSERT(heapManager);

	return heapManager->allocate(size, alignment);
}

void operator delete(void* ptr)
{
	if (fixed_size_allocator->Contains(ptr))
		fixed_size_allocator->Free(ptr);

	if (pHeapManager->contains(ptr))
		pHeapManager->_free(ptr);
}

void operator delete[](void* ptr)
{
	if (fixed_size_allocator->Contains(ptr))
		fixed_size_allocator->Free(ptr);

	if (pHeapManager->contains(ptr))
		pHeapManager->_free(ptr);
}

void FSA_Test()
{
	char* ch = new char;
	char* ch1 = new char;
	char* ch2 = new char;
	char* ch3 = new char;
	char* ch4 = new char;
	char* ch5 = new char;
}