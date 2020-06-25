#pragma once
#include "HashFunctions.h"
#include "Entry.h"


// Generic template
template<typename KeyT, typename DataT>
class HashTable
{
public:
	HashTable(unsigned int size) :
		hash(HashFunctions::defaultHash),
		data(new Entry<KeyT, DataT>[size]),
		size(size)
	{
	}

	~HashTable()
	{
		delete[] data;
	}


	// Used to access the hash table like an array
	DataT& operator [](const KeyT& key)
	{
		// Cast the key to char* to get its bytes
		// Use a hashed key as the array's index
		auto hashedKey = hash((const char*)&key, sizeof(key)) % size;

		// Collision handling
		while (true)
		{
			// If the keys match, this is the correct entry
			if (data[hashedKey].key == key)
				break;
			
			// If the entry's flag is not set, it can be taken
			if (data[hashedKey].valid == false)
			{
				// Set flag and key
				data[hashedKey].valid = true;
				data[hashedKey].key = key;
				break;
			}


			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// Return reference to data
		return data[hashedKey].data;
	}

	const DataT& operator [](const KeyT& key) const
	{
		// Cast the key to char* to get its bytes
		// Use a hashed key as the array's index
		auto hashedKey = hash((const char*)&key, sizeof(KeyT)) % size;

		// Collision handling
		while (true)
		{
			// If the keys match, this is the correct entry
			if (data[hashedKey].key == key)
				break;

			// If the entry's flag is not set, it can be taken
			if (data[hashedKey].valid == false)
			{
				// Set flag and key
				data[hashedKey].valid = true;
				data[hashedKey].key = key;
				break;
			}


			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// Return reference to data
		return data[hashedKey].data;
	}


private:
	// The hash function used
	HashFunctions::HashFunc(hash);

	// Pointer to an array of entries
	Entry<KeyT, DataT>* data;
	// The number of elements in the array 'data'
	unsigned int size;
};


// Specialisation for string key type
template<typename DataT>
class HashTable<std::string, DataT>
{
public:
	HashTable(unsigned int size) :
		hash(HashFunctions::defaultHash),
		data(new Entry<std::string, DataT>[size]),
		size(size)
	{
	}

	~HashTable()
	{
		delete[] data;
	}


	// Used to access the hash table like an array
	DataT& operator [](const std::string& key)
	{
		// c_str returns const char*
		// Use a hashed key as the array's index
		auto hashedKey = hash(key.c_str(), (unsigned int)key.size()) % size;

		// Collision handling
		while (true)
		{
			// If the keys match, this is the correct entry
			if (data[hashedKey].key == key)
				break;

			// If the entry's flag is not set, it can be taken
			if (data[hashedKey].valid == false)
			{
				// Set flag and key
				data[hashedKey].valid = true;
				data[hashedKey].key = key;
				break;
			}


			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// Return reference to data
		return data[hashedKey].data;
	}

	const DataT& operator [](const std::string& key) const
	{
		// c_str returns const char*
		// Use a hashed key as the array's index
		auto hashedKey = hash(key.c_str(), key.size()) % size;

		// Collision handling
		while (true)
		{
			// If the keys match, this is the correct entry
			if (data[hashedKey].key == key)
				break;

			// If the entry's flag is not set, it can be taken
			if (data[hashedKey].valid == false)
			{
				// Set flag and key
				data[hashedKey].valid = true;
				data[hashedKey].key = key;
				break;
			}


			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// Return reference to data
		return data[hashedKey].data;
	}

private:
	// The hash function used
	HashFunctions::HashFunc(hash);

	// Pointer to an array of entries
	Entry<std::string, DataT>* data;
	// The number of elements in the array 'data'
	unsigned int size;
};