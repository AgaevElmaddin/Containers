#ifndef IS_ITERATOR
# define IS_ITERATOR

# include "is_integral.hpp"
# include "iterators_traits.hpp"

namespace ft
{
	template<class T>
	struct is_iterator: public false_type
	{

	};

	// 1) input iterator
	template<>
	struct is_iterator<input_iterator_tag>: public true_type
	{

	};

	// 2) output iterator
	template<>
	struct is_iterator<output_iterator_tag>: public true_type
	{

	};

	// 3) forward iterator
	template<>
	struct is_iterator<forward_iterator_tag>: public true_type
	{

	};

	// 4) bidirectional iterator
	template<>
	struct is_iterator<bidirectional_iterator_tag>: public true_type
	{

	};

	// 5) random_access_iterator_tag iterator
	template<>
	struct is_iterator<random_access_iterator_tag>: public true_type
	{

	};
}

#endif