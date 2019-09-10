#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
#include <iostream>
#include "Node.h"

#define PRIME1 16890581;
#define PRIME2 17027399;

struct HashMap
{
	HashMap() {};

	std::vector<Node*> newMap;

	unsigned int a, b, c, p1, p2, seed;
};

#endif