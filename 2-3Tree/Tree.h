#ifndef TREE_H
#define TREE_H

#include <iterator>
#include <ostream>
#include <queue>
#include <utility>
#include "Node.h"

/*
 * 2-3 Tree class
 * All nodes in a 2-3 tree either have 1 or 2 keys.
 * Internal nodes that have 1 key have 2 children.
 * Internal nodes that have 2 keys have 3 children.
 * All leaves are at the same level.
 *
 * For every 2 node n, all modes to the left of n have
 * value less than or equal to n's value, and all values
 * to the right of n have value greater than or equal to
 * n's value.
 *
 * For every 3 node n with key's k1 and k2, all nodes in
 * n's left subtree have value less than k1, all nodes in
 * n's middle subtree have value between, possibly equal to,
 * k1 and k2, and all nodes in n's right subtree have value
 * greater than or equal to k2.
 *
 * Template params:
 * DataType - type of data to be stored in the tree.
 * Compare - functor to compare data so it is stored
 * in sorted order. Calling Compare()(a, b) returns
 * true if a is less than b, and false otherwise.
 */
template <typename DataType, typename Compare = std::less<DataType> >
class Tree
{
public:
    /* Iterator for the tree */
    class iterator;

    /* Default Constructor - construct an empty tree */
    Tree();

    /* Copy constructor */
    Tree(const Tree<DataType, Compare> &other);

    /* Copy assignment */
    Tree &operator=(const Tree<DataType, Compare> &other);

    /* Destructor */
    ~Tree();

	/* Deletes an entire tree node by node */
	void destruct(Node<DataType>* n);

	/* Copies an entire tree node by node */
	void copy(Node<DataType>* n);

    /* Insert the given data into the tree */
    void insert(const DataType data);

	/* Another helper function! */
	void insertTwo(Node<DataType>* n, const DataType data);

	/* Our helper for the insert function */
	void insertHelp(Node<DataType>* n, const DataType data);

	/* This function will determine if the current node is the left, middle, or right of a parent */
	int childFind(const Node<DataType>* p, const Node<DataType>* n) const;

	/* this will split a node for us */
	Node<DataType>* splitter(Node<DataType>* n, Node<DataType>* d, const int loc);

    /* Return whether or not the tree is empty */
    bool empty() const;

	/* Return whether or not a node is a leaf */
	bool isLeaf(Node<DataType>* n) const;

	/* This helps our splitter by sorting three datatypes */
	DataType* sorter(const DataType a, const DataType b, const DataType c);

    /* Return the number of data items stored in the tree */
    size_t size() const;

    /* Return an iterator pointing to the first element in the tree */
    iterator begin();

    /* Return an iterator past the end of the tree */
    iterator end();

    /* Return an iterator pointing to the first item in the tree equal to key */
    template <typename KeyType>
    iterator find_first(KeyType key);

    /* Return an iterator pointing to the last item in the tree equal to key */
    template <typename KeyType>
    iterator find_last(KeyType key);

    /*
     * Return a pair of iterators pointing to the first item
     * in the tree equal to key, and past the last item
     * in the tree equal to key.
     */
    template <typename KeyType>
    std::pair<iterator, iterator> find_range(KeyType key);

    /* Level order print of the tree */
    template <typename DataType_, typename Compare_>
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Tree<DataType_, Compare_> &tree);

private:
    Node<DataType>* root;
	unsigned int treeSize;
};

/* Tree iterator that performs in-order traversals */
template <typename DataType, typename Compare>
class Tree<DataType, Compare>::iterator
    : public std::iterator<std::forward_iterator_tag, DataType>
{
public:
    /* Default constructor - creates past-the-end iterator */
    iterator();

    /* Copy constructor */
    iterator(const iterator &other);

    /* Copy assignment */
    iterator &operator=(const iterator &other);

    /* Return whether or not two iterators are pointing at the same place */
    bool operator==(const iterator &other) const;

    /* Return whether or not two iterators are not pointing at the same place */
    bool operator!=(const iterator &other) const;

    /* Return the data the iterator is pointing to */
    DataType operator*() const;

    /* Advance to the current data's successor */
    iterator &operator++();

    /* Advance to the current data's successor */
    iterator operator++(int unused);

	Node<DataType>* curr;

	int kIndex;
};

#include "Tree.cpp"
#include "TreeIterator.cpp"

#endif
