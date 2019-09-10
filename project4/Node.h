#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

struct Node
{
	Node() : info(""), coords(""), hashVal(0) {};

	Node(std::string name) : info(name), coords(""), hashVal(0) {};

	std::string print() const;

	std::string info;

	std::string coords;

	long hashVal;

	class SecondHash* secondMap = nullptr;

	std::vector<Node*> collisions;
};

std::ostream& operator<<(std::ostream& os, const Node& node);

#endif