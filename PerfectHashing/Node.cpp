#include "Node.h"
#include <sstream>

using namespace std;

string Node::print() const
{
	stringstream outputString;
	outputString << this->info << " ("
		<< this->coords << ")";
	return outputString.str();
}

ostream& operator<<(ostream& os, const Node& node)
{
	os << node.print();
	return os;
}