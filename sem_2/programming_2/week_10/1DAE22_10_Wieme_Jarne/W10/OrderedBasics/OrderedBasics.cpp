#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include "Player.h"
#include <iomanip>
#include <set> 
#include <map>

struct City
{
	explicit City(std::string name, int population) :name{ name }, population{ population } {};
	std::string name;
	int population;
};

void TestPair();
void TestSetOfIntegers();
void DeleteElementsFromSetDivisibleBy3(std::set<int>& set);
void TestSetOfPlayers();
void TestMultiset();
void TestMapOfGameRankings();
void TestMapOfCities();
void TestMultimap();

#pragma region HelperDeclarations
void PrintNumbers(const std::vector<int>& numbers);
void PrintNumber(int nr);
std::ostream& operator<<(std::ostream& out, const City& city);
void PrintCityPair(const std::pair<std::string, City> & p);
#pragma endregion

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << std::boolalpha;

	// Explore the ordered associative containers
	TestPair( );

	TestSetOfIntegers( );
	TestSetOfPlayers( );

	TestMultiset( );
	
	TestMapOfGameRankings( );
	TestMapOfCities( );
	
	TestMultimap( );

	// Wait
	std::cout << "\nPush ENTER to continue";
	std::cin.get();

	return 0;
}

void TestPair()
{
	std::cout << "\n--> TestPair\n";
	// We will consider following pairs [gameName, rating] e.g.
	//    ["Andromeda",73.62f]
	//    ["World of Warcraft",91.89f]

	std::cout << "There are many ways to create a pair\n";
	// TODO: 1a. Create 2 std::pair<std::string, float> type objects pair1 and pair2
	// - pair1: Using the 2 arg constructor
	// - pair2: Using the result of std::make_pair as argument of the pair constructor
	std::pair<std::string, float> pair1{ "Andromeda", 73.62f };
	std::pair<std::string, float> pair2{ std::make_pair<std::string, float>("World of Warcraft", 91.89f) };

	std::cout << "\nThere are 2 ways to get the values of a pair\n";
	// TODO: 1b. Print the  pairs on the console
	// - One using first, second member
	// - The other using std::get<0> and std::get<1>
	std::cout << '[' << pair1.first << ' ' << pair1.second << "]\n";
	std::cout << '[' << std::get<0>(pair2) << ' ' << std::get<1>(pair2) << "]\n";
}

void TestSetOfIntegers()
{
	std::cout << "\n--> Set of integer elements\n";

	// TODO: 2a. Create an empty set of integer type elements
	std::set<int> set{};

	// TODO: 2b. Using the insert function of the set, add the multiples of value 10 in [10, 100] 
	for (int value{ 10 }; value <= 100; value += 10)
	{
		set.insert(value);
	}

	// TODO: 2c. Print the numbers using a ranged based for-loop, 
	//  You can use the  given function 'PrintNumber'
	std::cout << "The elements of the set\n";
	for (int value : set)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

	// TODO: 2d. Insert a number that is already in the set (e.g. the first number)
	std::cout << "\nInserting an already existing membern\n";
	std::cout << "Calling insert(10)\n";
	set.insert(10);
	std::cout << "The elements of the set\n";
	for (int value : set)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

	// TODO: 2e. Insert a number that is not yet in the set (e.g. the first number + 5)
	std::cout << "\nInserting a new member\n";
	set.insert(15);
	std::cout << "The elements of the set\n";
	for (int value : set)
	{
		PrintNumber(value);
	}
	std::cout << '\n';
	// TODO: 2f. Erase an element choose e.g. value 10 using this member function: size_type erase( const key_type& key );
	// and then print the value of the return value of calling this erase function: it is the number of elements removed
	std::cout << "\nErasing the first element, result is:\n";
	std::cout << "Calling erase(10) results in " << set.erase(10) << " removed\n";
	std::cout << "The elements of the set\n";
	for (int value : set)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

	// TODO: 2g. Erase this element again in the same way and print the result again
	std::cout << "\nErasing this element again, result is:\n";
	std::cout << "Calling once again erase(10) results in " << set.erase(10) << " removed\n";

	// TODO: 2h. Loop over the elements and erase the ones that are divisible by 3,
	std::cout << "\nErasing all the elements that are divisible by 3\n";

	DeleteElementsFromSetDivisibleBy3(set);

	std::cout << "The elements of the set\n";
	for (int value : set)
	{
		PrintNumber(value);
	}
	std::cout << '\n';
}

void DeleteElementsFromSetDivisibleBy3(std::set<int>& set)
{
	for (int value : set)
	{
		if (value % 3 == 0)
		{
			set.erase(value);
			DeleteElementsFromSetDivisibleBy3(set);
			return;
		}
	}
}

void TestSetOfPlayers()
{
	std::cout << "\n--> Set of Player objects\n";
	// TODO: 3a. Change Player::operator< function,
	// should be printed from low to high score
	std::set<Player> players;
	players.insert({
		Player{ "Devolder", "Warre", 1000 },
		Player{ "De schoenmaker", "An", 10 },
		Player{ "Janssens","Bart", 20 },
		Player{ "Janssens","Xavier", 30 } });	
	for (const Player& p : players)
	{
		std::cout << p << std::endl;
	}
}

void TestMultiset()
{
	std::cout << "\n--> Multiset of integer numbers\n";
	std::vector<int> numbersSrc{ 10,20,30,40 };
	std::cout << "These are the elements of the vector used as source: ";
	PrintNumbers(numbersSrc);

	// TODO: 4a. Create a multiset of integers using its constructor that takes iterators of the vector numbersSrc
	//       Then print the elements of the multiset using for_each
	std::multiset<int> multiset{ numbersSrc.begin(), numbersSrc.end() };

	std::cout << "Elements of the multiset: ";
	for (int value : multiset)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

	const int value{ 50 };
	const int nrTimes{ 3 };
	std::cout << "\nInserting " << nrTimes << " times the value " << value << "\n";
	// TODO: 4b. Insert the same value multiple times 
	for (int index{}; index < nrTimes; ++index)
	{
		multiset.insert(value);
	}

	std::cout << "Verify that the multiset contains " << nrTimes << " times the value " << value << "\n";
	std::cout << "These are the elements of the multiset: ";
	// TODO: 4c. Print all the multiset elements
	for (int value : multiset)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

	std::cout << "\nErase the value " << value << " that occurs multiple times in the multiset\n";
	// TODO: 4d. Call erase using this same value, and print the returned value (number of erased elements)
	std::cout << "erase(50) => " << multiset.erase(value) << " elements erased\n";
	std::cout << "Verify that the multiset doesn't contain the value " << value << " anymore\n";
	// TODO: 4e. Print all the multiset elements
	std::cout << "Elements of the multiset: ";
	for (int value : multiset)
	{
		PrintNumber(value);
	}
	std::cout << '\n';

}

void TestMapOfGameRankings()
{
	std::cout << "\n--> Map of Game rankings (key is name of game, value is the score)\n";
	// Ratings from http://www.gamerankings.com/pc/index.html

	std::cout << "\n--> How to create a map and adding elements to it";
	// TODO: 5a. Create a map, key is the name of a game, value is the score
	// Don't specify a compare function, in which case the operator< of std:string (key) is used
	std::map<std::string, float> map{ };
	// Some values
	// "League of Legends", 79.16f
	// "Andromeda", 73.62f
	// "Final Fantasy XIV", 78.54f
	// "World of Warcraft", 91.89f
	// "Grand Theft Auto", 94.39f
	// "Wild Hunt", 92.11f
	// "The Sims 3", 86.61f
	// "Fallout 4", 85.60f
	// "Grand Theft Auto: San Andreas", 91.94f

	// TODO: 5b. Add elements in 3 different ways, you can use the above data 
	// - Using the [] operator
	// - Using the insert function
	// - Using the emplace function
	map["League of Legends"] = 79.16f;
	map.insert(std::pair<std::string, float>{"Andromeda", 73.62f});
	map.emplace(std::pair<std::string, float>{"Final Fantasy XIV", 78.54f});
	map["World of Warcraft"] = 91.89f;
	map["Grand Theft Auto"] = 94.39f;
	map["Wild Hunt"] = 92.11f;
	map["The Sims 3"] = 86.61f;
	map["Fallout 4"] = 85.60f;
	map["Grand Theft Auto: San Andreas"] = 91.94f;

	// TODO: 5c. Print the elements of the map using a ranged-based for loop
	std::cout << "\nThese are the elements of the map after adding elements in 3 different ways\n";
	for (std::pair<const std::string, float>& pair : map)
	{
		std::cout << pair.first << ", " << pair.second << std::endl;
	}

	std::cout << "\n--> How to change the content of a map";
	std::cout << "\nRemove an element using erase(key), key is 'Wild Hunt'";
	// TODO: 5d. Remove an element using erase(key)
	map.erase("Wild Hunt");

	std::cout << "\nAdd an element with an already existing key but another value and check what happens\n";
	// No duplicate keys in map
	// TODO: 5e. Add an element with an already existing key and check what happens
	// - Using the [] operator
	// - Using the insert function
	// - Using the emplace function
	std::cout << "- Add 'Andromeda' with rating value 10.0, using [] operator\n";
	map["Andromeda"] = 10.f;

	std::cout << "- Adding 'League of Legends' with rating value 20.0, using insert\n";
	map.insert(std::pair<const std::string, float>{"League of Legends", 20.f});

	std::cout << "- Adding 'Grand Theft Auto' with rating value 30.0, using emplace\n ";
	map.emplace(std::pair<const std::string, float>{"Grand Theft Auto", 30.f});
	
	// TODO: 5f. Print the elements of the map using a ranged-based for loop
	std::cout << "\nThese are the elements of the map after these change operations\n";
	for (std::pair<const std::string, float>& pair : map)
	{
		std::cout << pair.first << ", " << pair.second << std::endl;
	}

	std::cout << "\n--> How to get the value of an element";
	std::cout << "\nGet the score of an existing game in 3 different ways and print the scores\n";
	// TODO: 5g. Get the score of a game in 3 different ways and print the 3 scores
	// - using []
	// - using at
	// - using find
	std::cout << "Ratings of game Andromeda " << map["Andromeda"] << ", " << map.at("Andromeda") << ", " << map.find("Andromeda")->second << '\n';

	std::cout << "\nGet the score of a not existing game in 3 different ways\n";
	// TODO: 5h. Get the score of a game in 3 different ways
	// but this time use a not existing key
	// Use this sequence:
	// - using at
	// - using find
	// - using []
	// Two of these result in an exception, one creates a new element, print the score of this element
	std::cout << "Ratings of the game notExistingGame " << map["notExistingGame"];
	// TODO: 5i. And print the elements 
	std::cout << "\nThese are the elements of the map after getting some scores\n";
	for (std::pair<const std::string, float>& pair : map)
	{
		std::cout << pair.first << ", " << pair.second << std::endl;
	}

	std::cout << "\n--> How to change the key of an element";
	std::cout << "\nRename one of the games";
	// TODO: 5j. Rename one of the games, e.g. "Final Fantasy XIV" into "Final Fantasy"
	// You have to do this in 2 steps: 
	// - First create a new element "Final Fantasy" and copy the value of  "Final Fantasy XIV" into it
	// - Then delete "Final Fantasy XIV" using erase
	map["Final Fantasy"] = map["Final Fantasy XIV"];
	map.erase("Final Fantasy XIV");

	std::cout << "\nThese are the elements of the map after changing 'Final Fantasy XIV' into 'Final Fantasy'\n";
	// TODO: 5l. Print the elements
	for (std::pair<const std::string, float>& pair : map)
	{
		std::cout << pair.first << ", " << pair.second << std::endl;
	}
}

void TestMapOfCities()
{
	std::cout << "\n--> Cities map, key is the name of a city, value is the City object\n";
	// TODO: 6a. Define this map, give it the name citiesMap
	std::map<std::string, City> citiesMap{ };

	std::cout << "\nInsert the cities from a given vector of City objects into the map using a loop\n";
	std::vector<City>  citiesSrc{
		City("Aalst",84000) ,
		City("Kortrijk",76000) ,
		City("Gent",255000) ,
		City("Antwerpen", 504000) ,
		City("Namen",111000) ,
		City("Hasselt",77000) ,
	};

	for (const City& city : citiesSrc)
	{
		citiesMap.insert(std::pair<std::string, City>{city.name, city});
	}

	// TODO: 6b. Print the elements of citiesSrc vector
	std::cout << "These are the elements of the vector:\n";
	for (const City& city : citiesSrc)
	{
		std::cout << city << '\n';
	}
	// TODO: 6c. Insert the cities from citiesSrc into the map using a loop
	

	std::cout << "\nThese are the elements of the map after the insert operation\n";
	// TODO: 6d. Print the elements of the map using a range base for loop
	// Use a helper function PrintCityPair
	for (std::pair<std::string, City> pair : citiesMap)
	{
		PrintCityPair(pair);
	}

	// TODO: 6e. Uncommenting next code line of leads to a compiler error, why?
	// You don't need to solve this error, you just have to know why it results in an error
	//std::cout << citiesMap["Namen"].population << "\n";
}

void TestMultimap()
{
	std::cout << "\n--> Multimap for an English - Dutch dictionary\n";
	//TODO: 7a. Define an English - Dutch dictionary using a multimap 
	// It contains <std::string, std::string> pairs
	std::multimap<std::string, std::string> multimap{};

	std::cout << "\nInsert elements from a source container (vector) into the multimap\n";
	std::vector<std::pair<std::string, std::string>> translations{
		{ "strange", "vreemd" },
	{ "date", "datum" },
	{ "smart", "heftig" },
	{ "right", "juist" },
	{ "smart", "bijdehand" },
	{ "strange", "onbekend" },
	{ "date", "dadel" },
	{ "right", "rechts" },
	{ "date", "afspraak" },
	};

	std::cout << "These are the elements of the vector:\n";
	std::cout.setf(std::ios::left, std::ios::adjustfield);
	std::cout << std::setw(10) << "English" << "Dutch";
	std::cout << std::setfill('-') << std::setw(20) << '\n';
	std::cout << std::setfill(' ') << '\n';
	// TODO:7b. Print the elements of translations vector
	for (const std::pair<std::string, std::string>& pair : translations)
	{
		std::cout << std::setw(10) << pair.first << pair.second << '\n';
	}

	// TODO: 7c. Add the elements from  the translations vector above. 
	for (const std::pair<std::string, std::string>& pair : translations)
	{
		multimap.insert(pair);
	}

	std::cout << "\nThese are the elements of the multimap after the insert operation\n";
	std::cout.setf(std::ios::left, std::ios::adjustfield);
	std::cout << std::setw(10) << "English" << "Dutch";
	std::cout << std::setfill('-') << std::setw(20) << '\n';
	std::cout << std::setfill(' ') << '\n';
	// TODO: 7d. Print all the elements
	// In which order are they printed ?
	for (const std::pair<std::string, std::string>& pair : multimap)
	{
		std::cout << std::setw(10) << pair.first << pair.second << '\n';
	}

	std::cout << "\nErase the elements with a specific key";
	const std::string wordEng{ "right" };
	// TODO: 7e. Erase all the values of elements having the key "right"
	multimap.erase(wordEng);
	std::cout << "\nThese are the elements of the multimap after the erase operation\n";
	// TODO: 7f. Print all the elements
	for (const std::pair<std::string, std::string>& pair : multimap)
	{
		std::cout << std::setw(10) << pair.first << pair.second << '\n';
	}
}

#pragma region HelperDefinitions
void PrintNumbers(const std::vector<int>& numbers)
{
	for (int nr : numbers)
	{
		std::cout << nr << " ";
	}
	std::cout << '\n';
}

void PrintNumber(int nr)
{
	std::cout << nr << " ";
}

std::ostream& operator<<(std::ostream& out, const City& city)
{
	out << city.name << " (" << city.population << ")";
	return out;
}

void PrintCityPair(const std::pair<std::string, City> & p)
{
	std::cout << p.second << '\n';
}
#pragma endregion
