#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

// DEBUG
#include <iostream>

namespace ft {

// DOUBLY LINKED NODE TEMPLATE STRUCT

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

// LIST TEMPLATE CLASS

template <class T, class Alloc = std::allocator<T>>
class list {

public:

	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	// TODO: iterator
	// TODO: const_iterator
	// TODO: reverse_iterator
	// TODO: const_reverse_iterator
	// TODO: difference_type
	typedef size_t size_type;

	// CONSTRUCTORS AND DESTRUCTORS

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
		// TODO : clear list
		_node_alloc.destroy(_sentinel_node);
		_node_alloc.deallocate(_sentinel_node, 1);
	}

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

	// DEBUG

	void print_list() {
		DNode<T> * tmp = _sentinel_node->next;

		//std::cout << "Sentinel " << _sentinel_node << ", prev: " << _sentinel_node->prev << ", next: " << _sentinel_node->next << std::endl;
		std::cout << "LIST: " << std::endl;
		while(tmp != _sentinel_node) {
			//std::cout << "\t" << tmp << ": " << tmp->data << ", prev: " << tmp->prev << ", next: " << tmp->next << std::endl;
			std::cout << "\t" << tmp->data << std::endl;
			tmp = tmp->next;
		}
	}

private:
	typedef typename allocator_type::template rebind<DNode<T>>::other node_alloc;
	//typedef typename node_alloc::pointer node_pointer;
	typedef DNode<T> * node_pointer;

	allocator_type _alloc;
	node_alloc _node_alloc;
	node_pointer _sentinel_node;

	node_pointer _create_node(const T & data, DNode<T> * prev = NULL, DNode<T> * next = NULL) {
		node_pointer new_node = _node_alloc.allocate(1);

		_node_alloc.construct(new_node, DNode<T>(data));
		new_node->prev = prev;
		new_node->next = next;
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
