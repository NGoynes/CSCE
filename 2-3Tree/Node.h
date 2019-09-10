#ifndef NODE_H
#define NODE_H

/* Node structure for use in 2-3 trees */
template <typename DataType>
struct Node
{
	/* Your members/methods here... */
	Node() : key1(NULL), key2(NULL), parent(nullptr), left(nullptr),
		middle(nullptr), right(nullptr), size(0) {}

	Node(DataType data) : key1(data), key2(NULL), parent(nullptr), left(nullptr),
		middle(nullptr), right(nullptr), size(1) {}

    DataType key1;

    DataType key2;

    Node* parent;

    Node* left;

    Node* middle;

    Node* right;

	unsigned int size;

};

#endif
