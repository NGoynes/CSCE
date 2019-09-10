#include "MainHash.h"
#include <sstream>
using namespace std;



MainHash::MainHash()
{
	p1 = PRIME1;
	p2 = PRIME2;
	seed = 0;
	srand(seed);
	c = (rand() % p1) + 1;
	a = (rand() % p2) + 1;
	b = rand() % p2;
}

MainHash::MainHash(vector<Node*> table)
{
	p1 = PRIME1;
	p2 = PRIME2;
	seed = 0;
	srand(seed);
	c = (rand() % p1) + 1;
	a = (rand() % p2) + 1;
	b = rand() % p2;
	insert(table);
}


MainHash::~MainHash()
{

}

void MainHash::insert(vector<Node*> table)
{
	vector<Node*> map(table.size());
	for (unsigned int i = 0; i < table.size(); i++) {
		//get hashval
		unsigned long hashVal = 0;
		string name = table.at(i)->info;
		for (unsigned int j = 0; j < name.length(); j++) {
			hashVal = ((hashVal * c) + name.at(j)) % p1;
		}
		table.at(i)->hashVal = hashVal;

		//hash
		unsigned int loc = 0;
		loc = ((a * table.at(i)->hashVal + b) % p2) % table.size();
		if (map.at(loc) == nullptr) {
			map.at(loc) = table.at(i);
		}
		else {
			//insert into collisions vector
			map.at(loc)->collisions.push_back(table.at(i));
		}
	}
	newMap = map;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (newMap.at(i) != nullptr) {
			if (newMap.at(i)->collisions.size() != 0) {
				newMap.at(i)->secondMap = new class SecondHash(p2, seed, newMap.at(i)->collisions);
			}
		}
	}
}

unsigned int MainHash::getCollisions(unsigned int val) const
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (val == 0) {
			if (newMap.at(i) == nullptr) {
				count++;
			}
		}
		else if (newMap.at(i) != nullptr) {
			if (val == 1) {
				if (newMap.at(i)->collisions.size() == 0) {
					count++;
				}
			}
			else {
				if (newMap.at(i)->collisions.size() + 1 == val) {
					count++;
				}
			}
		}
	}

	return count;
}

unsigned int MainHash::getMax() const
{
	unsigned int loc = 0;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (newMap.at(i) != nullptr && newMap.at(i)->collisions.size() != 0) {
			if (newMap.at(i)->collisions.size() + 1 > newMap.at(loc)->collisions.size()) {
				loc = i;
			}
		}
	}

	return loc;
}

unsigned int MainHash::getTries(unsigned int val) const
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (newMap.at(i) != nullptr && newMap.at(i)->collisions.size() != 0) {
			if (newMap.at(i)->secondMap->tries == val) {
				count++;
			}
		}
	}
	return count;
}

unsigned int MainHash::getTables() const
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (newMap.at(i) != nullptr && newMap.at(i)->collisions.size() != 0) {
			count++;
		}
	}

	return count;
}

float MainHash::getAverage() const
{
	float sum = 0.0;
	for (unsigned int i = 0; i < newMap.size(); i++) {
		if (newMap.at(i) != nullptr && newMap.at(i)->collisions.size() != 0) {
			sum += newMap.at(i)->secondMap->tries;
		}
	}

	return sum / getTables();
}

string MainHash::search(string city) const
{
	stringstream searchString;
	//get hashval
	unsigned long hashVal = 0;
	for (unsigned int i = 0; i < city.length(); i++) {
		hashVal = ((hashVal * c) + city.at(i)) % p1;
	}

	//hash to find location
	unsigned int firstLoc = 0;
	firstLoc = ((a * hashVal + b) % p2) % newMap.size();
	if (newMap.at(firstLoc) == nullptr) {
		searchString << "city details: Key = n/a" << endl;
		searchString << "n/a";
		return searchString.str();
	}
	if (newMap.at(firstLoc)->info == city) {
		searchString << "city details: Key = " << firstLoc << endl;
		searchString << *newMap.at(firstLoc);
		return searchString.str();
	}
	else {
		if (newMap.at(firstLoc)->collisions.size() == 0) {
			searchString << "city details: Key = n/a" << endl;
			searchString << "n/a";
			return searchString.str();
		}
		else {
			//hash
			unsigned int secLoc = 0;
			secLoc = ((newMap.at(firstLoc)->secondMap->a * hashVal + newMap.at(firstLoc)->secondMap->b) % p2) % newMap.at(firstLoc)->secondMap->newMap.size();
			if (newMap.at(firstLoc)->secondMap->newMap.at(secLoc)->info == city) {
				searchString << "city details: Key = " << firstLoc << endl;
				searchString << *newMap.at(firstLoc)->secondMap->newMap.at(secLoc);
				return searchString.str();
			}
			else {
				searchString << "city details: Key = n/a" << endl;
				searchString << "n/a";
				return searchString.str();
			}
		}
	}
}

string MainHash::print() const
{
	stringstream outputString;
	unsigned int loc = getMax();
	outputString << "p1: " << p1 << endl;
	outputString << "p2: " << p2 << endl;
	outputString << "a: " << a << endl;
	outputString << "b: " << b << endl;
	outputString << "c: " << c << endl << endl;
	outputString << "number of cities: " << newMap.size() << endl;
	outputString << "maximum collisions: " << newMap.at(loc)->collisions.size() + 1 << endl;
	for (unsigned int i = 0; i < 10; i++) {
		outputString << "# primary slots with " << i << " cities: " << getCollisions(i) << endl;
	}
	outputString << "** cities in the slot with most collisions **" << endl;
	outputString << *newMap.at(loc) << endl;
	for (unsigned int i = 0; i < newMap.at(loc)->collisions.size(); i++) {
		outputString << *newMap.at(loc)->collisions.at(i) << endl;
	}
	for (unsigned int i = 1; i <= 10; i++) {
		outputString << "# secondary hash tables trying " << i << " hash functions: " << getTries(i) << endl;
	}
	outputString << "number of secondary hash tables with more than one item: " << getTables() << endl;
	outputString << "average # of hash functions tried: " << getAverage();
	return outputString.str();
}

ostream& operator<<(ostream& os, const MainHash& table)
{
	os << table.print();
	return os;
}
