#include "Tree.h"

#ifndef TREE_ITERATOR_CPP
#define TREE_ITERATOR_CPP

template <typename DataType, typename Compare>
Tree<DataType, Compare>::iterator::iterator()
{
	/* Your code here... */
	//default constructor
	curr = nullptr;
	kIndex = 0;
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::iterator::iterator(const iterator &other)
{
	/* Your code here... */
	//copy constructor
	curr = other.curr;
	kIndex = other.kIndex;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::operator=(const iterator &other)
{
	/* Your code here... */
	//overloaded operator= constructor
	curr = other.curr;
	kIndex = other.kIndex;
	return *this;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::iterator::operator==(const iterator &other) const
{
	/* Your code here... */
	//overloaded comparison== operation
	if (this->kIndex == 0 && other->kIndex == 0)
	{
		if ((Compare()(this->curr->key1, other->curr->key1) == false) && (Compare()(other->curr->key1, this->curr->key1) == false))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (this->kIndex == 1 && other->kIndex == 1)
	{
		if ((Compare()(this->curr->key2, other->curr->key2) == false) && (Compare()(other->curr->key2, this->curr->key2) == false))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::iterator::operator!=(const iterator &other) const
{
	/* Your code here... */
	//overloaded operator!=
	if (this->kIndex == 0 && other.kIndex == 0)
	{
		if ((Compare()(this->curr->key1, other.curr->key1) == false) && (Compare()(other.curr->key1, this->curr->key1) == false))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (this->kIndex == 1 && other.kIndex == 1)
	{
		if ((Compare()(this->curr->key2, other.curr->key2) == false) && (Compare()(other.curr->key2, this->curr->key2) == false))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

template <typename DataType, typename Compare>
DataType Tree<DataType, Compare>::iterator::operator*() const
{
	/* Your code here... */
	//overloaded iterator dereference
	if (kIndex == 0)
	{
		return this->curr->key1;
	}
	else
	{
		return this->curr->key2;
	}
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::operator++()
{
	/* Your code here... */
	//overloaded ++ operation
	//get next
	if ((curr->key2 == NULL) && (curr->right != nullptr))
	{
		curr = curr->right;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((curr->key2 == NULL && curr->right == nullptr) || ((kIndex == 1) && (curr->right == nullptr) && (curr->key2 != NULL)))
	{
		while (curr->parent != nullptr)
		{
			if (curr->parent->left == curr)
			{
				curr = curr->parent;
				kIndex = 0;
				return *this;
			}
			else if ((curr->parent->key2 != NULL) && (curr->parent->left == curr))
			{
				curr = curr->parent;
				kIndex = 0;
				return *this;
			}
			else if ((curr->parent->key2 != NULL) && (curr->parent->middle == curr))
			{
				curr = curr->parent;
				kIndex = 1;
				return *this;
			}
			curr = curr->parent;
		}
	}
	else if ((kIndex == 0) && (curr->middle != nullptr) && (curr->key2 != NULL))
	{
		curr = curr->middle;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((kIndex == 1) && (curr->right != nullptr) && (curr->key2 != NULL))
	{
		curr = curr->right;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((kIndex == 0) && (curr->middle == nullptr) && (curr->key2 != NULL))
	{
		kIndex = 1;
		return *this;
	}
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator
Tree<DataType, Compare>::iterator::operator++(int unused)
{
	if ((curr->key2 == NULL) && (curr->right != nullptr))
	{
		curr = curr->right;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((curr->key2 == NULL && curr->right == nullptr) || ((kIndex == 1) && (curr->right == nullptr) && (curr->key2 != NULL)))
	{
		while (curr->parent != nullptr)
		{
			if (curr->parent->left == curr)
			{
				curr = curr->parent;
				kIndex = 0;
				return *this;
			}
			else if ((curr->parent->key2 != NULL) && (curr->parent->left == curr))
			{
				curr = curr->parent;
				kIndex = 0;
				return *this;
			}
			else if ((curr->parent->key2 != NULL) && (curr->parent->middle == curr))
			{
				curr = curr->parent;
				kIndex = 1;
				return *this;
			}
			curr = curr->parent;
		}
	}
	else if ((kIndex == 0) && (curr->middle != nullptr) && (curr->key2 != NULL))
	{
		curr = curr->middle;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((kIndex == 1) && (curr->right != nullptr) && (curr->key2 != NULL))
	{
		curr = curr->right;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		kIndex = 0;
		return *this;
	}
	else if ((kIndex == 0) && (curr->middle == nullptr) && (curr->key2 != NULL))
	{
		kIndex = 1;
		return *this;
	}
}


#endif
