#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include <cassert>
#include <iomanip>
#include <cstdlib>


#ifndef NS
#define NS ft
#endif

template <class T> void print_vector(NS::vector<T> & v) {
	size_t size = v.size();
	size_t capacity = v.capacity();
	std::cout << " └─> Vector | size:" << std::setw(4) << size;
	std::cout << " | capacity:" << std::setw(4) << capacity << " | content: [";
	for (size_t i = 0; i < capacity; i++) {
		if (i < size) {
			std::cout << std::setw(2) << v[i];
		} else {
			std::cout << "  ";
		}
		if (i < capacity - 1) {
			std::cout << "|";
		}
	}
	std::cout << "]" << std::endl;
}

void test_vector() {

	std::cout << "\n========== TESTING VECTOR ==========\n" << std::endl;

	std::cout << "---------- TESTING CONSTRUCTION / DESTRUCTION ----------" << std::endl;

	std::cout << "empty_vector()" << std::endl;
	NS::vector<int> empty_vector;
	print_vector(empty_vector);
	assert(empty_vector.empty());

	std::cout << "my_vector(5, 42)" << std::endl;
	NS::vector<int> my_vector(5, 42);
	print_vector(my_vector);
	assert(my_vector.size() == 5);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "my_vector_range(my_vector.begin(), my_vector.end())" << std::endl;
	NS::vector<int> my_vector_range(my_vector.begin(), my_vector.end());
	print_vector(my_vector_range);

	std::cout << "my_vector_copy(my_vector)" << std::endl;
	NS::vector<int> my_vector_copy(my_vector);
	print_vector(my_vector_copy);
	assert(my_vector == my_vector_copy);

	std::cout << "---------- TESTING CAPACITY ----------" << std::endl;

	std::cout << "resize(3)" << std::endl;
	my_vector.resize(3);
	print_vector(my_vector);
	assert(my_vector.size() == 3);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "resize(10, 21)" << std::endl;
	my_vector.resize(10, 21);
	print_vector(my_vector);
	assert(my_vector.size() == 10);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "reserve(3)" << std::endl;
	my_vector.reserve(3);
	print_vector(my_vector);
	assert(my_vector.size() == 10);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "reserve(12)" << std::endl;
	my_vector.reserve(12);
	print_vector(my_vector);
	assert(my_vector.size() == 10);
	assert(my_vector.capacity() >= 12);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "nonempty_vector.empty()" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << (my_vector.empty() ? "true" : "false") << std::endl;
	assert(my_vector.empty() == false);

	std::cout << "empty_vector.empty()" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << (empty_vector.empty() ? "true" : "false") << std::endl;
	assert(empty_vector.empty() == true);

	std::cout << "---------- TESTING ELEMENT ACCESS ----------" << std::endl;

	std::cout << "front()" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << my_vector.front() << std::endl;
	assert(my_vector.front() == 42);

	std::cout << "back()" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << my_vector.back() << std::endl;
	assert(my_vector.back() == 21);

	std::cout << "my_vector[2]" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << my_vector[2] << std::endl;
	assert(my_vector[2] == 42);

	std::cout << "my_vector.at(2)" << std::endl;
	print_vector(my_vector);
	std::cout << " └─> " << my_vector.at(2) << std::endl;
	assert(my_vector.at(2) == 42);

	std::cout << "my_vector.at(-1)" << std::endl;
	print_vector(my_vector);
	try {
		my_vector.at(-1);
	} catch (std::exception & e) {
		std::cout << " └─> " << "Exception: " << e.what() << std::endl;
	}

	std::cout << "my_vector.at(2) = 67" << std::endl;
	my_vector.at(2) = 67;
	print_vector(my_vector);
	assert(my_vector.at(2) == 67);

	std::cout << "my_vector[3] = 23" << std::endl;
	my_vector[3] = 23;
	print_vector(my_vector);
	assert(my_vector[3] == 23);

	std::cout << "---------- TESTING ITERATORS ----------" << std::endl;

	std::cout << "iterator it = my_vector.begin()" << std::endl;
	NS::vector<int>::iterator it = my_vector.begin();
	std::cout << "*it -> " << *it << std::endl;
	std::cout << "*(it + 3) -> " << *(it + 3) << std::endl;
	std::cout << "*(3 + it)-> " << *(3 + it) << std::endl;
	std::cout << "it += 4" << std::endl;
	it += 4;
	std::cout << "*it -> " << *it << std::endl;
	std::cout << "it -= 1" << std::endl;
	it -= 1;
	std::cout << "*it -> " << *it << std::endl;
	std::cout << "*(it + 1) -> " << *(it + 1) << std::endl;
	std::cout << "*(it - 3) -> " << *(it - 3) << std::endl;
	std::cout << "it[0]-> " << it[0] << std::endl;
	std::cout << "iterator it2 = my_vector.begin()" << std::endl;
	NS::vector<int>::iterator it2 = my_vector.begin();
	std::cout << "it == it -> " << (it == it ? "true" : "false") << std::endl;
	std::cout << "it == it2 -> " << (it == it2 ? "true" : "false") << std::endl;
	std::cout << "it != it2 -> " << (it != it2 ? "true" : "false") << std::endl;
	std::cout << "it < it2 -> " << (it < it2 ? "true" : "false") << std::endl;
	std::cout << "it2 < it -> " << (it2 < it ? "true" : "false") << std::endl;
	std::cout << "it >= it2 -> " << (it >= it2 ? "true" : "false") << std::endl;
	std::cout << "it2 <= it -> " << (it2 <= it ? "true" : "false") << std::endl;
	std::cout << "*(--it) -> " << *(--it) << std::endl;
	std::cout << "*(it--) -> " << *(it--) << std::endl;
	std::cout << "*it -> " << *it << std::endl;
	std::cout << "*(++it) -> " << *(++it) << std::endl;
	std::cout << "*(it++) -> " << *(it++) << std::endl;
	std::cout << "*it -> " << *it << std::endl;
	// TODO: Test for loop iteration
	// TODO: Test reverse iteration

	NS::vector<int>::const_iterator cit = it;
	std::cout << "*cit -> " << *cit << std::endl;


	std::cout << "---------- TESTING MODIFIERS ----------" << std::endl;

	std::cout << "clear()" << std::endl;
	my_vector.clear();
	print_vector(my_vector);
	assert(my_vector.empty());

	std::cout << "assign(13, 42)" << std::endl;
	my_vector.assign(13, 42);
	print_vector(my_vector);
	assert(my_vector.size() == 13);

	std::cout << "assign(5, 21)" << std::endl;
	my_vector.assign(5, 21);
	print_vector(my_vector);
	assert(my_vector.size() == 5);

	std::cout << "assign(5, 21)" << std::endl;
	my_vector.assign(5, 21);
	print_vector(my_vector);
	assert(my_vector.size() == 5);

	std::cout << "creating my_vector2 with a push_back for loop" << std::endl;
	NS::vector<int> my_vector2;
	for (size_t i = 0; i < 10; i++) {
		my_vector2.push_back(i);
	}
	print_vector(my_vector2);

	std::cout << "my_vector.assign(my_vector2.begin(), my_vector2.end())" << std::endl;
	my_vector.assign(my_vector2.begin(), my_vector2.end());
	print_vector(my_vector);

	std::cout << "adding a few element to my_vector2 with push_back" << std::endl;
	for (size_t i = 10; i < 18; i++) {
		my_vector2.push_back(i);
	}
	print_vector(my_vector2);

	std::cout << "my_vector.assign(my_vector2.begin(), my_vector2.end())" << std::endl;
	my_vector.assign(my_vector2.begin(), my_vector2.end());
	print_vector(my_vector);

	std::cout << "my_vector.pop_back() 3 times" << std::endl;
	my_vector.pop_back();
	my_vector.pop_back();
	my_vector.pop_back();
	print_vector(my_vector);

	std::cout << "my_vector.insert(begin() + 2, 27)" << std::endl;
	my_vector.insert(my_vector.begin() + 2, 27);
	print_vector(my_vector);
	assert(my_vector[2] == 27);

	std::cout << "my_vector.insert(begin() + 3, 2, 33)" << std::endl;
	my_vector.insert(my_vector.begin() + 3, 2, 33);
	print_vector(my_vector);
	assert(my_vector[3] == 33);
	assert(my_vector[4] == 33);

	std::cout << "my_vector.insert(begin() + 5, 5, 49)" << std::endl;
	my_vector.insert(my_vector.begin() + 5, 5, 49);
	print_vector(my_vector);
	assert(my_vector[5] == 49);
	assert(my_vector[9] == 49);

	std::cout << "my_vector.insert(begin(), 66)" << std::endl;
	my_vector.insert(my_vector.begin(), 66);
	print_vector(my_vector);
	assert(my_vector[0] == 66);

	std::cout << "my_vector.insert(begin(), my_vector2.begin(), my_vector2.begin() + 5)"
			  << std::endl;
	my_vector.insert(my_vector.begin(), my_vector2.begin(), my_vector2.begin() + 5);
	print_vector(my_vector);
	assert(my_vector[0] == 0);
	assert(my_vector[4] == 4);

	std::cout << "my_vector.insert(end(), my_vector2.begin() + 5, my_vector2.begin() + 10)"
			  << std::endl;
	my_vector.insert(my_vector.end(), my_vector2.begin() + 5, my_vector2.begin() + 10);
	print_vector(my_vector);
	assert(my_vector[29] == 5);
	assert(my_vector[33] == 9);

	std::cout << "my_vector.insert(begin() + size() / 2, my_vector2.begin(), my_vector2.end())"
			  << std::endl;
	my_vector.insert(my_vector.begin() + static_cast<ptrdiff_t>(my_vector.size()) / 2,
					 my_vector2.begin(), my_vector2.end());
	print_vector(my_vector);
	assert(my_vector[17] == 0);
	assert(my_vector[34] == 17);

	std::cout << "my_vector.erase(begin())" << std::endl;
	my_vector.erase(my_vector.begin());
	print_vector(my_vector);
	assert(my_vector[0] == 1);

	std::cout << "my_vector.erase(begin() + 2)" << std::endl;
	my_vector.erase(my_vector.begin() + 2);
	print_vector(my_vector);
	assert(my_vector[2] == 4);

	std::cout << "it_last_before_erase = my_vector.erase(begin() + 15, begin() + 32)" << std::endl;
	NS::vector<int>::iterator
			it_last_before_erase = my_vector.erase(my_vector.begin() + 15, my_vector.begin() + 33);
	print_vector(my_vector);
	std::cout << "*it_last_before_erase -> " << *it_last_before_erase << std::endl;

	std::cout << "it_end = my_vector.erase(begin(), end())" << std::endl;
	NS::vector<int>::iterator it_end = my_vector.erase(my_vector.begin(), my_vector.end());
	print_vector(my_vector);
	std::cout << "it_end == my_vector.end() -> " << (it_end == my_vector.end() ? "true" : "false")
			  << std::endl;

	std::cout << "empty_vector.swap(my_vector)" << std::endl;
	empty_vector.swap(my_vector);
	std::cout << "empty_vector" << std::endl;
	print_vector(empty_vector);
	std::cout << "my_vector" << std::endl;
	print_vector(my_vector);

	std::cout << "swap(my_vector, my_vector2)" << std::endl;
	swap(my_vector, my_vector2);
	std::cout << "my_vector" << std::endl;
	print_vector(my_vector);
	std::cout << "my_vector2" << std::endl;
	print_vector(my_vector2);

	std::cout << "my_vector2 = my_vector" << std::endl;
	my_vector2 = my_vector;
	std::cout << "my_vector" << std::endl;
	print_vector(my_vector);
	std::cout << "my_vector2" << std::endl;
	print_vector(my_vector2);

	std::cout << "---------- TESTING COMPARISONS ----------" << std::endl;

	std::cout << "creating v_abc" << std::endl;
	NS::vector<char> v_abc;
	v_abc.push_back('a');
	v_abc.push_back('b');
	v_abc.push_back('c');
	print_vector(v_abc);

	std::cout << "creating v_abd" << std::endl;
	NS::vector<char> v_abd;
	v_abd.push_back('a');
	v_abd.push_back('b');
	v_abd.push_back('d');
	print_vector(v_abd);

	std::cout << "creating v_abc2" << std::endl;
	NS::vector<char> v_abc2;
	v_abc2.push_back('a');
	v_abc2.push_back('b');
	v_abc2.push_back('c');
	print_vector(v_abc2);

	std::cout << "creating v_abcd" << std::endl;
	NS::vector<char> v_abcd;
	v_abcd.push_back('a');
	v_abcd.push_back('b');
	v_abcd.push_back('c');
	v_abcd.push_back('d');
	print_vector(v_abcd);

	std::cout << "v_abc == v_abc2 -> " << (v_abc == v_abc2 ? "true" : "false") << std::endl;
	assert(v_abc == v_abc2);
	std::cout << "v_abc != v_abc2 -> " << (v_abc != v_abc2 ? "true" : "false") << std::endl;
	assert(!(v_abc != v_abc2));
	std::cout << "v_abc == v_abd -> " << (v_abc == v_abd ? "true" : "false") << std::endl;
	assert(!(v_abc == v_abd));
	std::cout << "v_abc != v_abd -> " << (v_abc != v_abd ? "true" : "false") << std::endl;
	assert(v_abc != v_abd);
	std::cout << "v_abc < v_abd -> " << (v_abc < v_abd ? "true" : "false") << std::endl;
	assert(v_abc < v_abd);
	std::cout << "v_abc > v_abd -> " << (v_abc > v_abd ? "true" : "false") << std::endl;
	assert(!(v_abc > v_abd));
	std::cout << "v_abc <= v_abd -> " << (v_abc <= v_abd ? "true" : "false") << std::endl;
	assert(v_abc <= v_abd);
	std::cout << "v_abc >= v_abd -> " << (v_abc >= v_abd ? "true" : "false") << std::endl;
	assert(!(v_abc >= v_abd));
	std::cout << "v_abc == v_abcd -> " << (v_abc == v_abcd ? "true" : "false") << std::endl;
	assert(!(v_abc == v_abcd));
	std::cout << "v_abcd == v_abc -> " << (v_abcd == v_abc ? "true" : "false") << std::endl;
	assert(!(v_abcd == v_abc));
	std::cout << "v_abc < v_abcd -> " << (v_abc < v_abcd ? "true" : "false") << std::endl;
	assert(v_abc < v_abcd);

}

#include "map.hpp"


int main() {

	//test_vector();
	//TODO: test_stack
	//TODO: test_map

	ft::map<int, char> my_map;
	std::cout << "size: " << my_map.size() << std::endl;
	my_map.print_tree();

	for (int i = 0; i < 10; i++) {
		int random_variable = std::rand() % 26;
		ft::pair<int, char> pair = ft::make_pair(random_variable, random_variable + 65);
		my_map.insert(pair);
	}

	std::cout << "size: " << my_map.size() << std::endl;
	my_map.print_tree();

	ft::map<int, char>::iterator it = my_map.begin();
	for (; it != my_map.end(); it++) {
		std::cout << it->first << std::endl;
	}
	it = my_map.end();

	std::cout << "####################" << std::endl;

	it = my_map.begin();

	for (; it != my_map.end();) {
		my_map.erase(it++);
		my_map.print_tree();
		std::cout << "############################################" << std::endl;
	}


	//TODO: DEBUG NEEDED !
//	ft::map<int, char>::reverse_iterator rit = my_map.rbegin();
//	for (; rit != my_map.rend(); rit++) {
//		std::cout << rit->first << std::endl;
//	}
//
//	my_map.clear();
//
//	std::cout << "size: " << my_map.size() << std::endl;
//	my_map.print_tree();
//
//	it = my_map.begin();
//	for (; it != my_map.end(); it++) {
//		std::cout << it->first << std::endl;
//	}

	return 0;
}
