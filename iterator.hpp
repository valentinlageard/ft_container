#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

// Iterator tags

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

// Iterator

template <
	class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T *,
	class Reference = T &>
class iterator {

public:

	typedef Category iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;

};

// Generic random access iterator

template <class T>
class RandomAccessIterator: public ft::iterator<ft::random_access_iterator_tag, T> {

public:

	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category
		iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type
		difference_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;

	RandomAccessIterator(): _ptr(NULL) {}

	RandomAccessIterator(pointer ptr): _ptr(ptr) {}

	RandomAccessIterator(RandomAccessIterator const & original): _ptr(original._ptr) {}

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

	RandomAccessIterator & operator++(int) {
		// TODO: Debug needed
		RandomAccessIterator tmp(*this);
		++_ptr;
		return tmp;
	}

	RandomAccessIterator & operator--() {
		--_ptr;
		return *this;
	}

	RandomAccessIterator & operator--(int) {
		// TODO: Debug needed
		RandomAccessIterator tmp(*this);
		--_ptr;
		return tmp;
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

	// For comparison operators, friend is necessary to compare
	// iterator and const_iterator without exposing _ptr.

	template<typename T1, typename T2>
	friend bool operator==(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	template<typename T1, typename T2>
	friend bool operator!=(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	template<typename T1, typename T2>
	friend bool operator<(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	template<typename T1, typename T2>
	friend bool operator>(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	template<typename T1, typename T2>
	friend bool operator<=(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	template<typename T1, typename T2>
	friend bool operator>=(
		const RandomAccessIterator<T1> & lhs,
		const RandomAccessIterator<T2> & rhs);

	operator RandomAccessIterator<const T> () const {
		return (RandomAccessIterator<const T>(this->_ptr));
	}


private:
	pointer _ptr;

};

template<typename T>
RandomAccessIterator<T> operator+(
	typename ft::RandomAccessIterator<T>::difference_type n,
	typename ft::RandomAccessIterator<T> & it)
{
	return it + n;
}

template<typename T>
RandomAccessIterator<T> operator-(
	typename ft::RandomAccessIterator<T>::difference_type n,
	typename ft::RandomAccessIterator<T> & it)
{
	return it - n;
}

template<typename T1, typename T2>
bool operator==(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr == rhs._ptr);
}

template<typename T1, typename T2>
bool operator!=(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr != rhs._ptr);
}

template<typename T1, typename T2>
bool operator<(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr < rhs._ptr);
}

template<typename T1, typename T2>
bool operator>(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr > rhs._ptr);
}

template<typename T1, typename T2>
bool operator<=(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr <= rhs._ptr);
}

template<typename T1, typename T2>
bool operator>=(
	const RandomAccessIterator<T1> & lhs,
	const RandomAccessIterator<T2> & rhs)
{
	return (lhs._ptr >= rhs._ptr);
}

// Reverse iterator

template <class Iterator> class reverse_iterator {
	// TODO :
	// - copies the iterator passed ans stores it.
	// - calls Iterator::operator -- when ++ is called (for both pre and post)
	// - calls Iterator::operator ++ when -- is called (for both pre and post)
};


// Iterator traits

template <typename iterator>
struct iterator_traits {
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T *> {
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T * pointer;
	typedef T & reference;
	typedef random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T *> {
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T * pointer;
	typedef const T & reference;
	typedef random_access_iterator_tag iterator_category;
};

// Iterator distance computation

template<typename iterator>
typename iterator_traits<iterator>::difference_type compute_distance(
	iterator first,
	iterator last,
	input_iterator_tag)
{
	typename iterator_traits<iterator>::difference_type result = 0;
	while (first != last) {
		++first;
		++result;
	}
	return result;
}

template<typename iterator>
typename iterator_traits<iterator>::difference_type compute_distance(
	iterator first,
	iterator last,
	random_access_iterator_tag)
{
	return last - first;
}

template<typename iterator>
typename iterator_traits<iterator>::difference_type distance(iterator first, iterator last)
{
	return compute_distance(
		first,
		last,
		typename iterator_traits<iterator>::iterator_category());
}

}

#endif
