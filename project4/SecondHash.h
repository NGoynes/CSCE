#ifndef SECONDHASH_H
#define SECONDHASH_H
#include "HashMap.h"
#include <vector>
struct SecondHash : public HashMap
{
	SecondHash();

	SecondHash(unsigned int, unsigned int, std::vector<Node*>);

	~SecondHash();

	void insert (std::vector<Node*>);

	unsigned int tries = 1;
};

#endif
