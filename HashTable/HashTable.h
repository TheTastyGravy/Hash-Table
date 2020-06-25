#pragma once
#include "HashFunctions.h"
#include "Entry.h"



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



	DataT& operator [](const KeyT& key)
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

	// Pointer to an array of type 'T'
	Entry<KeyT, DataT>* data;
	// The number of elements in the array 'data'
	unsigned int size;
};