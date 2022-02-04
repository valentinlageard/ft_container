#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"


namespace ft {

template <class Key, class T> class BSTNode {
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<Key, T> value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		BSTNode(const value_type & pair) : _pair(pair), _left(NULL), _right(NULL), _parent(NULL) {}

		BSTNode(const BSTNode & original) :
				_pair(original.get_pair()), _left(original.get_left()),
				_right(original.get_right()), _parent(original.get_parent()) {}

		virtual ~BSTNode() {}

		BSTNode & operator=(const BSTNode & rhs) {
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

		value_type & get_pair() {
			return _pair;
		}

		const value_type & get_pair() const {
			return _pair;
		}

		void set_left(BSTNode * left) {
			_left = left;
		}

		void set_right(BSTNode * right) {
			_right = right;
		}

		void set_parent(BSTNode * parent) {
			_parent = parent;
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

		void print_subtree() {
			std::cout << _pair.first << ": " << _pair.second << std::endl;
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

		void _recursive_print(std::string indent = "", bool is_left = false) {
			if (!is_left) {
				std::cout << indent << "├R─> " << _pair.first << ": " << _pair.second;
				std::cout << " (parent key: " << (_parent ? _parent->_pair.first : 0) << ")"
						  << std::endl;
				indent = indent.append("|	");
			} else {
				std::cout << indent << "└L─> " << _pair.first << ": " << _pair.second;
				std::cout << " (parent key: " << (_parent ? _parent->_pair.first : 0) << ")"
						  << std::endl;
				indent = indent.append("	 ");
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

	private:

		value_type _pair;
		BSTNode * _left;
		BSTNode * _right;
		BSTNode * _parent;

		BSTNode() {};

};

template <class T> class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category
				iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type
				difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type mapped_type;
		typedef ft::BSTNode<key_type, mapped_type> node;
		typedef node * node_pointer;
		typedef node & node_reference;

		MapIterator() : _node(NULL) {}

		MapIterator(node_pointer node) : _node(node) {}

		MapIterator(const MapIterator & original) : _node(original._node) {}

		~MapIterator() {}

		MapIterator & operator=(const MapIterator & rhs) {
			if (this == &rhs) {
				return *this;
			}
			_node = rhs._node;
			return *this;
		}

		T & operator*() const {
			return _node->get_pair();
		}

		T * operator->() const {
			return &(_node->get_pair());
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

template <typename T1, typename T2>
bool operator==(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs) {
	return (lhs._node == rhs._node);
}

template <typename T1, typename T2>
bool operator!=(const MapIterator<T1> & lhs, const MapIterator<T2> & rhs) {
	return (lhs._node != rhs._node);
}

template <class Key, class T, class Compare = std::less<Key>,
		  class Alloc = std::allocator<pair<const Key, T> > > class map {

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

		explicit map(const key_compare & comp = key_compare(),
					 const allocator_type & alloc = allocator_type()) :
				_root(NULL), _alloc(alloc), _node_alloc(_node_allocator_type()), _comp(comp) {};

		//TODO: Range constructor
		//TODO: Copy constructor
		//TODO: Assign operator

		~map() { //TODO: remove virtual ??
			// Delete the tree
		};

		// Iterators

		iterator begin() {
			if (_root) { return iterator(_root->find_min()); }
			return iterator(NULL);
		}

		const_iterator begin() const {
			if (_root) { return const_iterator(_root->find_min()); }
			return const_iterator(NULL);
		}

		iterator end() {
			if (_root) { ++iterator(_root->find_max()); }
			return iterator(NULL);
		}

		const_iterator end() const {
			if (_root) { return ++const_iterator(_root->find_max()); }
			return const_iterator(NULL);
		}

		//TODO: Reverse iterators don't work :(

//		reverse_iterator rbegin() {
//			return reverse_iterator(iterator(_root->find_max()));
//		}
//
//		const_reverse_iterator rbegin() const {
//			return const_reverse_iterator(const_iterator(_root->find_max()));
//		}
//
//		reverse_iterator rend() {
//			return reverse_iterator(--iterator(_root->find_min()));
//		}
//
//		const_reverse_iterator rend() const {
//			return const_reverse_iterator(--const_iterator(_root->find_min()));
//		}

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

//		mapped_type & operator[](const key_type & k) {
//			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
//		}

		// Modifiers

		void clear() {
			_node_type * tmp = _root;
			_node_type * tmp_parent = NULL;

			while (tmp) {
				tmp_parent = tmp->get_parent();
				if (tmp->get_left()) {
					tmp = tmp->get_left();
				} else if (tmp->get_right()) {
					tmp = tmp->get_right();
				} else {
					if (tmp_parent && tmp_parent->get_left() == tmp) {
						tmp_parent->set_left(NULL);
					} else if (tmp_parent && tmp_parent->get_right() == tmp) {
						tmp_parent->set_right(NULL);
					}
					_node_alloc.destroy(tmp);
					_node_alloc.deallocate(tmp, 1);
					tmp = tmp_parent;
				}
			}
			_root = NULL;
		}

		ft::pair<iterator, bool> insert(const value_type & val) {
			_node_type * tmp = _root;
			_node_type * tmp_parent = NULL;
			bool inserted;

			while (tmp) {
				tmp_parent = tmp;
				if (_comp(val.first, tmp->get_pair().first)) {
					tmp = tmp->get_left();
				} else if (_comp(tmp->get_pair().first, val.first)) {
					tmp = tmp->get_right();
				} else {
					break;
				}
			}
			if (!tmp) {
				_node_type * new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, val);
				new_node->set_parent(tmp_parent);
				if (!tmp_parent) {
					_root = new_node;
				} else if (_comp(val.first, tmp_parent->get_pair().first)) {
					tmp_parent->set_left(new_node);
				} else {
					tmp_parent->set_right(new_node);
				}
				inserted = true;
			} else {
				inserted = false;
			}
			return ft::make_pair(iterator(tmp), inserted);
		}

		//iterator insert (iterator position, const value_type& val);
		//template <class InputIterator> void insert (InputIterator first, InputIterator last);

		// Observers

		key_compare key_comp() const {
			return key_compare(_comp);
		}

		//value_compare value_comp() const {}

		// DEBUG
		//TODO : to remove
		void print_tree() const {
			if (_root) {
				_root->print_subtree();
			}
		}

	private:
		typedef BSTNode<const key_type, mapped_type> _node_type;
		typedef _node_type * _node_pointer;
		typedef typename Alloc::template rebind<_node_type>::other _node_allocator_type;

		_node_pointer _root;
		allocator_type _alloc;
		_node_allocator_type _node_alloc;
		key_compare _comp;
};

}

#endif
