#pragma once

#include<memory>
#include<cstdint>
#include <intrin.h>

#include "Memory/MemoryAllocator.h"


#define BITS_PER_BYTE 8

#ifdef WIN32
#define BITUNIT uint32_t
#define BITS_PER_UNIT 32
#define BITSCANFORWARD _BitScanForward
#define ZERO 0x00000000
#else
#define BITUNIT uint64_t
#define BITS_PER_UNIT 64
#define BITSCANFORWARD _BitScanForward64
#define ZERO 0x0000000000000000
#endif

#define ONE ~ZERO

namespace Engine
{

	class BitArray
	{

	private:

		BITUNIT * m_pBits;//byte array
		size_t m_bit_num;
		size_t m_unit_num;

	public:

		static BitArray* Create(size_t i_numBits, MemoryAllocator* i_pAllocator, bool i_startClear = true);
		BitArray();
		~BitArray();

		void SetAll(void);
		void ClearAll(void);

		bool AreAllSet(void) const;
		bool AreAllClear(void) const;

		bool IsBitSet(size_t i_bitNumber) const;
		bool IsBitClear(size_t i_bitNumber) const;

		void SetBit(size_t i_bitNumber);
		void ClearBit(size_t i_bitNumber);

		bool GetFirstSetBit(size_t & o_bitNumber) const;
		bool GetFirstClearBit(size_t & o_bitNumber) const;

		bool operator[](size_t i_index) const;

	};

}