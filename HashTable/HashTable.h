#pragma once
#include <string>
#include "HashFunctions.h"


template<typename T>
class HashTable
{
public:
	HashTable(unsigned int size) :
		hash(HashFunctions::defaultHash),
		data(new T[size]),
		size(size)
	{
	}

	~HashTable()
	{
		delete[] data;
	}


	T& operator [](const std::string& key)
	{
		auto hashedKey = hash(key.c_str(), key.size()) % size;
		//collision handling
		return data[hashedKey];
	}

	const T& operator [](const std::string& key) const
	{
		auto hashedKey = hash(key.c_str(), key.size()) % size;
		//collision handling
		return data[hashedKey];
	}

private:
	// The hash function used
	HashFunctions::HashFunc(hash);

	// Pointer to an array of type 'T'
	T* data;
	// The number of elements in the array 'data'
	unsigned int size;
};