#pragma once

template<typename KeyT, typename DataT>
struct Entry
{
	// Used to determine if the entry has been used yet
	bool valid = false;
	KeyT key;
	DataT data;
};