#pragma once
#include "HashFunctions.h"
#include "Entry.h"


// Base hash table functionality
template<typename KeyT, typename DataT, class BaseT>
class HashTableBase
{
public:
	HashTableBase(unsigned int size) :
		hash(HashFunctions::defaultHash),
		data(new Entry<KeyT, DataT>[size]),
		size(size)
	{
	}

	~HashTableBase()
	{
		delete[] data;
	}


	// Used to access the hash table like an array. Will flag the accessed enrty as used
	DataT& operator [](const KeyT& key)
	{
		// Hash the key to use it as the index
		unsigned int hashedKey = static_cast<BaseT*>(this)->HashKey(key);


		// Count how many times the array is probed
		unsigned int loopCount = 0;

		// Collision handling
		for (; loopCount < size; loopCount++)
		{
			// If the keys match, this is the correct entry
			if (data[hashedKey].key == key)
				break;
			
			// If the entry's flag is not set, it can be taken
			if (data[hashedKey].inUse == false)
			{
				// Set flag and key
				data[hashedKey].inUse = true;
				data[hashedKey].key = key;
				break;
			}


			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// If the entry isnt found, create larger array
		if (loopCount == size)
		{
			// Old data needs to be kept temporarily
			unsigned int oldSize = size;
			Entry<KeyT, DataT>* oldData = data;

			// Increate size, and create new array
			size *= 2;
			data = new Entry<KeyT, DataT>[size];


			// Iterate through all entries
			for (unsigned int i = 0; i < oldSize; i++)
			{
				// If the entry has been used, add it to the new array
				if (oldData[i].inUse == true)
					this->operator[](oldData[i].key) = oldData[i].data;
			}

			// Delete the old array
			delete[] oldData;
			// Return data in new array
			return this->operator[](key);
		}


		// Return reference to data
		return data[hashedKey].data;
	}

	// Check if the entry exists, without setting its flag if it doesnt
	bool doesEntryExist(const KeyT& key) const
	{
		// Hash the key to use it as the index
		unsigned int hashedKey = static_cast<BaseT*>(this)->HashKey(key);

		// Collision handling
		for (unsigned int i = 0; i < size; i++)
		{
			// If the keys match, the enrty exists
			if (data[hashedKey].key == key)
				return true;

			// If the entry's flag is not set, the entry doesnt exist
			if (data[hashedKey].inUse == false)
				return false;
			
			// Linear probing, and loop the key
			hashedKey += 3;
			hashedKey %= size;
		}

		// The entry couldnt be found
		return false;
	}


protected:
	// The hash function used
	HashFunctions::HashFunc(hash);

	// Pointer to an array of entries
	Entry<KeyT, DataT>* data;
	// The number of elements in the array 'data'
	unsigned int size;
};



// Generic template
template<typename KeyT, typename DataT>
class HashTable : 
	public HashTableBase<KeyT, DataT, HashTable<KeyT, DataT>>
{
public:
	HashTable(unsigned int size) : HashTableBase<KeyT, DataT, HashTable>(size) { }


	// Used by HashTableBase to get the corrent hash
	unsigned int HashKey(const KeyT& key) const
	{
		// Cast the key to char* to get its bytes
		return this->hash((const char*)&key, sizeof(key)) % this->size;
	}
};

// Specialised string key
template<typename DataT>
class HashTable<std::string, DataT> : 
	public HashTableBase<std::string, DataT, HashTable<std::string, DataT>>
{
public:
	HashTable(unsigned int size) : HashTableBase<std::string, DataT, HashTable>(size) { }


	// Used by HashTableBase to get the corrent hash
	unsigned int HashKey(const std::string& key) const
	{
		// c_str returns a const char*
		return this->hash(key.c_str(), (unsigned int)key.size()) % this->size;
	}
};

// Specialised const char* key
template<typename DataT>
class HashTable<const char*, DataT> : 
	public HashTableBase<const char*, DataT, HashTable<const char*, DataT>>
{
public:
	HashTable(unsigned int size) : HashTableBase<const char*, DataT, HashTable>(size) { }


	// Used by HashTableBase to get the corrent hash
	unsigned int HashKey(const char*& key) const
	{
		// No need to cast; its already char*
		return this->hash(key, (unsigned int)std::strlen(key)) % this->size;
	}
};