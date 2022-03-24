#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

#include <type_traits>

namespace ft
{
	// implementation of integral_constant which is parent for is_integral
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const { return value; }
	};

	// bool variant true_type
	typedef integral_constant<bool, true> true_type;

	// bool variant false_type
	typedef integral_constant<bool, false> false_type;

	// implementation of is_integral which inherited from integral_constant;
	// if the type is integral, returns true, otherwise it returns false
	template <class T>
	struct is_integral: public false_type
	{

	};

	// 1) bool
	template <>
	struct is_integral<bool>: public true_type
	{

	};

	// 2) char
	template <>
	struct is_integral<char>: public true_type
	{

	};

	// 3) char16_t
	template <>
	struct is_integral<char16_t>: public true_type
	{

	};

	// 4) char32_t
	template <>
	struct is_integral<char32_t>: public true_type
	{

	};

	// 5) wchar_t
	template <>
	struct is_integral<wchar_t>: public true_type
	{

	};

	// 6) signed char
	template <>
	struct is_integral<signed char>: public true_type
	{

	};

	// 7) short int
	template <>
	struct is_integral<short int>: public true_type
	{

	};

	// 8) int
	template <>
	struct is_integral<int> : public true_type
	{

	};

	// 9) long int
	template <>
	struct is_integral<long int> : public true_type
	{

	};

	// 10) long long int
	template <>
	struct is_integral<long long int> : public true_type
	{

	};

	// 11) unsigned char
	template <>
	struct is_integral<unsigned char>: public true_type
	{

	};

	// 12) unsigned short int
	template <>
	struct is_integral<unsigned short int>: public true_type
	{

	};

	// 13) unsigned int
	template <>
	struct is_integral<unsigned int> : public true_type
	{

	};

	// 14) unsigned long int
	template <>
	struct is_integral<unsigned long int> : public true_type
	{

	};

	// 15) unsigned long long int
	template <>
	struct is_integral<unsigned long long int> : public true_type
	{

	};
}

#endif
