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

	BSTNode & operator=(BSTNode & rhs) {
		if (this == &rhs) {
			return *this;
		}
		_pair = rhs._pair;
		_left = rhs._left;
		_right = rhs._right;
		_parent = rhs._parent;
		return *this;
	}

	BSTNode * get_left() const {
		return _left;
	}

	BSTNode * get_right() const {
		return _right;
	}

	BSTNode * get_parent() const {
		return _parent;
	}

	value_type * get_pair() const {
		return _pair;
	}

    BSTNode * find_min() {
        if (!_left) {
            return this;
        }
        return _left->find_min();
    }

    BSTNode * find_max() {
        if (!_right) {
            return this;
        }
        return _right->find_max();
    }


    BSTNode * get_next() {
		BSTNode * tmp;
		BSTNode * tmp_parent;

		if (_right) {
			tmp = _right;
			while (tmp->_left) {
				tmp = tmp->_left;
			}
			return tmp;
		}
		tmp = this;
		tmp_parent = _parent;
		while (tmp_parent) {
			if (tmp_parent->_right != tmp) {
				break;
			}
			tmp = _parent;
			tmp_parent = tmp->_parent;
		}
		return tmp_parent;
	}

	BSTNode * get_prev() {
		BSTNode * tmp;
		BSTNode * tmp_parent;

		if (_left) {
			tmp = _left;
			while (tmp->_right) {
				tmp = tmp->_right;
			}
			return tmp;
		}
		tmp = this;
		tmp_parent = _parent;
		while (tmp_parent) {
			if (tmp_parent->_left != tmp) {
				break;
			}
			tmp = _parent;
			tmp_parent = tmp->_parent;
		}
		return tmp_parent;
	}

	void set_parent(BSTNode * parent) {
		_parent = parent;
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
				_right->set_parent(this);
				return _right;
			} else {
				return _right->insert(node);
			}
		} else {
			if (!_left) {
				_left = node;
				_left->set_parent(this);
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
	BSTNode * _parent;
	BSTNode * _left;
	BSTNode * _right;
	key_compare _comp;

	void _recursive_print(std::string indent = "", bool is_left = false) {
		if (!is_left) {
			std::cout << indent << "├R─> " << _pair->first << ": " << _pair->second;
			std::cout << " (parent key: " << _parent->_pair->first << ")" << std::endl;
			indent = indent.append("|    ");
		} else {
			std::cout << indent << "└L─> " << _pair->first << ": " << _pair->second;
			std::cout << " (parent key: " << _parent->_pair->first << ")" << std::endl;
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

template <class T> class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

	// Let's consider T is a pair !

public:
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
	typedef ft::BSTNode<const typename T::first_type, typename T::second_type> node;
	typedef node * node_pointer;
	typedef node & node_reference;

	MapIterator() : _node(NULL) {}

	MapIterator(node_pointer node) : _node(node) {}

	MapIterator(MapIterator const & original) : _node(original._node) {}

	~MapIterator() {}

	MapIterator & operator=(const MapIterator & rhs) {
		if (this == &rhs) {
			return *this;
		}
		_node = rhs._node;
		return *this;
	}

	T & operator*() const {
		return *(_node->get_pair());
	}

	T * operator->() const {
		return &(*(_node->get_pair()));
	}

	MapIterator & operator++() {
		_node = _node->get_next();
		return *this;
	}

	MapIterator operator++(int) {
		node_pointer tmp(_node);
		_node = _node->get_next();
		return MapIterator<T>(tmp);

	}

	MapIterator & operator--() {
		_node = _node->get_prev();
		return *this;
	}

	MapIterator operator--(int) {
		node_pointer tmp(_node);
		_node = _node->get_prev();
		return MapIterator<T>(tmp);
	}

	template <typename T1, typename T2>
	friend bool operator==(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs);

	template <typename T1, typename T2>
	friend bool operator!=(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs);

private:
	node_pointer _node;

};

template <typename T1, typename T2> bool operator==(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs) {
	return (lhs._node == rhs._node);
}

template <typename T1, typename T2> bool operator!=(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs) {
	return (lhs._node != rhs._node);
}

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
	typedef MapIterator<value_type> iterator;
	typedef MapIterator<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// Constructors and destructor.

	explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) :
			_root(NULL), _comp(comp), _alloc(alloc), _node_alloc(_node_allocator_type()) {};

	//TODO: Range constructor
	//TODO: Copy constructor

	virtual ~map() {
		// Delete the tree
	};

    // Iterators

    iterator begin() {
        return iterator(_root->find_min());
    }

    //const_iterator begin() const;

    //TODO: How to implement the end iterator ?
    // - Map automatically keep tracks of the first and last node ?
    // - Use a sentinel value as the max node right child ?

    iterator end() {
        return iterator(_root->find_max()) + 1;
    }

    //const_iterator end() const;

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


	// Element access

//	mapped_type & operator[](const key_type & k) {
//		return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
//	}

	// Modifiers

	ft::pair<iterator, bool> insert(const value_type & val) {
        value_type value = _alloc.allocate(1);
        _node node_tmp = node(val);
        _node_pointer node = _node_alloc.allocate(1);

        _alloc.construct(value, val);
        _node_alloc.construct(node, node_tmp);
        if (!_root) {
            _root = node;
        }
        _root->insert(node);
    }

    //iterator insert (iterator position, const value_type& val);
	//template <class InputIterator> void insert (InputIterator first, InputIterator last);

	// Observers

	key_compare key_comp() const {
		return key_compare(_comp);
	}

	//value_compare value_comp() const {}

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
