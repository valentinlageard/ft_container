#ifndef STACK_HPP
#define STACK_HPP


#include <cstddef>
#include "vector.hpp"


namespace ft {

template <class T, class Container = ft::vector<T> > class stack {

	public:

		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;
		typedef size_t size_type;

		stack(const container_type & ctnr = container_type()) : c(ctnr) {}

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

		template <class T_x, class Container_x>
		friend bool operator==(const stack<T_x, Container_x> & lhs,
							   const stack<T_x, Container_x> & rhs);

		template <class T_x, class Container_x>
		friend bool operator!=(const stack<T_x, Container_x> & lhs,
							   const stack<T_x, Container_x> & rhs);

		template <class T_x, class Container_x>
		friend bool operator<=(const stack<T_x, Container_x> & lhs,
							   const stack<T_x, Container_x> & rhs);

		template <class T_x, class Container_x>
		friend bool operator<(const stack<T_x, Container_x> & lhs,
							  const stack<T_x, Container_x> & rhs);

		template <class T_x, class Container_x>
		friend bool operator>(const stack<T_x, Container_x> & lhs,
							  const stack<T_x, Container_x> & rhs);

		template <class T_x, class Container_x>
		friend bool operator>=(const stack<T_x, Container_x> & lhs,
							   const stack<T_x, Container_x> & rhs);

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
