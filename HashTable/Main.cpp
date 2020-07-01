#include <iostream>
#include "HashTable.h"

#define print(str) std::cout << str << std::endl
using std::string;


// Used to store and return data from getInput()
struct Command
{
	int id = 0;
	string data[2];
};

// Get input from the user
Command getInput();
// Search for entry in 'table'
void searchTable(const string& key, HashTable<string, string>& table);
// Add a new entry to 'table'
void addToTable(const string& key, const string& data, HashTable<string, string>& table);
// Display info on how to use the commands
void showHelp();


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
			continue;
		// Search for entry
		case 2:
			searchTable(command.data[0], hashTable);
			break;
		// Add new entry
		case 3:
			addToTable(command.data[0], command.data[1], hashTable);
			break;
		// Show help text
		case 4:
			showHelp();
			break;
		// 0 is invalid input
		default:
			print("Invalid input; try again");
			break;
		}

		
		print("\nPress any key to continue...");
		// Clear in stream
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		// Pause
		std::cin.get();
		// Clear console
		system("cls");
	}


	return 0;
}


Command getInput()
{
	char input[50] = "\0";
	// Get input
	std::cout << "Enter command : ";
	std::cin.clear();
	std::cin >> input;

	// Store the command info
	// An id of 0 is an invalid command
	Command command;
	
	// How much extra input is nessesary?
	int loopCount = 0;


	// Exit the program
	if (strcmp(input, "exit") == 0)
	{
		command.id = 1;
	}
	// Search for entry
	else if (strcmp(input, "search") == 0)
	{
		command.id = 2;
		loopCount = 1;
	}
	// Add new entry
	else if (strcmp(input, "add") == 0)
	{
		command.id = 3;
		loopCount = 2;
	}
	// Show command help
	else if (strcmp(input, "help") == 0)
	{
		command.id = 4;
	}
	

	// Loop while more input is nessesary
	// Contains check for if more input exists
	for (int i = 0; i < loopCount; i++)
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


		// Add the input to the struct
		command.data[i] = input;
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

void showHelp()
{
	print("search <name> - Search the table for an entry of <name>");
	print("add <name> <number> - Create a new entry of <name> and <number>, or if an entry of <name> already exists, change its number");
	print("help - Display this text");
	print("exit - Exit the program");
}