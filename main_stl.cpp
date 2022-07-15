#include <map>
#include <stack>
#include <vector>


namespace ft = std;

#include <cassert>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <string>
#include <deque>


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T> class MutantStack : public ft::stack<T> {
	public:
		MutantStack() {}

		MutantStack(const MutantStack<T> & src) { *this = src; }

		MutantStack<T> & operator=(const MutantStack<T> & rhs) {
			this->c = rhs.c;
			return *this;
		}

		~MutantStack() {}

		typedef typename ft::stack<T>::container_type::iterator iterator;

		iterator begin() { return this->c.begin(); }

		iterator end() { return this->c.end(); }
};

void test_42(int argc, char ** argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return;
	}
	const int seed = std::atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++) {
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++) {
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try {
		for (int i = 0; i < COUNT; i++) {
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	} catch (const std::exception & e) {
		//NORMAL ! :P
	}

	for (int i = 0; i < COUNT; ++i) {
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++) {
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++) {
		iterable_stack.push(letter);
	}
	for (MutantStack<char>::iterator it = iterable_stack.begin();
		 it != iterable_stack.end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl;
}

template <class T> void print_vector(ft::vector<T> & v) {
	size_t size = v.size();
	std::cout << " └─> Vector | size:" << std::setw(4) << size;
	std::cout << " | content: [";
	for (size_t i = 0; i < size; i++) {
		if (i < size) {
			std::cout << std::setw(2) << v[i];
		} else {
			std::cout << "  ";
		}
		if (i < size - 1) {
			std::cout << "|";
		}
	}
	std::cout << "]" << std::endl;
}

template <class key, class value> void print_map(ft::map<key, value> & m) {
	size_t size = m.size();
	std::cout << " └─> Map | size:" << std::setw(4) << size;
	std::cout << " | content: [";
	ft::map<int, char>::iterator it = m.begin();
	for (size_t i = 0; it != m.end(); i++, it++) {
		std::cout << std::setw(2) << it->first << ", " << it->second;
		if (i < size - 1) {
			std::cout << "|";
		}
	}
	std::cout << "]" << std::endl;
}

void test_vector() {

	std::cout << "\n========== TESTING VECTOR ==========\n" << std::endl;

	std::cout << "---------- TESTING CONSTRUCTION / DESTRUCTION ----------" << std::endl;

	std::cout << "empty_vector()" << std::endl;
	ft::vector<int> empty_vector;
	print_vector(empty_vector);
	assert(empty_vector.empty());

	std::cout << "my_vector(5, 42)" << std::endl;
	ft::vector<int> my_vector(5, 42);
	print_vector(my_vector);
	assert(my_vector.size() == 5);
	assert(my_vector.capacity() >= my_vector.size());

	std::cout << "my_vector_range(my_vector.begin(), my_vector.end())" << std::endl;
	ft::vector<int> my_vector_range(my_vector.begin(), my_vector.end());
	print_vector(my_vector_range);

	std::cout << "my_vector_copy(my_vector)" << std::endl;
	ft::vector<int> my_vector_copy(my_vector);
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

	// Commented because the ouput is implementation defined and causes a confusing diff
//	std::cout << "my_vector.at(-1)" << std::endl;
//	print_vector(my_vector);
//	try {
//		my_vector.at(-1);
//	} catch (std::exception & e) {
//		std::cout << " └─> " << "Exception: " << e.what() << std::endl;
//	}

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
	ft::vector<int>::iterator it = my_vector.begin();
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
	ft::vector<int>::iterator it2 = my_vector.begin();
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

	ft::vector<int>::const_iterator cit = it;
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
	ft::vector<int> my_vector2;
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
	my_vector.insert(my_vector.begin() + static_cast<std::ptrdiff_t>(my_vector.size()) / 2,
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
	ft::vector<int>::iterator
			it_last_before_erase = my_vector.erase(my_vector.begin() + 15, my_vector.begin() + 33);
	print_vector(my_vector);
	std::cout << "*it_last_before_erase -> " << *it_last_before_erase << std::endl;

	std::cout << "it_end = my_vector.erase(begin(), end())" << std::endl;
	ft::vector<int>::iterator it_end = my_vector.erase(my_vector.begin(), my_vector.end());
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
	ft::vector<char> v_abc;
	v_abc.push_back('a');
	v_abc.push_back('b');
	v_abc.push_back('c');
	print_vector(v_abc);

	std::cout << "creating v_abd" << std::endl;
	ft::vector<char> v_abd;
	v_abd.push_back('a');
	v_abd.push_back('b');
	v_abd.push_back('d');
	print_vector(v_abd);

	std::cout << "creating v_abc2" << std::endl;
	ft::vector<char> v_abc2;
	v_abc2.push_back('a');
	v_abc2.push_back('b');
	v_abc2.push_back('c');
	print_vector(v_abc2);

	std::cout << "creating v_abcd" << std::endl;
	ft::vector<char> v_abcd;
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

void test_map() {
	std::cout << "\n========== TESTING MAP ==========\n" << std::endl;

	ft::map<int, char> my_map;
	print_map(my_map);

	std::cout << "---------- TESTING INSERTION AND ITERATORS ----------" << std::endl;
	for (int i = 0; i < 10; i++) {
		int random_variable = std::rand() % 26;
		ft::pair<int, char> pair = ft::make_pair(random_variable, random_variable + 65);
		my_map.insert(pair);
	}
	print_map(my_map);

	ft::map<int, char>::iterator it = my_map.begin();
	for (; it != my_map.end(); it++) {
		std::cout << it->first << std::endl;
	}
	ft::map<int, char>::const_iterator cit = my_map.begin();
	for (; cit != my_map.end(); cit++) {
		std::cout << cit->first << std::endl;
	}
	ft::map<int, char>::reverse_iterator rit = my_map.rbegin();
	for (; rit != my_map.rend(); rit++) {
		std::cout << rit->first << std::endl;
	}
	ft::map<int, char>::const_reverse_iterator crit(my_map.rbegin());
	for (; crit != my_map.rend(); crit++) {
		std::cout << crit->first << std::endl;
	}
	std::cout << "---------- TESTING ERASE ----------" << std::endl;
	it = my_map.begin();
	for (; it != my_map.end();) {
		my_map.erase(it++);
		print_map(my_map);
	}

	for (int i = 0; i < 10; i++) {
		int random_variable = std::rand() % 26;
		ft::pair<int, char> pair = ft::make_pair(random_variable, random_variable + 65);
		my_map.insert(pair);
	}
	print_map(my_map);

	std::cout << "---------- TESTING COPY AND RANGE INSERTION ----------" << std::endl;
	ft::map<int, char> my_map2(my_map);
	print_map(my_map2);
	ft::map<int, char> my_map3;
	my_map3.insert(my_map2.begin(), my_map2.end());
	print_map(my_map3);
	assert(my_map == my_map2);
	assert(my_map == my_map3);

	std::cout << "---------- TESTING FIND ----------" << std::endl;
	std::cout << my_map.find(my_map.begin()->first)->first << std::endl;

	std::cout << "---------- TESTING SWAP ----------" << std::endl;
	my_map.erase((my_map.begin()++)->first);
	my_map.swap(my_map2);
	print_map(my_map);
	print_map(my_map2);
	swap(my_map, my_map2);
	print_map(my_map);
	print_map(my_map2);

	std::cout << "---------- TESTING COMPARISONS ----------" << std::endl;
	assert(my_map != my_map2);
	assert(my_map2 == my_map3);
	assert(my_map > my_map2);

	std::cout << "---------- TESTING BOUNDS ----------" << std::endl;
	std::cout << my_map.upper_bound(5)->first << std::endl;
	std::cout << my_map.lower_bound(5)->first << std::endl;
	std::cout << my_map2.upper_bound(5)->first << std::endl;
	std::cout << my_map2.lower_bound(5)->first << std::endl;
	std::cout << my_map3.upper_bound(5)->first << std::endl;
	std::cout << my_map3.lower_bound(5)->first << std::endl;
}

void test_stack() {
	std::cout << "\n========== TESTING STACK ==========\n" << std::endl;
	ft::stack<int> my_stack;
	my_stack.push(1);
	std::cout << my_stack.top() << std::endl;
	std::cout << my_stack.size() << std::endl;
	my_stack.push(2);
	std::cout << my_stack.top() << std::endl;
	std::cout << my_stack.size() << std::endl;
	my_stack.push(3);
	std::cout << my_stack.top() << std::endl;
	std::cout << my_stack.size() << std::endl;
	my_stack.pop();
	std::cout << my_stack.top() << std::endl;
	std::cout << my_stack.size() << std::endl;
	my_stack.pop();
	std::cout << my_stack.top() << std::endl;
	std::cout << my_stack.size() << std::endl;
	my_stack.pop();
	std::cout << my_stack.size() << std::endl;
}

int main(int argc, char ** argv) {

	test_42(argc, argv);
	test_vector();
	test_map();
	test_stack();

	return 0;
}
