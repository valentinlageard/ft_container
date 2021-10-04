#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include "iterator.hpp"

// DEBUG
#include <iostream>

namespace ft {

/*

██████  ███    ██  ██████  ██████  ███████
██   ██ ████   ██ ██    ██ ██   ██ ██
██   ██ ██ ██  ██ ██    ██ ██   ██ █████
██   ██ ██  ██ ██ ██    ██ ██   ██ ██
██████  ██   ████  ██████  ██████  ███████

*/

template <class T>
struct DNode {
	DNode * prev;
	DNode * next;
	T data;

	DNode():
		prev(NULL),
		next(NULL)
	{}

	DNode(const T & val):
		prev(NULL),
		next(NULL),
		data(val)
	{}

	DNode(const T & val, DNode * prev_addr, DNode * next_addr):
		prev(prev_addr),
		next(next_addr),
		data(val)
	{}
};

/*

██      ██ ███████ ████████ ██ ████████ ███████ ██████   █████  ████████  ██████  ██████
██      ██ ██         ██    ██    ██    ██      ██   ██ ██   ██    ██    ██    ██ ██   ██
██      ██ ███████    ██    ██    ██    █████   ██████  ███████    ██    ██    ██ ██████
██      ██      ██    ██    ██    ██    ██      ██   ██ ██   ██    ██    ██    ██ ██   ██
███████ ██ ███████    ██    ██    ██    ███████ ██   ██ ██   ██    ██     ██████  ██   ██

*/

template <class T>
class ListIterator: public ft::iterator<ft::bidirectional_iterator_tag, T> {

public:
	ListIterator(): _node(NULL) {}

	ListIterator(DNode<T> * node): _node(node) {}

	ListIterator(ListIterator const & original): _node(original._node) {}

	~ListIterator() {}

	ListIterator & operator=(ListIterator const & rhs) {
		if (*this == rhs) {
			return;
		}
		_node = rhs._node;
		return *this;
	}

/*
	friend bool operator==(const ListIterator<T> & lhs, const ListIterator<T> & rhs) {
		return (lhs._node == rhs._node);
	}

	friend bool operator!=(const ListIterator<T> & lhs, const ListIterator<T> & rhs) {
		return (lhs._node != rhs._node);
	}
*/
	bool & operator==(ListIterator<T> const & rhs) const {
		return (_node == rhs._node);
	}

	bool & operator!=(ListIterator<T> const & rhs) const {
		return (_node != rhs._node);
	}

	T & operator*() const {
		return _node->data;
	}

	T * operator->() const {
		return &(_node->data);
	}

	ListIterator & operator++() {
		_node = _node->next;
		return *this;
	}

	ListIterator & operator++(int) {
		ListIterator tmp(*this);
		_node = _node->next;
		return tmp;
	}

	ListIterator & operator--() {
		_node = _node->prev;
		return *this;
	}

	ListIterator & operator--(int) {
		ListIterator tmp(*this);
		_node = _node->prev;
		return tmp;
	}

private:
	typedef DNode<T> * node_pointer;

	node_pointer _node;

};

/*

██      ██ ███████ ████████
██      ██ ██         ██
██      ██ ███████    ██
██      ██      ██    ██
███████ ██ ███████    ██

*/

template <class T, class Alloc = std::allocator<T>>
class list {

public:

	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef ListIterator<T> iterator;
	typedef ListIterator<const T> const_iterator;
	// TODO: reverse_iterator
	// TODO: const_reverse_iterator
	// TODO: difference_type
	typedef size_t size_type;

	explicit list (const allocator_type & alloc = allocator_type()):
		_alloc(alloc)
	{
		_sentinel_node = _node_alloc.allocate(1);
		_node_alloc.construct(_sentinel_node, DNode<T>());
		_sentinel_node->prev = _sentinel_node;
		_sentinel_node->next = _sentinel_node;
	}

	/*
	explicit list (
		size_type n,
		const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type())
	{

	}

	template <class InputIterator>
	list (
		InputIterator first,
		InputIterator last,
		const allocator_type& alloc = allocator_type())
	{

	}

	list (const list& x) {

	}
	*/

	~list() {
		clear();
		// TODO : clear list
		_node_alloc.destroy(_sentinel_node);
		_node_alloc.deallocate(_sentinel_node, 1);
	}

	/*

	██ ████████ ███████ ██████   █████  ████████  ██████  ██████  ███████
	██    ██    ██      ██   ██ ██   ██    ██    ██    ██ ██   ██ ██
	██    ██    █████   ██████  ███████    ██    ██    ██ ██████  ███████
	██    ██    ██      ██   ██ ██   ██    ██    ██    ██ ██   ██      ██
	██    ██    ███████ ██   ██ ██   ██    ██     ██████  ██   ██ ███████

	*/

	iterator begin() {
		return iterator(_sentinel_node->next);
	}

	//const_iterator begin() const;

	iterator end() {
		return iterator(_sentinel_node);
	}

	/*

	 ██████  █████  ██████   █████   ██████ ██ ████████ ██    ██
	██      ██   ██ ██   ██ ██   ██ ██      ██    ██     ██  ██
	██      ███████ ██████  ███████ ██      ██    ██      ████
	██      ██   ██ ██      ██   ██ ██      ██    ██       ██
	 ██████ ██   ██ ██      ██   ██  ██████ ██    ██       ██

	*/

	bool empty() const {
		return _sentinel_node->next == _sentinel_node;
	}

	size_type size() const {
		node_pointer tmp = _sentinel_node->next;
		size_type i = 0;

		while (tmp != _sentinel_node) {
			i++;
			tmp = tmp->next;
		}
		return (i);
	}

	size_type max_size() const {
		return _node_alloc.max_size();
	}

	/*

	███████ ██      ███████ ███    ███      █████   ██████  ██████ ███████ ███████ ███████
	██      ██      ██      ████  ████     ██   ██ ██      ██      ██      ██      ██
	█████   ██      █████   ██ ████ ██     ███████ ██      ██      █████   ███████ ███████
	██      ██      ██      ██  ██  ██     ██   ██ ██      ██      ██           ██      ██
	███████ ███████ ███████ ██      ██     ██   ██  ██████  ██████ ███████ ███████ ███████

	*/

	reference front() {
		return _sentinel_node->next->data;
	}

	const_reference front() const {
		return _sentinel_node->next->data;
	}

	reference back() {
		return _sentinel_node->prev->data;
	}

	const_reference back() const {
		return _sentinel_node->prev->data;
	}

	/*

	███    ███  ██████  ██████  ██ ███████ ██ ███████ ██████  ███████
	████  ████ ██    ██ ██   ██ ██ ██      ██ ██      ██   ██ ██
	██ ████ ██ ██    ██ ██   ██ ██ █████   ██ █████   ██████  ███████
	██  ██  ██ ██    ██ ██   ██ ██ ██      ██ ██      ██   ██      ██
	██      ██  ██████  ██████  ██ ██      ██ ███████ ██   ██ ███████

	*/

	void push_front(const value_type & val) {
		_insert_front(_create_node(val));
	}

	void pop_front() {
		_delete(_sentinel_node->next);
	}

	void push_back(const value_type & val) {
		_insert_back(_create_node(val));
	}

	void pop_back() {
		_delete(_sentinel_node->prev);
	}

	void swap (list & x) {
		// TODO : check if same -> return;
		node_pointer tmp_sentinel = x._sentinel_node;

		x._sentinel_node = this->_sentinel_node;
		this->_sentinel_node = tmp_sentinel;

		// TODO : Check if it works !
	}

	void resize (size_type n, value_type val = value_type()) {
		size_type previous_size = size();
		size_type i = 0;

		if (n == previous_size) {
			return;
		} else if (n > previous_size) {
			while (i < n - previous_size) {
				push_back(val);
				i++;
			}
		} else {
			while (i < previous_size - n) {
				pop_back();
				i++;
			}
		}

		// TODO: How to invalidate iterators pointing to erased elements ?
	}

	void clear() {
		node_pointer tmp = _sentinel_node->next;
		node_pointer next;

		while (tmp != _sentinel_node) {
			next = tmp->next;
			_delete(tmp);
			tmp = next;
		}
	}

	/*

	 ██████  ██████  ███████ ██████   █████  ████████ ██  ██████  ███    ██ ███████
	██    ██ ██   ██ ██      ██   ██ ██   ██    ██    ██ ██    ██ ████   ██ ██
	██    ██ ██████  █████   ██████  ███████    ██    ██ ██    ██ ██ ██  ██ ███████
	██    ██ ██      ██      ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██      ██
	 ██████  ██      ███████ ██   ██ ██   ██    ██    ██  ██████  ██   ████ ███████

	*/

	/*

	██████  ███████ ██████  ██    ██  ██████
	██   ██ ██      ██   ██ ██    ██ ██
	██   ██ █████   ██████  ██    ██ ██   ███
	██   ██ ██      ██   ██ ██    ██ ██    ██
	██████  ███████ ██████   ██████   ██████

	*/

	void print_list() {
		node_pointer tmp = _sentinel_node->next;

		//std::cout << "Sentinel " << _sentinel_node << ", prev: " << _sentinel_node->prev << ", next: " << _sentinel_node->next << std::endl;
		std::cout << "LIST: " << std::endl;
		while(tmp != _sentinel_node) {
			//std::cout << "\t" << tmp << ": " << tmp->data << ", prev: " << tmp->prev << ", next: " << tmp->next << std::endl;
			std::cout << "\t" << tmp->data << std::endl;
			tmp = tmp->next;
		}
	}


	/*

	██████  ██████  ██ ██    ██  █████  ████████ ███████
	██   ██ ██   ██ ██ ██    ██ ██   ██    ██    ██
	██████  ██████  ██ ██    ██ ███████    ██    █████
	██      ██   ██ ██  ██  ██  ██   ██    ██    ██
	██      ██   ██ ██   ████   ██   ██    ██    ███████

	*/

private:
	typedef typename allocator_type::template rebind<DNode<T>>::other node_alloc;
	typedef DNode<T> * node_pointer;

	allocator_type _alloc;
	node_alloc _node_alloc;
	node_pointer _sentinel_node;

	node_pointer _create_node(const T & data, DNode<T> * prev = NULL, DNode<T> * next = NULL) {
		node_pointer new_node = _node_alloc.allocate(1);

		_node_alloc.construct(new_node, DNode<T>(data, prev, next));
		return new_node;
	}

	void _insert_front(DNode<T> * node) {
		node_pointer previous_first_node = _sentinel_node->next;

		node->next = previous_first_node;
		previous_first_node->prev = node;
		node->prev = _sentinel_node;
		_sentinel_node->next = node;
	}

	void _insert_back(DNode<T> * node) {
		node_pointer previous_last_node = _sentinel_node->prev;

		node->next = _sentinel_node;
		_sentinel_node->prev = node;
		node->prev = previous_last_node;
		previous_last_node->next = node;
	}

	void _disconnect(DNode<T> * node) {
		if (node->prev == _sentinel_node) {
			_sentinel_node->next = node->next;
		} else {
			node->prev->next = node->next;
		}
		if (node->next == _sentinel_node) {
			_sentinel_node->prev = node->prev;
		} else {
			node->next->prev = node->prev;
		}
	}

	void _delete(DNode<T> * node) {
		if (node != _sentinel_node) {
			_disconnect(node);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}
	}
};

}

#endif
