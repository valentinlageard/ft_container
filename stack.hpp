#ifndef STACK_HPP
#define STACK_HPP


#include <cstddef>
#include "vector.hpp"

// DEBUG
#include <deque>


namespace ft {

template <class T, class Container = ft::vector<T> > class stack {

	public:

		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;
		typedef size_t size_type;

		explicit stack(const container_type & ctnr = container_type()) : c(ctnr) {}

		~stack() {}

		stack & operator=(const stack & rhs) {
			if (*this != rhs) {
				c = rhs.c;
			}
			return *this;
		}

		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		value_type & top() {
			return c.back();
		}

		const value_type & top() const {
			return c.back();
		}

		void push(const value_type & val) {
			c.push_back(val);
		}

		void pop() {
			c.pop_back();
		}

		// Need to use friend for relational operator overload so they can access protected member c
		// without exposing it.

		friend bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

		friend bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

		friend bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

		friend bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

		friend bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

		friend bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);

	protected:
		container_type c;

};

template <class T, class Container>
bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c == rhs.c);
}

template <class T, class Container>
bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c != rhs.c);
}

template <class T, class Container>
bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c < rhs.c);
}

template <class T, class Container>
bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c <= rhs.c);

}

template <class T, class Container>
bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c > rhs.c);
}

template <class T, class Container>
bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
	return (lhs.c >= rhs.c);
}

}

#endif
