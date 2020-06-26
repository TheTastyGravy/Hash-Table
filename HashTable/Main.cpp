#include <iostream>
#include "HashTable.h"

#define print(str) std::cout << str << std::endl
using std::string;


// Used to store and return data from getInput()
struct Command
{
	int id = 0;
	string key = "";
	string data = "";
};

// Get input from the user
Command getInput();
// Search for entry in 'table'
void searchTable(const string& key, HashTable<string, string>& table);
// Add a new entry to 'table'
void addToTable(const string& key, const string& data, HashTable<string, string>& table);


int main()
{
	HashTable<string, string> hashTable(50);
	bool running = true;

	// Game loop
	while (running)
	{
		// Get user input
		Command command = getInput();

		switch (command.id)
		{
		// Exit the program
		case 1:
			running = false;
			break;
		// Search for entry
		case 2:
			searchTable(command.key, hashTable);
			break;
		// Add new entry
		case 3:
			addToTable(command.key, command.data, hashTable);
			break;
		// 0 is invalid input
		default:
			print("Invalid input; try again");
			continue;
		}
	}


	return 0;
}


Command getInput()
{
	char input[50] = "\0";
	// Get input
	std::cout << "Enter command :";
	std::cin.clear();
	std::cin >> input;

	// Store the command info
	// An id of 0 is an invalid command
	Command command;
	

	// Exit the program
	if (strcmp(input, "exit") == 0)
	{
		command.id = 1;
		return command;
	}
	// Search for entry
	else if (strcmp(input, "search") == 0)
	{
		command.id = 2;
	}
	// Add new entry
	else if (strcmp(input, "add") == 0)
	{
		command.id = 3;
	}
	// Invalid input
	else
	{
		return command;
	}
	

	// Only search and add need more info.
	// Loop twice, unless input is empty
	for (int i = 0; input && i < 2; i++)
	{
		// Check if there is any input left
		char next = std::cin.peek();
		// Not enough input; invalid command
		if (next == '\n' || next == EOF)
		{
			command.id = 0;
			break;
		}
		// Get next word
		std::cin >> input;

		// On first loop, get key
		if (i == 0)
		{
			command.key = input;

			// Search only needs one string
			if (command.id == 2)
				break;
		}
		// On second loop, get name
		else
		{
			command.data = input;
		}
	}
	
	// Return the final command
	return command;
}

void searchTable(const string& key, HashTable<string, string>& table)
{
	// Check if the entry exists first
	if (table.doesEntryExist(key))
	{
		// Display the entry's data
		print("Name: " << key);
		print("Number: " << table[key]);
	}
	else
	{
		print("Entry does not exist");
	}
}

void addToTable(const string& key, const string& data, HashTable<string, string>& table)
{
	// Display what was done
	if (table.doesEntryExist(key))
		print("Entry changed");
	else
		print("Entry added");

	// Set the data
	table[key] = data;
}