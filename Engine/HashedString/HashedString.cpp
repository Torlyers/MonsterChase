#include "HashedString.h"
#include "DebugTool/Debug.h"
#include <string.h>
#include <stdlib.h>

namespace Engine
{

	HashedString::HashedString():
		m_Hash(Hash(""))
	{

	}

	HashedString::HashedString(const char* i_string):
		m_Hash(Hash(i_string))
	{

	}

	HashedString::HashedString(const HashedString & i_other):
		m_Hash(i_other.m_Hash)
	{

	}


	HashedString::~HashedString()
	{

	}

	HashedString & HashedString::operator=(const HashedString & i_other)
	{
		m_Hash = i_other.m_Hash;

		return *this;
	}

	unsigned int HashedString::Get()
	{
		return m_Hash;
	}

	bool HashedString::operator<(const HashedString & i_other) const
	{
		return m_Hash < i_other.m_Hash;
	}

	bool HashedString::operator>(const HashedString & i_other) const
	{
		return m_Hash > i_other.m_Hash;
	}

	bool HashedString::operator==(const HashedString & i_other) const
	{
		return m_Hash == i_other.m_Hash;
	}

	unsigned int HashedString::Hash(const char * i_String)
	{
		ASSERT(i_String);

		return Hash(reinterpret_cast<void*>(const_cast<char*>(i_String)), strlen(i_String));
	}

	unsigned int HashedString::Hash(const void * i_Bytes, size_t i_Count)
	{
		register const unsigned char* p = static_cast<const unsigned char*>(i_Bytes);
		unsigned int hash = 2166136261;

		for (size_t i = 0; i < i_Count; ++i)
			hash = 16777619 * (hash ^ p[i]);

		return hash ^ (hash >> 16);
	}
}
