#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <memory>
#include "type_traits.hpp"


namespace ft {

// Iterator

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *,
		  class Reference = T &> class iterator {

	public:

		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

};

// Generic random access iterator

template <class T>
class RandomAccessIterator : public ft::iterator<std::random_access_iterator_tag, T> {

	public:

		typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category
				iterator_category;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type
				difference_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;

		RandomAccessIterator() : _ptr(NULL) {}

		RandomAccessIterator(pointer ptr) : _ptr(ptr) {}

		RandomAccessIterator(RandomAccessIterator const & original) : _ptr(original._ptr) {}

		~RandomAccessIterator() {}

		RandomAccessIterator & operator=(const RandomAccessIterator & rhs) {
			if (*this != rhs) {
				_ptr = rhs._ptr;
			}
			return *this;
		}

		RandomAccessIterator & operator+=(const difference_type & n) {
			_ptr += n;
			return *this;
		}

		RandomAccessIterator & operator-=(const difference_type & n) {
			_ptr -= n;
			return *this;
		}

		T & operator*() const {
			return *_ptr;
		}

		T * operator->() const {
			return &(*_ptr);
		}

		RandomAccessIterator & operator++() {
			++_ptr;
			return *this;
		}

		RandomAccessIterator operator++(int) {
			pointer tmp = _ptr;
			++_ptr;
			return RandomAccessIterator<T>(tmp);
		}

		RandomAccessIterator & operator--() {
			--_ptr;
			return *this;
		}

		RandomAccessIterator operator--(int) {
			pointer tmp = _ptr;
			--_ptr;
			return RandomAccessIterator<T>(tmp);
		}

		RandomAccessIterator operator+(difference_type n) const {
			return (RandomAccessIterator<T>(_ptr + n));
		}

		RandomAccessIterator operator-(difference_type n) const {
			return (RandomAccessIterator<T>(_ptr - n));
		}

		difference_type operator-(RandomAccessIterator rhs) const {
			return (_ptr - rhs._ptr);
		}

		reference operator[](difference_type n) {
			return _ptr[n];
		}

		reference operator[](difference_type n) const {
			return _ptr[n];
		}

		operator RandomAccessIterator<const T>() const {
			RandomAccessIterator<const T> const_iterator(this->_ptr);
			return const_iterator;
		}

		// For comparison operators, friend is necessary to compare
		// iterator and const_iterator without exposing _ptr.

		template <typename T1, typename T2>
		friend bool operator==(const RandomAccessIterator<T1> & lhs,
							   const RandomAccessIterator<T2> & rhs);

		template <typename T1, typename T2>
		friend bool operator!=(const RandomAccessIterator<T1> & lhs,
							   const RandomAccessIterator<T2> & rhs);

		template <typename T1, typename T2>
		friend bool operator<(const RandomAccessIterator<T1> & lhs,
							  const RandomAccessIterator<T2> & rhs);

		template <typename T1, typename T2>
		friend bool operator>(const RandomAccessIterator<T1> & lhs,
							  const RandomAccessIterator<T2> & rhs);

		template <typename T1, typename T2>
		friend bool operator<=(const RandomAccessIterator<T1> & lhs,
							   const RandomAccessIterator<T2> & rhs);

		template <typename T1, typename T2>
		friend bool operator>=(const RandomAccessIterator<T1> & lhs,
							   const RandomAccessIterator<T2> & rhs);

	private:
		pointer _ptr;

};

template <typename T>
RandomAccessIterator<T> operator+(typename ft::RandomAccessIterator<T>::difference_type n,
								  typename ft::RandomAccessIterator<T> & it) {
	return it + n;
}

template <typename T>
RandomAccessIterator<T> operator-(typename ft::RandomAccessIterator<T>::difference_type n,
								  typename ft::RandomAccessIterator<T> & it) {
	return it - n;
}

template <typename T1, typename T2>
bool operator==(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr == rhs._ptr);
}

template <typename T1, typename T2>
bool operator!=(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr != rhs._ptr);
}

template <typename T1, typename T2>
bool operator<(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr < rhs._ptr);
}

template <typename T1, typename T2>
bool operator>(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr > rhs._ptr);
}

template <typename T1, typename T2>
bool operator<=(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr <= rhs._ptr);
}

template <typename T1, typename T2>
bool operator>=(const RandomAccessIterator<T1> & lhs, const RandomAccessIterator<T2> & rhs) {
	return (lhs._ptr >= rhs._ptr);
}

// Iterator traits

template <typename iterator> struct iterator_traits {
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::iterator_category iterator_category;
};

template <typename T> struct iterator_traits<T *> {
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T * pointer;
	typedef T & reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <typename T> struct iterator_traits<const T *> {
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T * pointer;
	typedef const T & reference;
	typedef std::random_access_iterator_tag iterator_category;
};

// Iterator distance computation

template <typename iterator>
typename iterator_traits<iterator>::difference_type compute_distance(iterator first, iterator last,
																	 std::input_iterator_tag) {
	typename iterator_traits<iterator>::difference_type result = 0;
	while (first != last) {
		++first;
		++result;
	}
	return result;
}

template <typename iterator>
typename iterator_traits<iterator>::difference_type compute_distance(iterator first, iterator last,
																	 std::random_access_iterator_tag) {
	return last - first;
}

template <typename iterator>
typename iterator_traits<iterator>::difference_type distance(iterator first, iterator last) {
	return compute_distance(first, last, typename iterator_traits<iterator>::iterator_category());
}

// Reverse iterator

template <class Iterator> class reverse_iterator {

	public:

		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;

		reverse_iterator() : _base(iterator_type()) {}

		reverse_iterator(iterator_type it) : _base(iterator_type(it)) {}

		template <class value_type>
		reverse_iterator & operator=(const reverse_iterator<value_type> & other) {
			if (_base == other.base()) {
				return *this;
			}
			_base = other.base();
			return *this;
		}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> & rev_it): _base(rev_it.base()) {}

		iterator_type base() const {
			return iterator_type(_base);
		}

		reference operator*() const {
			iterator_type tmp(_base);
			return *(--tmp);
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference operator[](difference_type n) const {
			return _base[-n - 1];
		}

		reverse_iterator & operator++() {
			--_base;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		reverse_iterator & operator--() {
			++_base;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		reverse_iterator & operator+=(difference_type n) {
			_base -= n;
			return *this;
		}

		reverse_iterator & operator-=(difference_type n) {
			_base += n;
			return *this;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_base - n);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_base + n);
		}

	private:
		iterator_type _base;

};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() != rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() > rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() >= rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
									 const reverse_iterator<Iterator> & rev_it) {
	return rev_it + n;
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) {
	return -(lhs.base() - rhs.base());
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
	return -(lhs.base() - rhs.base());
}

}

#endif
