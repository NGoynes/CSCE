#include "Tree.h"

#ifndef TREE_CPP
#define TREE_CPP

/* Stubs for the tree's methods */

template <typename DataType, typename Compare>
Tree<DataType, Compare>::Tree()
{
    /* Your code here... */
	//default constructor
    root = nullptr;
	treeSize = 0;
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::destruct(Node<DataType>* n)
{
	/* Your code here... */
	//copy every node from existing tree to this tree
	if (n != nullptr)
	{
		destruct(n->left);
		destruct(n->middle);
		destruct(n->right);
		delete(n);
	}
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::copy(Node<DataType>* n)
{
	/* Your code here... */
	//copy every node from existing tree to this tree
	if (n != nullptr)
	{
		if (n->key1 != NULL)
		{
			insert(n->key1);
		}
		if (n->key2 != NULL)
		{
			insert(n->key2);
		}
		copy(n->left);
		copy(n->middle);
		copy(n->right);
	}
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::Tree(const Tree<DataType, Compare> &other)
{
	copy(this->root);
}

template <typename DataType, typename Compare>
Tree<DataType, Compare> &
Tree<DataType, Compare>::operator=(const Tree<DataType, Compare> &other)
{
    /* Your code here... */
	//copy every node from existing tree to this tree
	destruct(this->root);
	copy(other.root);
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::~Tree()
{
    /* Your code here... */
	//destructor
	//delete every node in the tree
	destruct(this->root);
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insert(const DataType data)
{
	treeSize++;
	if (root == nullptr)
	{
		Node<DataType>* n = new Node<DataType>(data);
		root = n;
	}
	else if (isLeaf(root))
	{
		if (root->size == 1)
		{
			insertTwo(root, data);
		}
		else
		{
			Node<DataType>* n = new Node<DataType>(data);
			root = splitter(root, n, 0);
		}
	}
	else
	{
		insertHelp(root, data);
	}
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insertTwo(Node<DataType>* n, const DataType data)
{
	if (Compare()(data, n->key1))
	{
		n->key2 = n->key1;
		n->key1 = data;
	}
	else
	{
		n->key2 = data;
	}
	n->size = 2;
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insertHelp(Node<DataType>* n, DataType data)
{
	if (isLeaf(n))
	{
		if (n->size == 1)
		{
			insertTwo(n, data);
		}
		else
		{
			int loc;
			Node<DataType>* higher = new Node<DataType>(data);
			loc = childFind(n->parent, n);
			higher = splitter(n, higher, loc);
			while (n->parent != root)
			{
				if (n->parent->size == 1)
				{
					insertTwo(n->parent, higher->key1);
					int loc;
					loc = childFind(n->parent, n);
					if (loc == 0)
					{
						n->parent->left = higher->left;
						n->parent->middle = higher->right;
					}
					else if (loc == 2)
					{
						n->parent->middle = higher->left;
						n->parent->right = higher->right;
					}
					higher->right->parent = n->parent;
					higher->left->parent = higher->right->parent;
					break;
				}
				else
				{
					loc = childFind(n->parent, n);
					n = n->parent;
					higher = splitter(n, higher, loc);
				}
			}
			if (n->parent == root)
			{
				loc = childFind(n->parent, n);
				if (n->parent->size == 1)
				{
					insertTwo(n->parent, higher->key1);
					if (loc == 0)
					{
						n->parent->left = higher->left;
						n->parent->middle = higher->right;
					}
					else if (loc == 2)
					{
						n->parent->middle = higher->left;
						n->parent->right = higher->right;
					}
					higher->right->parent = n->parent;
					higher->left->parent = higher->right->parent;
				}
				else
				{
					loc = childFind(n->parent, n);
					n = n->parent;
					root = splitter(n, higher, loc);
				}
			}
		}
	}
	else
	{
		if (n->size == 1)
		{
			if (Compare()(data, n->key1))
			{
				insertHelp(n->left, data);
			}
			else
			{
				insertHelp(n->right, data);
			}
		}
		else
		{
			if (Compare()(data, n->key1))
			{
				insertHelp(n->left, data);
			}
			else if (!Compare()(data, n->key2))
			{
				insertHelp(n->right, data);
			}
			else
			{
				insertHelp(n->middle, data);
			}
		}
	}
}

template <typename DataType, typename Compare>
Node<DataType>* Tree<DataType, Compare>::splitter(Node<DataType>* n, Node<DataType>* d, const int loc)
{
	Node<DataType>* store[4];
	if (loc == 0)
	{
		store[0] = d->left;
		store[1] = d->right;
		store[2] = n->middle;
		store[3] = n->right;
	}
	else if (loc == 2)
	{
		store[0] = n->left;
		store[1] = n->middle;
		store[2] = d->left;
		store[3] = d->right;
	}
	else
	{
		store[0] = n->left;
		store[1] = d->left;
		store[2] = d->right;
		store[3] = n->right;
	}

	DataType* median = sorter(n->key1, n->key2, d->key1);

	Node<DataType>* higher = new Node<DataType>(median[1]);
	Node<DataType>* left = new Node<DataType>(median[0]);
	Node<DataType>* right = new Node<DataType>(median[2]);

	higher->left = left;
	higher->right = right;
	left->parent = higher;
	right->parent = higher;

	if (store[0] != nullptr)
	{
		left->left = store[0];
		left->right = store[1];
		store[1]->parent = left;
		store[0]->parent = store[1]->parent;
		right->left = store[2];
		right->right = store[3];
		store[3]->parent = right;
		store[2]->parent = store[3]->parent;
	}

	return higher;
}

template <typename DataType, typename Compare>
int Tree<DataType, Compare>::childFind(const Node<DataType>* p, const Node<DataType>* n) const
{
	if (p->left == n)
	{
		return 0;
	}
	else if (p->middle == n)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

template <typename DataType, typename Compare>
DataType* Tree<DataType, Compare>::sorter(const DataType a, const DataType b, const DataType c)
{
	DataType* median = new DataType[3];
	DataType temp;
	median[0] = a;
	median[1] = b;
	median[2] = c;

	if (Compare()(median[1], median[0]))
	{
		temp = median[0];
		median[0] = median[1];
		median[1] = temp;
	}

	if (Compare()(c, median[1]))
	{
		temp = median[1];
		median[1] = median[2];
		median[2] = temp;
		if (Compare()(median[1], median[0]))
		{
			temp = median[0];
			median[0] = median[1];
			median[1] = temp;
		}
	}

	return median;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::empty() const
{
    /* Your code here... */
	//all this function does is determine whether the tree is empty or not
	return (root == nullptr);
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::isLeaf(Node<DataType>* n) const
{
	return (n->left == nullptr && n->middle == nullptr && n->right == nullptr);
}

template <typename DataType, typename Compare>
size_t Tree<DataType, Compare>::size() const
{
    /* Your code here... */
	//this function will find the size of a tree
	//it will return the sum of data items in the tree
    return treeSize;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator Tree<DataType, Compare>::begin()
{
    /* Your code here... */
	//this function returns the smallest element of the tree as an iterator
	Tree<DataType, Compare>::iterator* i = new Tree<DataType, Compare>::iterator();
	i->curr = root;
	while (i->curr->left != nullptr)
	{
		i->curr = i->curr->left;
	}
	i->kIndex = 0;
    return *i;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator Tree<DataType, Compare>::end()
{
	/* Your code here... */
	//this function returns the largest element of the tree as an iterator
	Tree<DataType, Compare>::iterator* i = new Tree<DataType, Compare>::iterator();
	i->curr = root;
	while (i->curr->right != nullptr)
	{
		i->curr = i->curr->right;
	}
	if (i->curr->key2 != NULL)
	{
		i->kIndex = 1;
	}
	else
	{
		i->kIndex = 0;
	}
	return *i;
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator
Tree<DataType, Compare>::find_first(KeyType key)
{
    /* Your code here... */
	//this function finds the first occurence of a key that is given
	//and returns the location of that key
	//if no item exists then return end
	for (iterator i = this->begin(); i != this->end(); i++)
	{
		if ((Compare()(i.curr->key1, key) == false) && (Compare()(key, i.curr->key1) == false))
		{
			i.kIndex = 0;
			return i;
		}
		else if ((Compare()(i.curr->key2, key) == false) && (Compare()(key, i.curr->key2) == false))
		{
			i.kIndex = 1;
			return i;
		}
	}
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator
Tree<DataType, Compare>::find_last(KeyType key)
{
    /* Your code here... */
	//this function finds the last occurence of a key that is given
	//and returns the location of that key
	//if no item exists then return end
	iterator last;
	iterator end = this->end();
	for (iterator i = this->begin(); i != end; i++)
	{
		if ((Compare()(i.curr->key1, key) == false) && (Compare()(key, i.curr->key1) == false))
		{
			last = i;
			last.kIndex = 0;
		}
		if ((Compare()(i.curr->key2, key) == false) && (Compare()(key, i.curr->key2) == false))
		{
			last = i;
			last.kIndex = 1;
		}
	}
	return last;
}

template <typename DataType, typename Compare>
template <typename KeyType>
std::pair<typename Tree<DataType, Compare>::iterator,
          typename Tree<DataType, Compare>::iterator>
Tree<DataType, Compare>::find_range(KeyType key)
{
    /* Your code here... */
	//this function is sort of a combination of find_first and find_last
	//it will return a pair of iterators, the first pointing to find_first
	//and the second pointing to find_last of a given key
	iterator first = this->find_first();
	iterator last = this->find_last();
    return std::make_pair(first, last);
}

template <typename DataType, typename Compare>
std::ostream &operator<<(std::ostream &stream,
                         const Tree<DataType, Compare> &tree)
{
    /* Your code here... */
	//this will print a level order traversal of the tree given
    unsigned int i = 0;
	if (tree.root == nullptr)
	{
		return stream;
	}
	else
	{
		std::queue<Node<DataType>*> queue;
		queue.push(tree.root);

		while (queue.empty() == false)
		{
			int count = queue.size();

            stream << "Level " << i << std::endl;
			while (count > 0)
			{
				Node<DataType>* n = queue.front();
				if (n->key1 != NULL)
				{
					stream << "(" << n->key1;
				}
				if (n->key2 != NULL)
				{
					stream << ", " << n->key2 << ")" << " ";
				}
                else
                {
                    stream << ")" << "";
                }
                stream << std::endl;
				queue.pop();
				if (n->left != nullptr)
				{
					queue.push(n->left);
				}
				if (n->middle != nullptr)
				{
					queue.push(n->middle);
				}
				if (n->right != nullptr)
				{
					queue.push(n->right);
				}
				count--;
			}
            i++;
		}
	}
    return stream;
}

#endif
