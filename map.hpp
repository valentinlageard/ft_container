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
	typedef ft::pair<const Key, T> pair_type;
	typedef Compare key_compare;

	BSTNode() : _pair(NULL), _left(NULL), _right(NULL), _comp(key_compare()) {}

	BSTNode(pair_type * pair) : _pair(pair), _left(NULL), _right(NULL), _comp(key_compare()) {}

	virtual ~BSTNode() {}

	BSTNode * get_left() {
		return _left;
	}

	BSTNode * get_right() {
		return _right;
	}

	BSTNode * insert(BSTNode * node) {
		if (!_comp(_pair->first, node->_pair->first) && !_comp(node->_pair->first, _pair->first)) {
			return NULL;
		}
		if (_comp(_pair->first, node->_pair->first)) {
			if (!_right) {
				_right = node;
				return _right;
			} else {
				return _right->insert(node);
			}
		} else {
			if (!_left) {
				_left = node;
				return _left;
			} else {
				return _left->insert(node);
			}
		}
	}

	// search
	// last
	// first
	// remove

	void print_subtree() {
		std::cout << _pair->first << ": " << _pair->second << std::endl;
		if (_right) {
			_right->_recursive_print("", false);
		} else {
			std::cout << "" << "├R─> NULL" << std::endl;
		}
		if (_left) {
			_left->_recursive_print("", true);
		} else {
			std::cout << "" << "└L─> NULL" << std::endl;
		}
	}

private:

	const pair_type * _pair;
	BSTNode * _left;
	BSTNode * _right;
	key_compare _comp;

	void _recursive_print(std::string indent = "", bool is_left = false) {
		if (!is_left) {
			std::cout << indent << "├R─> " << _pair->first << ": " << _pair->second << std::endl;
			indent = indent.append("|    ");
		} else {
			std::cout << indent << "└L─> " << _pair->first << ": " << _pair->second << std::endl;
			indent = indent.append("     ");
		}
		if (_right) {
			_right->_recursive_print(indent, false);
		} else {
			std::cout << indent << "├R─> NULL" << std::endl;
		}
		if (_left) {
			_left->_recursive_print(indent, true);
		} else {
			std::cout << indent << "└L─> NULL" << std::endl;
		}
	}
};

//TODO: BSTNodeIterator
//TODO: Map
//
//template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
//class map {
//
//public:
//
//	typedef Key key_type;
//	typedef T mapped_type;
//	typedef ft::pair<const Key, T> value_type;
//	typedef size_t size_type;
//	typedef ptrdiff_t difference_type;
//	typedef Compare key_compare;
//	typedef Alloc allocator_type;
//	typedef value_type & reference;
//	typedef const value_type & const_reference;
//	typedef typename Alloc::pointer pointer;
//	typedef typename Alloc::const_pointer const_pointer;
//	//TODO: iterator
//	//TODO: const_iterator
//	//TODO: reverse_iterator
//	//TODO: const_reverse_iterator
//
//	map() : _root(NULL), _size(0) {};
//
//	virtual ~map() {
//		// Delete the tree
//	};
//
//private:
//	typedef BSTNode<key_type, mapped_type, key_compare> _node_type;
//	typedef _node_type * _node_pointer;
//	typedef typename Alloc::template rebind<_node_type>::other _node_alloc;
//
//	_node_pointer _root;
//
//};

}

#endif
