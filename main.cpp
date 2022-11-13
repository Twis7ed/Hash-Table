#include <iostream>
#include <cstring>
#include <string>
#include <array>
#include <list>

class HashTable
{
private:
	static const int hashGroups = 10;
	std::list<std::pair<int, std::string>> table[hashGroups]; // List 1: Index 0, List 2: Index 1...

public:
	bool isEmpty();
	int hashFunction(int key);
	void insertItem(int key, std::string value);
	void removeItem(int key);
	void printTable();
};

bool HashTable::isEmpty()
{
	int sum{};
	for (int i{}; i < hashGroups; i++)
		sum += table[i].size();

	if (!sum)
		return true;

	return false;
}

int HashTable::hashFunction(int key)
{
	return key % hashGroups; // (Key / 10) to lowest denominator
}

void HashTable::insertItem(int key, std::string value)
{
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;

	for (; bItr != end(cell); bItr++)
	{
		if (bItr->first == key)
		{
			keyExists = true;
			bItr->second = value;
			std::cout << "WARNING: Key exists, Value replaced.\n";
			break;
		}
	}

	if (!keyExists)
		cell.emplace_back(key, value);

	return;
}

void HashTable::removeItem(int key)
{
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;

	for (; bItr != end(cell); bItr++)
	{
		if (bItr->first == key)
		{
			keyExists = true;
			bItr = cell.erase(bItr);
			std::cout << "INFO: Item removed.\n";
			break;
		}
	}

	if (!keyExists)
		std::cout << "WARNING: Key not found, Pair not removed.\n";

	return;
}

void HashTable::printTable()
{
	for (int i{}; i < hashGroups; i++)
	{
		if (table[i].size() == 0)
			continue;

		auto bItr = table[i].begin();

		for (; bItr != table[i].end(); bItr++)
			std::cout << "INFO: Key: " << bItr->first << " Value: " << bItr->second << "\n";
	}

	return;
}

int main()
{
	HashTable ht;

	if (ht.isEmpty())
		std::cout << "Correct answer. Good job!\n";
	else
		std::cout << "Bad code!\n";

	ht.insertItem(905, "bob");
	ht.insertItem(201, "tom");
	ht.insertItem(332, "jim");
	ht.insertItem(122, "sam");
	ht.insertItem(107, "ula");
	ht.insertItem(928, "oda");
	ht.insertItem(928, "rye");

	ht.printTable();

	ht.removeItem(201);
	ht.removeItem(100);

	if (ht.isEmpty())
		std::cout << "Bad code!\n";
	else
		std::cout << "Correct answer, Good job!\n";

	return 0;
}