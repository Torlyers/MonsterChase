#include "BitArray.h"

namespace Engine

{


	BitArray::BitArray()
	{

	}


	BitArray::~BitArray()
	{
		delete m_pBits;
	}

	BitArray* BitArray::Create(size_t i_numBits, MemoryAllocator* i_pAllocator, bool i_startClear)
	{
		BitArray* p_bit_array = reinterpret_cast<BitArray*>(i_pAllocator->Allocate(sizeof(BitArray)));

		p_bit_array->m_bit_num = i_numBits;
		p_bit_array->m_unit_num = i_numBits / BITS_PER_BYTE;
		p_bit_array->m_pBits = reinterpret_cast<BITUNIT*>(i_pAllocator->Allocate(i_numBits / BITS_PER_BYTE));

		if (i_startClear)
			p_bit_array->ClearAll();

		printf("BitArray Created!\n");

		return p_bit_array;
	}

	void BitArray::SetAll(void)
	{
		for (size_t i = 0; i < m_unit_num; i++)
			m_pBits[i] = ~(BITUNIT)0;
	}

	void BitArray::ClearAll(void)
	{
		for (size_t i = 0; i < m_unit_num; i++)
			m_pBits[i] = 0;
	}

	bool BitArray::AreAllSet(void) const
	{
		for (size_t i = 0; i < m_unit_num; i++)
		{
			if (m_pBits[i] != ~(BITUNIT)0)
				return false;
		}
		return true;
	}

	bool BitArray::AreAllClear(void) const
	{
		for (size_t i = 0; i < m_unit_num; i++)
		{
			if (m_pBits[i] != 0)
				return false;
		}
		return true;
	}

	bool BitArray::IsBitSet(size_t i_bitNumber) const
	{
		return (*this)[i_bitNumber];
	}

	bool BitArray::IsBitClear(size_t i_bitNumber) const
	{
		return !(*this)[i_bitNumber];
	}

	void BitArray::SetBit(size_t i_bitNumber)
	{
		m_pBits[i_bitNumber / BITS_PER_UNIT] |= ((BITUNIT)1 << (i_bitNumber % BITS_PER_UNIT));
	}

	void BitArray::ClearBit(size_t i_bitNumber)
	{
		m_pBits[i_bitNumber / BITS_PER_UNIT] &= ~((BITUNIT)1 << (i_bitNumber % BITS_PER_UNIT));
	}

	bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
	{
		for (size_t i = 0; i < m_unit_num; i++)
		{
			if (m_pBits[i] != 0)
			{
				BITSCANFORWARD(reinterpret_cast<unsigned long*>(&o_bitNumber), m_pBits[i]);
				o_bitNumber += i * BITS_PER_UNIT;
				return true;
			}
		}
		return false;
	}

	bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
	{
		for (size_t i = 0; i < m_unit_num; i++)
		{
			if (m_pBits[i] != ~(BITUNIT)0)
			{
				BITSCANFORWARD(reinterpret_cast<unsigned long*>(&o_bitNumber), ~m_pBits[i]);
				o_bitNumber += i * BITS_PER_UNIT;
				return true;
			}
		}
		return false;
	}

	bool BitArray::operator[](size_t i_index) const
	{
		if (m_pBits[i_index / BITS_PER_UNIT] & ((BITUNIT)1 << (i_index % BITS_PER_UNIT)))
			return true;
		else
			return false;
	}

}