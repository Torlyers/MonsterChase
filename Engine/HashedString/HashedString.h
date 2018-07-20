#pragma once

namespace Engine
{

	class HashedString
	{
	public:
		HashedString();
		HashedString(const char* i_string);
		HashedString(const HashedString & i_other);
		~HashedString();

		unsigned int Get();

		HashedString & operator=(const HashedString & i_other);
		bool operator<(const HashedString & i_other) const;
		bool operator>(const HashedString & i_other) const;
		bool operator==(const HashedString & i_other) const;

		static unsigned int	Hash(const char* i_String);
		static unsigned int Hash(const void* i_Bytes, size_t i_Count);

	private:

		unsigned int m_Hash;
	};
}

