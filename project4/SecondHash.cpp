#include "SecondHash.h"
using namespace std;



SecondHash::SecondHash()
{
}

SecondHash::SecondHash(unsigned int prime2, unsigned int seedx, vector<Node*> fails)
{
	p2 = prime2;
	seed = seedx;
	insert(fails);
}

SecondHash::~SecondHash()
{
}

void SecondHash::insert(vector<Node*> fails)
{
	//inc seed and regen a,b
	newMap.resize(fails.size() * fails.size());
	srand(seed);
	a = (rand() % p2) + 1;
	b = rand() % p2;

	//hash
	for (unsigned int i = 0; i < fails.size(); i++) {
		unsigned int loc = 0;
		loc = ((((a * fails.at(i)->hashVal) + b) % p2) % newMap.size());
		if (newMap.at(loc) == nullptr) {
			newMap.at(loc) = fails.at(i);
		}
		else {
			//start over
			seed++;
			tries++;
			newMap.clear();
			insert(fails);
			break;
		}
	}
}
