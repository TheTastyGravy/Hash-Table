#include "HashFunctions.h"


unsigned int HashFunctions::badHash(const char* data, unsigned int length)
{
	unsigned int hash = 0;

	// Add each byte together
	for (unsigned int i = 0; i < length; ++i)
		hash += data[i];

	return hash;
}

unsigned int HashFunctions::BKDRHash(const char* data, unsigned int size)
{
	unsigned int hash = 0;

	for (unsigned int i = 0; i < size; i++)
		hash = (hash * 1313) + data[i];
	
	return (hash & 0x7FFFFFFF);
}

unsigned int HashFunctions::ELFHash(const char* data, unsigned int size)
{
	unsigned int hash = 0;
	unsigned int x = 0;

	for (unsigned int i = 0; i < size; i++)
	{
		hash = (hash << 4) + data[i];

		if ((x = hash & 0xF000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}

	return (hash & 0x7FFFFFFF);
}