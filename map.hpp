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
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;

	BSTNode() : _pair(NULL), _left(NULL), _right(NULL), _comp(key_compare()) {}

	BSTNode(value_type * pair) : _pair(pair), _left(NULL), _right(NULL), _comp(key_compare()) {}

	virtual ~BSTNode() {}

	BSTNode * get_left() const {
		return _left;
	}

	BSTNode * get_right() const {
		return _right;
	}

	value_type * get_pair() const {
		return _pair;
	}

	size_type size() const {
		size_type left_subcount = 0;
		size_type right_subcount = 0;
		if (_right) {
			right_subcount = _right->size();
		}
		if (_left) {
			left_subcount = _left->size();
		}
		return right_subcount + left_subcount + 1;
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

	value_type * _pair;
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

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map {

public:

	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef value_type & reference;
	typedef const value_type & const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	//TODO: iterator
	//TODO: const_iterator
	//TODO: reverse_iterator
	//TODO: const_reverse_iterator

	// Constructors and destructor.

	explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) :
			_root(NULL), _comp(comp), _alloc(alloc), _node_alloc(_node_allocator_type()) {};

	//TODO: Range constructor
	//TODO: Copy constructor

	virtual ~map() {
		// Delete the tree
	};

	// Capacity

	bool empty() const {
		return (_root == NULL);
	}

	size_type size() const {
		if (_root) {
			return _root->size();
		}
		return 0;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

private:
	typedef BSTNode<key_type, mapped_type, key_compare> _node_type;
	typedef _node_type * _node_pointer;
	typedef typename Alloc::template rebind<_node_type>::other _node_allocator_type;

	_node_pointer _root;
	allocator_type _alloc;
	_node_allocator_type _node_alloc;
	key_compare _comp;

};

}

#endif
