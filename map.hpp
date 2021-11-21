#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"

// Who gets to allocate the BSTNode ? The BSTNode itself or the map ? I guess it could be the map that allocates the
// node and then pass that node to the BSTNode functions... ?
// For instance, while inserting, the map allocates the node using a rebound allocator and pass it to the insert
// method.


namespace ft {

template <class Key, class T, class Compare = std::less<Key> > class BSTNode {
public:

	typedef Key key_type;
	typedef T value_type;
	typedef ft::pair<const key_type, value_type> pair_type;
	typedef Compare key_compare;

	BSTNode(const pair_type & pair) : _pair(&pair), _left(NULL), _right(NULL) {}

	~BSTNode() {}

	BSTNode * insert(const BSTNode * node) {
		if (!key_compare(_pair->first, node->_pair->first) && !key_compare(node->_pair->first, _pair->first)) {
			return NULL;
		}
		if (key_compare(_pair->first, node->_pair->first)) {
			if (!_left) {
				_left = node;
				return _left;
			} else {
				return _left->insert(node);
			}
		} else {
			if (!_right) {
				_right = node;
				return _right;
			} else {
				return _right->insert(node);
			}
		}
	}
	// search
	// last
	// first
	// remove

private:
	BSTNode();

	const pair_type * _pair;
	BSTNode * _left;
	BSTNode * _right;
};

//TODO: Map

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map {

public:
	

};

}

#endif
