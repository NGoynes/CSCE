#ifndef MAINHASH_H
#define MAINHASH_H
#include "HashMap.h"
#include "SecondHash.h"
#include <vector>

struct MainHash : public HashMap
{
	MainHash();

	MainHash(std::vector<Node*>);

	~MainHash();

	std::vector<Node*> getMap() const { return newMap; };

	unsigned int getCollisions(unsigned int) const;

	unsigned int getMax() const;

	unsigned int getTries(unsigned int) const;

	void insert(std::vector<Node*>);

	unsigned int getTables() const;

	float getAverage() const;

	std::string search(std::string) const;

	std::string print() const;
};

std::ostream& operator<<(std::ostream& os, const MainHash& table);

#endif
