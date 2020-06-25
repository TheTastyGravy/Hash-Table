#pragma once
#include <functional>


namespace HashFunctions
{
	// The generic type of hash function
	typedef std::function<unsigned int(const char*, unsigned int)> HashFunc;


	// Basic hash function
	unsigned int badHash(const char* data, unsigned int length);

	unsigned int BKDRHash(const char* data, unsigned int size);

	unsigned int ELFHash(const char* data, unsigned int size);


	// Hash used by program
	static HashFunc defaultHash = BKDRHash;
}