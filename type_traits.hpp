#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

template <bool B, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> {
	typedef T type;
};

template <typename T, T v> struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;

	operator value_type() const {
		return value;
	}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <typename> struct is_integral_base : false_type {};
template <> struct is_integral_base<bool> : true_type {};
template <> struct is_integral_base<char> : true_type {};
template <> struct is_integral_base<wchar_t> : true_type {};
template <> struct is_integral_base<signed char> : true_type {};
template <> struct is_integral_base<short int> : true_type {};
template <> struct is_integral_base<int> : true_type {};
template <> struct is_integral_base<long int> : true_type {};
template <> struct is_integral_base<long long int> : true_type {};
template <> struct is_integral_base<unsigned char> : true_type {};
template <> struct is_integral_base<unsigned short int> : true_type {};
template <> struct is_integral_base<unsigned int> : true_type {};
template <> struct is_integral_base<unsigned long int> : true_type {};
template <> struct is_integral_base<unsigned long long int> : true_type {};
template <> struct is_integral_base<const bool> : true_type {};
template <> struct is_integral_base<const char> : true_type {};
template <> struct is_integral_base<const wchar_t> : true_type {};
template <> struct is_integral_base<const signed char> : true_type {};
template <> struct is_integral_base<const short int> : true_type {};
template <> struct is_integral_base<const int> : true_type {};
template <> struct is_integral_base<const long int> : true_type {};
template <> struct is_integral_base<const long long int> : true_type {};
template <> struct is_integral_base<const unsigned char> : true_type {};
template <> struct is_integral_base<const unsigned short int> : true_type {};
template <> struct is_integral_base<const unsigned int> : true_type {};
template <> struct is_integral_base<const unsigned long int> : true_type {};
template <> struct is_integral_base<const unsigned long long int> : true_type {};

template <typename T> struct is_integral : is_integral_base<T> {};

template <class T> struct remove_const {
	typedef T type;
};

template <class T> struct remove_const<const T> {
	typedef T type;
};

}

#endif
