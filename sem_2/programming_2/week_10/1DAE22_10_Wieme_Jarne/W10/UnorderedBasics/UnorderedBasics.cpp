#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include <iomanip>
#include <vector>
#include "Player.h"
#include <unordered_set>
#include <unordered_map>

void TestUnorderedSet();
void TestUnorderedMap();
void TestUnorderedMultiset();
void TestUnorderedMultimap();
void DeleteCityNamesWithLenght8OrMore(std::unordered_set<std::string>& unorderedSet);
void DeleteCityNamesWithLenght8OrMore(std::unordered_multiset<std::string>& unorderedMultiset);
void DeletePlayerWithScoreLessThen10(std::unordered_map<std::string, Player>& unorderedMap);
void DeletePlayerWithScoreLessThen10(std::unordered_multimap<std::string, Player>& unorderedMultimap);

#pragma region HelperDeclarations
size_t GetHashValue(const std::string& text);
template <typename T>
void PrintBuckets(const T& container);
#pragma endregion HelperDeclarations

int main()
{
	srand(unsigned int(time(nullptr)));
	std::cout << std::boolalpha;

	// Exploring the unordered associative containers
	TestUnorderedSet( );
	TestUnorderedMap( );
	TestUnorderedMultiset( );
	TestUnorderedMultimap( );

	// Wait
	std::cout << "\nPush ENTER to continue";
	std::cin.get();

	return 0;
}

void TestUnorderedSet()
{
	std::cout << "\n--> Unordered_set of city names\n";
	std::vector<std::string>  namesSrc1{
		"Aalst",
		"Kortrijk",
		"Gent",
		"Antwerpen",
		"Aalst",
		"Namen",
		"Gent",
		"Hasselt" };
	std::vector<std::string>  namesSrc2{
		"Brugge",
		"Mechelen",
		"Brussel",
		"Boom",
		"Lokeren" };


	std::cout << "\nCreate and fill the unordered_set using a given vector of cities\n";
	std::cout << "These are the elements of the vector: ";
	// TODO: 1a. Print the cities of vector namesSrc1
	for (const std::string& name : namesSrc1)
	{
		std::cout << name << ' ';
	}

	// TODO: 1b. Define and fill an unordered_set of cities  
	//  using the given namesSrc1 vector as a source
	std::unordered_set<std::string> unorderedSet{};

	for (const std::string& name : namesSrc1)
	{
		unorderedSet.insert(name);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1c. Print all the elements together with their hash value, 
	// You can use the given function 'GetHashValue'
	for (const std::string& name : unorderedSet)
	{
		std::cout << name << ' ' << GetHashValue(name) << '\n';
	}

	// TODO: 1d. Print the buckets using the given function 'PrintBuckets'
	// and have a look at the output
	PrintBuckets(unorderedSet);

	std::cout << "\nInsert another vector of city names into the unordered_set\n";
	std::cout << "These are the elements of this vector: ";
	// TODO: 1e. Print the cities of vector namesSrc2
	for (const std::string& name : namesSrc2)
	{
		std::cout << name << ' ';
	}

	// TODO: 1f. Insert the cities from the vector namesSrc2 into the unordered_set
	for (const std::string& name : namesSrc2)
	{
		unorderedSet.insert(name);
	}

	std::cout << "\nThese are the elements of the unordered_set (with their hash value):\n";
	// TODO: 1g. Again print all the elements together with their hash value, 
	for (const std::string& name : unorderedSet)
	{
		std::cout << name << ' ' << GetHashValue(name) << '\n';
	}

	// TODO: 1h. Print the buckets and have a look at the output
	PrintBuckets(unorderedSet);

	// TODO: 1i. Erase the cities that have a name length >= 8 and print the unordered_set elements after this erase 
	DeleteCityNamesWithLenght8OrMore(unorderedSet);

	for (const std::string& name : unorderedSet)
	{
		std::cout << name << "\n";
	}
}

void DeleteCityNamesWithLenght8OrMore(std::unordered_set<std::string>& unorderedSet)
{
	for (const std::string& name : unorderedSet)
	{
		if (name.size() >= 8)
		{
			unorderedSet.erase(name);
			DeleteCityNamesWithLenght8OrMore(unorderedSet);
			return;
		}
	}
}

void TestUnorderedMap()
{
	std::cout << "\n--> Unordered_map of Player objects, key is the name of the player\n";
	// Given is a vector of Player objects
	std::vector<Player>  playersSrc{ Player{ "Jan", 3 },
		Player{ "Thomas", 12 },
		Player{ "Sara", 14 },
		Player{ "Kris", 8 },
		Player{ "Thomas", 6 },
		Player{ "Anna", 18 },
		Player{ "Sara", 19 }
	};

	std::cout << "\nCreate the map and then insert elements from the vector of Player objects\n";
	std::cout << "These are the elements of the vector:\n";
	// TODO: 2a. Print the players  of  vector playersSrc

	for (Player& player : playersSrc)
	{
		std::cout << player << '\n';
	}

	// TODO: 2b. Define and fill - using insert - an unordered_map of of Players (key is name) 
	// using the given vector of players as a source
	std::unordered_map<std::string, Player> unorderedMap{ };
	for (Player& player : playersSrc)
	{
		unorderedMap.insert(std::pair<std::string, Player>{player.GetName(), player});
	}

	std::cout << "\nThese are the  unordered_map elements together with their hash value\n";
	// TODO: 2c. Print all the elements together with their hash value (GetHashValue)
	for (std::pair<std::string, Player> pair : unorderedMap)
	{
		std::cout << pair.second << GetHashValue(pair.first) << '\n';
	}

	// TODO: 2d. Print the buckets (PrintBuckets) and have a look at the output
	PrintBuckets(unorderedMap);

	// TODO: 2e. Erase players with a score less than 10 
	//  and print the remaining players in the unordered_map
	//  Print the buckets
	//  Know that the moment an element is erased from within a range loop, the range loop      //  can not continue and must be ended. Ignoring that will result in a crash. 
	DeletePlayerWithScoreLessThen10(unorderedMap);

	for (std::pair<std::string, Player> pair : unorderedMap)
	{
		std::cout << pair.second << '\n';
	}

	PrintBuckets(unorderedMap);
}

void DeletePlayerWithScoreLessThen10(std::unordered_map<std::string, Player>& unorderedMap)
{
	for (const std::pair<std::string, Player> pair : unorderedMap)
	{
		if (pair.second.GetScore() < 10)
		{
			unorderedMap.erase(pair.first);
			DeletePlayerWithScoreLessThen10(unorderedMap);
			return;
		}
	}
}

void TestUnorderedMultiset()
{
	std::cout << "\n--> unordered_multiset of city names\n";
	std::vector<std::string>  namesSrc1{
		"Aalst",
		"Kortrijk",
		"Gent",
		"Antwerpen",
		"Aalst",
		"Namen",
		"Gent",
		"Hasselt" };
	std::vector<std::string>  namesSrc2{
		"Brugge",
		"Mechelen",
		"Brussel",
		"Gent",
		"Hasselt" };
	// TODO: 3. Copy here the code from TestUnorderedSet without the source vector definitions and 
	//       change the type of the container into a unordered_multiset
	//		 Notice that duplicates are allowed

	std::cout << "\nCreate and fill the unordered_set using a given vector of cities\n";
	std::cout << "These are the elements of the vector: ";
	// TODO: 1a. Print the cities of vector namesSrc1
	for (const std::string& name : namesSrc1)
	{
		std::cout << name << ' ';
	}

	// TODO: 1b. Define and fill an unordered_set of cities  
	//  using the given namesSrc1 vector as a source
	std::unordered_multiset<std::string> unorderedMultiset{};

	for (const std::string& name : namesSrc1)
	{
		unorderedMultiset.insert(name);
	}

	std::cout << "\nThese are the elements of the unordered_multiset (with their hash value):\n";
	// TODO: 1c. Print all the elements together with their hash value, 
	// You can use the given function 'GetHashValue'
	for (const std::string& name : unorderedMultiset)
	{
		std::cout << name << ' ' << GetHashValue(name) << '\n';
	}

	// TODO: 1d. Print the buckets using the given function 'PrintBuckets'
	// and have a look at the output
	PrintBuckets(unorderedMultiset);

	std::cout << "\nInsert another vector of city names into the unordered_multiset\n";
	std::cout << "These are the elements of this vector: ";
	// TODO: 1e. Print the cities of vector namesSrc2
	for (const std::string& name : namesSrc2)
	{
		std::cout << name << ' ';
	}

	// TODO: 1f. Insert the cities from the vector namesSrc2 into the unordered_set
	for (const std::string& name : namesSrc2)
	{
		unorderedMultiset.insert(name);
	}

	std::cout << "\nThese are the elements of the unordered_multiset (with their hash value):\n";
	// TODO: 1g. Again print all the elements together with their hash value, 
	for (const std::string& name : unorderedMultiset)
	{
		std::cout << name << ' ' << GetHashValue(name) << '\n';
	}

	// TODO: 1h. Print the buckets and have a look at the output
	PrintBuckets(unorderedMultiset);

	// TODO: 1i. Erase the cities that have a name length >= 8 and print the unordered_set elements after this erase 
	DeleteCityNamesWithLenght8OrMore(unorderedMultiset);

	for (const std::string& name : unorderedMultiset)
	{
		std::cout << name << "\n";
	}
}

void DeleteCityNamesWithLenght8OrMore(std::unordered_multiset<std::string>& unorderedMultiset)
{
	for (const std::string& name : unorderedMultiset)
	{
		if (name.size() >= 8)
		{
			unorderedMultiset.erase(name);
			DeleteCityNamesWithLenght8OrMore(unorderedMultiset);
			return;
		}
	}
}

void TestUnorderedMultimap()
{
	std::cout << "\n--> unordered_multimap of Player objects, key is the name of the player\n";
	std::vector<Player>  playersSrc{ Player{ "Jan", rand() },
		Player{ "Thomas", rand() },
		Player{ "Sara", rand() },
		Player{ "Kris", rand() },
		Player{ "Thomas", rand() },
		Player{ "Anna", rand() },
		Player{ "Sara", rand() }
	};

	// TODO: 4. Copy here the code from TestUnorderedMap without the source vector definition and 
	//       change the type of the container into a unordered_multimap
	//		 Notice that duplicates are allowed

	std::cout << "\nCreate the map and then insert elements from the vector of Player objects\n";
	std::cout << "These are the elements of the vector:\n";
	// TODO: 2a. Print the players  of  vector playersSrc

	for (Player& player : playersSrc)
	{
		std::cout << player << '\n';
	}

	// TODO: 2b. Define and fill - using insert - an unordered_map of of Players (key is name) 
	// using the given vector of players as a source
	std::unordered_multimap<std::string, Player> unorderedMap{ };
	for (Player& player : playersSrc)
	{
		unorderedMap.insert(std::pair<std::string, Player>{player.GetName(), player});
	}

	std::cout << "\nThese are the  unordered_multimap elements together with their hash value\n";
	// TODO: 2c. Print all the elements together with their hash value (GetHashValue)
	for (std::pair<std::string, Player> pair : unorderedMap)
	{
		std::cout << pair.second << GetHashValue(pair.first) << '\n';
	}

	// TODO: 2d. Print the buckets (PrintBuckets) and have a look at the output
	PrintBuckets(unorderedMap);

	// TODO: 2e. Erase players with a score less than 10 
	//  and print the remaining players in the unordered_map
	//  Print the buckets
	//  Know that the moment an element is erased from within a range loop, the range loop      //  can not continue and must be ended. Ignoring that will result in a crash. 
	DeletePlayerWithScoreLessThen10(unorderedMap);

	for (std::pair<std::string, Player> pair : unorderedMap)
	{
		std::cout << pair.second << '\n';
	}

	PrintBuckets(unorderedMap);
}

void DeletePlayerWithScoreLessThen10(std::unordered_multimap<std::string, Player>& unorderedMultimap)
{
	for (const std::pair<std::string, Player> pair : unorderedMultimap)
	{
		if (pair.second.GetScore() < 10)
		{
			unorderedMultimap.erase(pair.first);
			DeletePlayerWithScoreLessThen10(unorderedMultimap);
			return;
		}
	}
}

#pragma region HelperDefinitions
size_t GetHashValue(const std::string& text)
{
	std::hash<std::string> hashFunction;
	return hashFunction(text);
}
template <typename T>
void PrintBuckets(const T& container)
{
	// Basic data
	std::cout << "\nBucket information\n";
	std::cout << "Nr. buckets: " << container.bucket_count() << ", nr. elements: " << container.size() << '\n';
	std::cout << "Load factor: " << container.load_factor() << '\n';
	std::cout << "Max load factor: " << container.max_load_factor() << '\n';

	// The buckets that contain values
	for (size_t i{ 0 }; i < container.bucket_count(); ++i)
	{
		if (container.begin(i) != container.end(i))
		{
			std::cout << "Bucket " << i << ": ";
			for (auto it = container.begin(i); it != container.end(i); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}
#pragma endregion HelperDefinitions