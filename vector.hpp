#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

// DEBUG
#include <iostream>


namespace ft {

template <class T, class Alloc = std::allocator<T> > class vector {

		// TODO: Check for max_size when allocating new elements
		// TODO: Check for allocation error when allocating elements
		// TODO: Check if NULL _array causes no bug ?

	public:

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef ptrdiff_t difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::RandomAccessIterator<T> iterator;
		typedef ft::RandomAccessIterator<const T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef size_t size_type;

		// Constructors

		explicit vector(const allocator_type & alloc = allocator_type()) :
				_alloc(alloc), _array(NULL), _size(0), _capacity(0) {}

		explicit vector(size_type n, const value_type & val = value_type(),
						const allocator_type & alloc = allocator_type()) :
				_alloc(alloc), _array(NULL), _size(n), _capacity(n) {
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_array + i, val);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type & alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0):
				_alloc(alloc), _array(NULL), _size(0), _capacity(0) {
			assign(first, last);
		}

		vector(const vector & x) : _alloc(x.get_allocator()), _array(NULL), _size(0), _capacity(0) {
			assign(x.begin(), x.end());
		}

		// Destructor

		~vector() {
			_delete_array();
		}

		// Assignment operator

		vector & operator=(const vector & rhs) {
			if (this == &rhs) {
				return *this;
			}
			if (_array != NULL) {
				_delete_array();
			}
			_size = rhs._size;
			_capacity = rhs._capacity;
			if (!rhs.empty()) {
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(_array + i, rhs._array[i]);
				}
			}
			return *this;
		}

		// Iterators

		iterator begin() {
			return _array;
		}

		const_iterator begin() const {
			return _array;
		}

		iterator end() {
			return _array + _size;
		}

		const_iterator end() const {
			return _array + _size;
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		// Capacity

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type()) {
			if (n < _size) {
				for (size_type i = n; i < _size; i++) {
					_alloc.destroy(_array + i);
				}
			} else if (n > _size) {
				reserve(n);
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(_array + i, val);
				}
			}
			_size = n;
		}

		size_type capacity() const {
			return _capacity;
		}

		bool empty() const {
			return (_size == 0);
		}

		void reserve(size_type n) {
			pointer new_array;

			if (n > _capacity) {
				new_array = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(new_array + i, _array[i]);
				}
				_delete_array();
				_array = new_array;
				_capacity = n;
			}
		}

		// Element access

		reference operator[](size_type n) {
			return _array[n];
		}

		const_reference operator[](size_type n) const {
			return _array[n];
		}

		reference at(size_type n) {
			_check_range(n);
			return _array[n];
		}

		const_reference at(size_type n) const {
			_check_range(n);
			return _array[n];
		}

		reference front() {
			return _array[0];
		}

		const_reference front() const {
			return _array[0];
		}

		reference back() {
			return _array[_size - 1];
		}

		const_reference back() const {
			return _array[_size - 1];
		}

		pointer data() {
			return _array;
		}

		const_pointer data() const {
			return _array;
		}

		// Modifiers

		void assign(size_type n, const value_type & val) {
			clear();
			reserve(n);
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_array + i, val);
			}
			_size = n;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
			difference_type new_size = ft::distance(first, last);
			clear();
			reserve(new_size);
			for (difference_type i = 0; i < new_size; ++i) {
				_alloc.construct(_array + i, *first);
				++first;
			}
			_size = new_size;
		}

		void push_back(const value_type & val) {
			if (_size == _capacity) {
				reserve(_capacity * 2 + 1);
			}
			_alloc.construct(_array + _size, val);
			_size++;
		}

		void pop_back() {
			_alloc.destroy(_array + _size - 1);
			_size--;
		}

		iterator insert(iterator position, const value_type & val) {
			size_type pos_idx = position - begin();
			insert(position, 1, val);
			return begin() + pos_idx;
		}

		void insert(iterator position, size_type n, const value_type & val) {
			pointer new_array;
			size_type pos_idx = position - begin();

			if (_size + n > _capacity) {
				new_array = _alloc.allocate(_capacity + (n * 2) + 1);
				for (size_type i = 0; i < pos_idx; i++) {
					_alloc.construct(new_array + i, _array[i]);
				}
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(new_array + pos_idx + i, val);
				}
				for (size_type i = pos_idx; i < _size; i++) {
					_alloc.construct(new_array + i + n, _array[i]);
				}
				_delete_array();
				_array = new_array;
				_capacity = _capacity + (n * 2) + 1;
			} else {
				for (size_type i = 0; i < _size - pos_idx; i++) {
					_alloc.construct(_array + _size + n - i - 1, _array[_size - 1 - i]);
					_alloc.destroy(_array + _size - 1 - i);
				}
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_array + pos_idx + i, val);
				}
			}
			_size += n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
			pointer new_array;
			size_type pos_idx = position - begin();
			size_type n = 0;
			InputIterator tmp(first);
			while (tmp != last) {
				n++;
				tmp++;
			}

			if (_size + n > _capacity) {
				new_array = _alloc.allocate(_capacity + (n * 2) + 1);
				for (size_type i = 0; i < pos_idx; i++) {
					_alloc.construct(new_array + i, _array[i]);
				}
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(new_array + pos_idx + i, *first);
					first++;
				}
				for (size_type i = pos_idx; i < _size; i++) {
					_alloc.construct(new_array + i + n, _array[i]);
				}
				_delete_array();
				_array = new_array;
				_capacity = _capacity + (n * 2) + 1;
			} else {
				for (size_type i = 0; i < _size - pos_idx; i++) {
					_alloc.construct(_array + _size + n - i - 1, _array[_size - 1 - i]);
					_alloc.destroy(_array + _size - 1 - i);
				}
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_array + pos_idx + i, *first);
					first++;
				}
			}
			_size += n;
		}

		iterator erase(iterator position) {
			return erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last) {
			size_type pos_idx = first - begin();
			size_type end_idx = last - begin();
			size_type n = last - first;

			for (size_type i = 0; i < n; i++) {
				_alloc.destroy(_array + pos_idx + i);
			}
			for (size_type i = 0; i < _size - end_idx; i++) {
				_alloc.construct(_array + pos_idx + i, _array[end_idx + i]);
				_alloc.destroy(_array + end_idx + i);
			}
			_size -= n;
			return RandomAccessIterator<T>(_array + pos_idx);
		}

		void swap(vector & x) {
			pointer tmp_array = x._array;
			size_type tmp_size = x._size;
			size_type tmp_capacity = x._capacity;

			x._array = _array;
			x._size = _size;
			x._capacity = _capacity;

			_array = tmp_array;
			_size = tmp_size;
			_capacity = tmp_capacity;
		}

		void clear() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_array + i);
			}
			_size = 0;
		}

		// Allocator

		allocator_type get_allocator() const {
			return allocator_type(_alloc);
		}

	private:
		allocator_type _alloc;
		pointer _array;
		size_type _size;
		size_type _capacity;

		void _delete_array() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_array + i);
			}
			_alloc.deallocate(_array, _capacity);
			_array = NULL;
		}

		void _check_range(const size_type & n) const {
			std::stringstream exception_ss;
			if (n >= _size) {
				exception_ss << "vector::_check_range: n (which is " << n;
				exception_ss << ") >= this->size() (which is " << _size << ")";
				throw std::out_of_range(exception_ss.str().c_str());
			}
		}
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	return !(rhs == lhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
	return (!(lhs < rhs));
}

template <class T, class Alloc> void swap(vector<T, Alloc> & x, vector<T, Alloc> & y) {
	x.swap(y);
}

}

#endif