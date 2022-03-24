#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

// #include <type_traits>

namespace ft
{
	// implementation of enable_if
	template <bool B, class T = void>
	struct enable_if
	{

	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif
