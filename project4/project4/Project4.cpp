#include "HashMap.h"
#include "MainHash.h"
#include "SecondHash.h"
#include "Node.h"
#include <iostream>
#include <fstream>

using namespace std;

const string SEARCH_FOR_CITY = "Ringgold, GA";

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " cities_file" << endl;
		return 1;
	}
	else {
		string cities = argv[1];

		//open input file
		ifstream file;
		file.open(cities, ios_base::in);
		if (file.fail()) {
			cout << "Cities file was not successfully opened." << endl;
			exit(-1);
		}

		//read input to vector
		string line;
		vector<Node*> keys;
		while (getline(file, line)) {
			Node* node = new Node(line);
			string coords;
			getline(file, coords);
			node->coords = coords;

			keys.push_back(node);
		}

		//hash
		MainHash* table = new MainHash(keys);
		cout << *table << endl;
		cout << table->search(SEARCH_FOR_CITY) << endl;
	}
	return 0;
}
